#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <algorithm>

#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include "../include/cyberdns.h"
#include "../include/cyberpc.h"
#include "../include/cyberexpert.h"
#include "../include/cyberworm.h"
using namespace std;

int days=0; 							// 1 event occurs per day
int terminationTime=-1;					//time to end simulation
 // used for the termination time (to keep the days output running)

void day_activity(CyberDNS *server,vector<CyberExpert*> *expert_list){

	vector<string> pc_list = server->GetCyberPCList(); //get list of pc names
	int index_pclist = 0; //points on the current computer to be examined
	int pcs_size = pc_list.size();
	int experts_size = expert_list->size();
	CyberPC* p_pc;
	CyberExpert* curr_expert;
	bool checkedAllPC;

	if (pcs_size>index_pclist)
		checkedAllPC=false;
	else
		checkedAllPC=true;

	//CLEANING EVENT
	for (int i=0; i<experts_size; i++){
		curr_expert= (*expert_list)[i];

		if (curr_expert->isActive() || curr_expert->getRestTime()==0){ //expert is now working
			for (int j=0; j<curr_expert->getEfficiency() && !checkedAllPC; j++){

				cout << "	" << curr_expert->getName() << " examining " << pc_list[index_pclist] << endl;
				p_pc= server->GetCyberPC(pc_list[index_pclist]); // receive current pc to examine by index
				p_pc->Disinfect();
				index_pclist++; // index_pclist runs over the pc list by loop

				if (index_pclist+1==pcs_size) // finished to check all pc list
								checkedAllPC=true;
			}
			if (index_pclist+1==pcs_size){ // finished to check all pc list
				checkedAllPC=true;
			}
			if (curr_expert->getWorkOrRest()==1 && curr_expert->getRestTime()!=0)
				cout << "	" << curr_expert->getName() << " is taking a break" << endl;

		}
		else { 		//expert is now resting
			if (curr_expert->getWorkOrRest()==0  && curr_expert->getRestTime()!=0){
				if (curr_expert->getRestTime()==1)
					curr_expert->setWorkOrRest(-1); //adjust to the rest days number (in negative)
			}
			if (curr_expert->getWorkOrRest() == (curr_expert->getRestTime()*(-1))){   //if finished resting (i.e if 3 = -3)
				if ( curr_expert->getRestTime()!=0)
					cout << "        " << curr_expert->getName() << " returns to work tomorrow" << endl;
				curr_expert->setWorkOrRest(curr_expert->getWorkTime()+1); // refresh back to the number of working days
			}
		}
		curr_expert->setWorkOrRest((curr_expert->getWorkOrRest())-1);      //reduce one day of work (or rest)
	}

	//INFECTING EVENT
	for (int i=0; i<pcs_size; i++){ //reduce time to infect for each pc
		p_pc = server->GetCyberPC(pc_list[i]); // p_pc list = the next computer
		if (p_pc->getWorm()!=NULL){
			if (p_pc->getTime()==0){ //if worm is awake
				p_pc->Run(*server); // infect all the other connected computers
			}
			//Dormancy check
			else if (p_pc->getTime()> 0){
				string worm_name = p_pc->getWorm()->getName();
				cout << "	" << p_pc->getName() << ": Worm " << worm_name << " is dormant" << endl;
			}
		}
		if (p_pc->getTime()>0)
			p_pc->reduceTime();
	}
	days++;
	return;
}




int main(int argc, char**argv){
	bool flagTerminate=false;
	vector<CyberExpert*> *expert_list;		//list of cyber experts
	expert_list = new vector<CyberExpert*>();

	CyberDNS* server= new CyberDNS();				//server with list of computers

    using boost::property_tree::ptree;
    ptree computers;
    read_xml("computers.xml", computers);
    BOOST_FOREACH(ptree::value_type &v, computers) {
    		 cout << "Adding to server: " << v.second.get<std::string>("name")<< endl;
           	 CyberPC* pc = new CyberPC(v.second.get<std::string>("os"),v.second.get<std::string>("name")); // deleted by DNS server destructor
           	 server->AddPC(pc);
             cout<<v.second.get<std::string>("name")+ " connected to server " << endl;
    }
	server->initNetwork(); // add all pcs and connections to network
	ptree events;
	read_xml("events.xml", events);

    BOOST_FOREACH(ptree::value_type &v, events) {
    	if (flagTerminate==false){

			cout << "Day : " << days << endl;

			if ((string)v.first.data()=="hack"){
																	//Create the Worm of the new hacker
				CyberWorm* newWorm;
				string wormH_os= v.second.get<std::string>("wormOs");
				string wormH_name= v.second.get<std::string>("wormName");
				int wormH_dormancy= v.second.get<int>("wormDormancy");
				newWorm = new CyberWorm(wormH_os,wormH_name,wormH_dormancy);
				vector<string> pc_list = server->GetCyberPCList(); //pc list for access to server to find the wanted pc to infect
				string pc_name= v.second.get<std::string>("computer"); // retrieve pc name from xml

				int size=pc_list.size();
				bool found=false; //found the pc
				for (int i=0; i< size&&!found; i++){ // search for pc name in CyberPC list from server
					if (pc_name == pc_list[i]){
						found=true;
						if (server->GetCyberPC(pc_list[i])->getOs() == wormH_os){
							std::cout << "	" << "Hack occured on " << pc_list[i] << std::endl;
							server->GetCyberPC(pc_list[i])->Infect(*newWorm);

						}
						else
							std::cout << "	Worm " << wormH_name << " is incompatible with " << pc_list[i] << std::endl;
					}
				}
				delete newWorm;
				day_activity(server,expert_list);
			}

			if ((string)v.first.data()=="clock-in"){
																		// CREATE NEW CYBER EXPERT
				string expert_name= v.second.get<std::string>("name");
				int expert_workTime= v.second.get<int>("workTime");
				int expert_restTime= v.second.get<int>("restTime");
				int expert_efficiency= v.second.get<int>("efficiency");
				CyberExpert* newExpert = new CyberExpert(expert_name,expert_workTime,expert_restTime,expert_efficiency);
				expert_list->push_back(newExpert); //add the expert to the experts list
				cout << "	Clock in: " << expert_name << " began working" << std::endl;
				day_activity(server,expert_list);
			}

			if ((string)v.first.data()=="termination"){			// Read from XML to the variable created
				terminationTime= v.second.get<int>("time");
				flagTerminate=true;
				day_activity(server,expert_list);
			}
    	} // if
    } // booster
    while (days<=terminationTime){ // Complete the rest of the days left until termination time
		cout << "Day : " << days << endl;
    	day_activity(server,expert_list);
    }


    int size=expert_list->size(); //delete all experts in the list
    for (int i=0; i<size; i++)
    	delete expert_list->at(i);

    delete expert_list; //delete the vector itself
	delete server;
}



#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "../include/cyberdns.h"
#include "../include/cyberpc.h"


#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
using namespace std;

CyberDNS::CyberDNS():cyber_DNS_(){}

CyberDNS::~CyberDNS(){ //DESTRUCTOR
	std::map<std::string,CyberPC*>::iterator it;
	for (it= cyber_DNS_.begin(); it!=cyber_DNS_.end(); it++){
		delete it->second; //delete the computers
	}
	cyber_DNS_.clear(); //delete the hashmap itself
}

void CyberDNS::AddPC(CyberPC * cyber_pc_){ //added in order of the string (pc_name)
	std::string s1=cyber_pc_->getName();
	cyber_DNS_.insert(std::pair<std::string,CyberPC*>(s1,cyber_pc_));
}

CyberPC* CyberDNS::GetCyberPC(const std::string & cyber_pc_name) const{
	return cyber_DNS_.find(cyber_pc_name)->second;
}

std::vector<std::string> CyberDNS::GetCyberPCList(){		// Return list of PC's as a vector of strings.
	std::map<std::string,CyberPC*>::reverse_iterator rev_it;
	std::vector<std::string> vec;
	for (rev_it= cyber_DNS_.rbegin(); rev_it!=cyber_DNS_.rend(); rev_it++) // maybe its ++rit CHECK
		vec.push_back(rev_it->first);
	return vec;
}


void CyberDNS::initNetwork()
 {
     // Create an empty property tree object
     using boost::property_tree::ptree;
     ptree wires;
     vector<string> pc_list = GetCyberPCList();
     int size=pc_list.size();
     bool pc1_found;
     bool pc2_found;
     read_xml("network.xml", wires);

           BOOST_FOREACH(ptree::value_type &v, wires) {
        	   	 pc1_found=false;							// check if computers to be wired exist
        	   	 pc2_found=false;
        	   	 for (int i=0; i<size && (!pc1_found || !pc2_found) ; i++){
        	   		 if (v.second.get<std::string>("pointA")==pc_list.at(i))
        	   			 pc1_found=true;
        	   		 if (v.second.get<std::string>("pointB")==pc_list.at(i))
        	   		        	   			 pc2_found=true;
        	   	 }

        	     if (pc1_found && pc2_found){ //connect the pcs
					 cout<<"Connecting "+v.second.get<std::string>("pointA")+ " to "+ v.second.get<std::string>("pointB")<< endl;
					 GetCyberPC(v.second.get<std::string>("pointA"))->AddConnection(v.second.get<std::string>("pointB"));
					 cout<<"	" << v.second.get<std::string>("pointA")+ " now connected to "+ v.second.get<std::string>("pointB")<<endl;
					 GetCyberPC(v.second.get<std::string>("pointB"))->AddConnection(v.second.get<std::string>("pointA"));
					 cout<<"	" << v.second.get<std::string>("pointB")+ " now connected to "+ v.second.get<std::string>("pointA")<<endl;

        	     }
           }
 }


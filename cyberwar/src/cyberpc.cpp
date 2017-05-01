#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../include/cyberpc.h"

CyberPC::CyberPC(std::string cyber_pc_os, std::string cyber_pc_name):
	cyber_pc_os_(cyber_pc_os),
	cyber_pc_name_(cyber_pc_name),
	cyber_worm_(0),
	cyber_pc_time_to_infect_(0)
	{}

const std::string CyberPC::getName()
{
	return cyber_pc_name_;
}

const std::string CyberPC::getOs(){
	return cyber_pc_os_;
}

CyberWorm * CyberPC::getWorm(){
	if (cyber_worm_!=NULL)
		return cyber_worm_;
	return NULL;
}

int CyberPC::getTime(){
	return cyber_pc_time_to_infect_;
}

void CyberPC::reduceTime(){ //reduce time by 1
	cyber_pc_time_to_infect_--;
}

// DESTRUCTOR
CyberPC::~CyberPC(){
	delete cyber_worm_;
	cyber_worm_=NULL; // init pointer
}

void CyberPC::Infect(CyberWorm & worm){
	if (cyber_pc_os_==worm.getOs()){
		cyber_pc_time_to_infect_=worm.getTime();
		delete cyber_worm_; //delete the old worm
		cyber_worm_= new CyberWorm(worm); //add a new one
		std::cout << "		" << cyber_pc_name_ << " infected by " << cyber_worm_->getName() << std::endl;
	}
	else
		std::cout << "		Worm " << worm.getName() << " is incompatible with " << cyber_pc_name_ << std::endl;

}

void CyberPC::Disinfect(){
	if (cyber_worm_!=NULL){
		cyber_pc_time_to_infect_=0;
		std::cout << "		Worm " << this->cyber_worm_->getName() << " successfully removed from " << cyber_pc_name_ << std::endl;
		delete cyber_worm_;
		cyber_worm_=NULL; //init pointer
	}
}

void CyberPC::Run(const CyberDNS & server){
	if (cyber_worm_!=NULL && cyber_pc_time_to_infect_==0){ // has a worm which is not sleeping
		std::cout << "	" << cyber_pc_name_ << " infecting... " << std::endl;
		int size=cyber_pc_connections_.size();
		CyberPC* pc_pointer; // pointer to the computer that will be infected (passes through all the pcs connected to this pc)
		for (int i=0; i<size; i++){
			pc_pointer= server.GetCyberPC(cyber_pc_connections_[i]);
			pc_pointer->Infect(*cyber_worm_);
		}
	}
}

void CyberPC::AddConnection(std::string  second_pc){ //add connection to pc_connections_list
	int size= cyber_pc_connections_.size();
	bool flag=false;
	for (int i=0; i<size && !flag; i++){ //run over the connections list
		if (cyber_pc_connections_[i]==second_pc)
			flag=true;
	}
	if (!flag)
		cyber_pc_connections_.push_back(second_pc); //add the wanted computer to the connection list
}


#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "../include/cyberpc.h"
#include "../include/cyberexpert.h"

CyberExpert::CyberExpert(std::string cyber_expert_name, int cyber_expert_work_time, int cyber_expert_rest_time, int cyber_expert_efficiency):
	cyber_expert_name_(cyber_expert_name),
	cyber_expert_work_time_(cyber_expert_work_time),
	cyber_expert_rest_time_(cyber_expert_rest_time),
	cyber_expert_efficiency_(cyber_expert_efficiency),
	workOrRest(cyber_expert_work_time){}

CyberExpert::~CyberExpert(){} //DESTRUCTOR

void CyberExpert::Clean(CyberPC & cyber_pc){
	cyber_pc.Disinfect();
}

bool CyberExpert::isActive(){
	if (workOrRest>0){
		return true;
	}
	else return false;
}

void CyberExpert::setWorkOrRest(int num){
	workOrRest = num;
}

int CyberExpert::getWorkOrRest(){
	return workOrRest;
}

const std::string CyberExpert::getName()
{
		return cyber_expert_name_;
}

const int CyberExpert::getWorkTime()
{
	return cyber_expert_work_time_;
}

const int CyberExpert::getRestTime()
{
	return cyber_expert_rest_time_;
}

const int CyberExpert::getEfficiency()
{
	return cyber_expert_efficiency_;
}

#include <iostream>
#include <string>
#include <vector>
#include "../include/cyberworm.h"


CyberWorm::CyberWorm(std::string cyber_worm_os,std::string cyber_worm_name,int cyber_worm_dormancy_time): // build constructor
	cyber_worm_os_(cyber_worm_os),
	cyber_worm_name_(cyber_worm_name),
	cyber_worm_dormancy_time_(cyber_worm_dormancy_time){}

CyberWorm::~CyberWorm(){}

CyberWorm::CyberWorm(const CyberWorm& other): //copy constructor
		cyber_worm_os_(other.cyber_worm_os_),
		cyber_worm_name_(other.cyber_worm_name_),
		cyber_worm_dormancy_time_(other.cyber_worm_dormancy_time_)
		{}


const std::string CyberWorm::getName()
{
		return cyber_worm_name_;
}

const std::string CyberWorm::getOs()
{
	return cyber_worm_os_;
}

const int CyberWorm::getTime()
{
	return cyber_worm_dormancy_time_;
}

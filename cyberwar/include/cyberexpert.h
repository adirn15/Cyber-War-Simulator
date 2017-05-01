#ifndef CYBER_EXPERT
#define CYBER_EXPERT
#include <iostream>
#include <string>
#include <vector>
#include "../include/cyberpc.h"


class CyberExpert
{
private:
	const std::string 	cyber_expert_name_;
    const int cyber_expert_work_time_;
    const int cyber_expert_rest_time_;
    const int cyber_expert_efficiency_;
    int workOrRest;
    CyberExpert(); // Prevent the use of an empty constructor
	// Add your own variables here
 
public:
    ~CyberExpert();
    bool isActive();
    const int getRestTime();
    const std::string getName();
    int getWorkOrRest();
    void setWorkOrRest(int num);
    const int getWorkTime();
    const int getEfficiency();
    CyberExpert(std::string cyber_expert_name, int cyber_expert_work_time, int cyber_expert_rest_time, int cyber_expert_efficiency);
 	void Clean(CyberPC & cyber_pc); 
	// Add your own functions here
};


#endif

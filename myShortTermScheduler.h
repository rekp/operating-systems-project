// File: myShortTermScheduler.h
// Author: Patrick Rek
// Date : Summer 2014
// Last Updated by: Patrick Rek 27/09/15
// Description: short term scheduler class for simulated operating system.

#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

#include "myRAM.h"
#include "Job.h"

#ifndef _myShortTermScheduler
#define _myShortTermScheduler

class myShortTermScheduler
{
	public:

		int readyQueueSize; // what is the size restriction on the ReadyQueue?
		std::vector<Job> stsList;
			int jobCount;
			int instructionCount;

		myShortTermScheduler()
		{
			readyQueueSize = 100;
		}
		myShortTermScheduler(int a)
		{
			readyQueueSize = a;
		}

		void readRAM(myRAM ram);
	
//		Will calculate stsList (from start to finish) the maximum amount of jobs that can be exported while staying below the Ready Queue limit. Excluded jobs will be left in the list.		//
		std::vector<Job> exportList();

		void print();
};
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////
void myShortTermScheduler::readRAM(myRAM ram)
{
	stsList = ram.getJobList();
	jobCount = stsList.size();
	instructionCount = 0;

	for(unsigned int i = 0; i < stsList.size(); i++)
	{
		
		instructionCount = instructionCount + stsList.at(i).size;
		
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<Job> myShortTermScheduler::exportList()
{
	std::vector<Job> temp;
	temp = stsList;
	int tempInstructionCount = instructionCount;
	int tempJobCount = jobCount;

	//std::cout << "\nShort Term Scheduler List being exported into Ready Queue, please wait..." << std::endl;

	if(tempInstructionCount > readyQueueSize)
	{
		while(tempInstructionCount > readyQueueSize)
		{
			tempInstructionCount = tempInstructionCount - temp.at(jobCount - 1).size;
			temp.erase(temp.begin() + (jobCount - 1));
			--jobCount;
		}

		stsList.erase(stsList.begin(), stsList.begin() + (jobCount));
		jobCount = stsList.size();
		instructionCount = instructionCount - tempInstructionCount;

		//std::cout << "Short Term Scheduler List has " << jobCount << " jobs left\n" << std::endl;

	}
	else if(tempInstructionCount <= readyQueueSize)
	{
		//std::cout << "Short Term Scheduler List has NO jobs left\n" << std::endl;
	}
	return temp;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void myShortTermScheduler::print()
{
	std::cout << "-----Job List: Short Term Scheduler-----\n" << std::endl;
	
	for(unsigned int i = 0; i < stsList.size(); i++)
	{
		stsList.at(i).print();
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
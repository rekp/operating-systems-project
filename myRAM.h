// File: myRAM.h
// Author: Patrick Rek
// Date : Summer 2014
// Last Updated by: Patrick Rek 27/09/15
// Description: RAM class for simulated operating system.

#pragma once
#include <queue>
#include <iostream>
#include <vector>
#include "Job.h"

#ifndef _myRAM
#define _myRAM

class myRAM
{
	public:

		std::vector<Job> jobRAM;
		int jobCount;
		int instructionCount;
		int size;
		
		myRAM()
		{
			jobCount = 0;
			instructionCount = 0;
			size = 100;
		}
		myRAM(int a)
		{
			jobCount = 0;
			instructionCount = 0;
			size = a;
		}

		void add(Job x);
		void remove();
		void print();
		void clearRAM();
		std::vector<Job> getJobList();
		Job exportJob();
		int getInstructionCount();
		bool isEmpty();
};
#endif

void myRAM::add(Job x)
{
	if((x.size + instructionCount) < size)
	{
		jobRAM.push_back(x);
		jobCount++;
		instructionCount = instructionCount + x.size;
	}
	else if((x.size + instructionCount) >= size) // ram size restriction, doubles as a check if the LTS is sorting properly
	{
		//std::cout << "ERROR: RAM is at capacity (" << size << ")" << std::endl;
	}
}

void myRAM::remove() // STILLL NEEEDS TO BE LOOKED AT
{
	/*jobRAM.erase(jobRAM.begin(),jobRAM.begin()+1);*/
	jobCount--;
}

void myRAM::print()
{
	std::cout << "----Job List: in RAM----" << std::endl;
	
	for(unsigned int i = 0; i < jobRAM.size(); i++)
	{
		jobRAM.at(i).print();
	}
}
void myRAM::clearRAM()
{
	std::vector<Job> tempList;
	jobRAM = tempList;

	jobCount = 0;
	instructionCount = 0;
	//std::cout << "\nRAM has been CLEARED" << std::endl;
}
std::vector<Job> myRAM::getJobList()
{
	std::vector<Job> tempList;
	tempList = jobRAM;
	clearRAM();

	return tempList;
}
Job myRAM::exportJob()
{
	std::vector<Job> tempList;
	tempList = jobRAM;

	return tempList.front();
}
int myRAM::getInstructionCount()
{
	return instructionCount;
}
bool myRAM::isEmpty()
{
	if(jobCount == 0)
		return 1;
	else if(jobCount > 0)
		return 0;
	else
	{
		std::cout << "Error: Job Count in myReadyQueue can't be less than 0" << std::endl;
		return 1;
	}
}
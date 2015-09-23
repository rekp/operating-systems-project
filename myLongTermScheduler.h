#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "myHardDrive.h"
#include "myRAM.h"
#include "Job.h"

#ifndef _myLongTermScheduler
#define _myLongTermScheduler

class myLongTermScheduler
{
	public:
		int ramSize;

		std::vector<Job> fifoList;
			int fifoJobCount;
			int fifoInstructionCount;

		std::vector<Job> sjfList;
			int sjfJobCount;
			int sjfInstructionCount;

		std::vector<Job> priorityList;
			int priorityJobCount;
			int priorityInstructionCount;

		myLongTermScheduler()
		{
			ramSize = 100;

			fifoJobCount = 0;
			fifoInstructionCount = 0;

			sjfJobCount = 0;
			sjfInstructionCount = 0;

			priorityJobCount = 0;
			priorityInstructionCount = 0;
		}
		myLongTermScheduler(int rs)
		{
			ramSize = rs;

			fifoJobCount = 0;
			fifoInstructionCount = 0;

			sjfJobCount = 0;
			sjfInstructionCount = 0;

			priorityJobCount = 0;
			priorityInstructionCount = 0;
		}

		void FIFO(myHardDrive drive);
		void SJF(myHardDrive drive);
		void Priority(myHardDrive drive);

//		All export methods will calculate each list (from start to finish) the maximum amount of jobs that can be exported while staying below the RAM limit. Excluded jobs will be left in the list.		//
		std::vector<Job> exportFIFO();
		std::vector<Job> exportSJF();
		std::vector<Job> exportPriority();

		void printFIFO();
		void printSJF();
		void printPriority();
};
#endif

bool bySize(const Job & s1, const Job & s2)
{  
	return s1.size < s2.size;
}

bool byPriority(const Job & s1, const Job & s2)
{
	return s1.priority > s2.priority;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void myLongTermScheduler::FIFO(myHardDrive drive)
{
	fifoList = drive.getJobList();
	fifoJobCount = fifoList.size();
	fifoInstructionCount = 0;

	for(unsigned int i = 0; i < fifoList.size(); i++)
	{
		fifoInstructionCount = fifoInstructionCount + fifoList.at(i).size;
	}
}
void myLongTermScheduler::SJF(myHardDrive drive)
{
	sjfList = drive.getJobList();
	sjfJobCount = fifoList.size();
	sjfInstructionCount = 0;

	for(unsigned int i = 0; i < sjfList.size(); i++)
	{
		sjfInstructionCount = sjfInstructionCount + sjfList.at(i).size;
	}

	std::sort (sjfList.begin(), sjfList.end(), bySize);
}
void myLongTermScheduler::Priority(myHardDrive drive)
{
	priorityList = drive.getJobList();
	priorityJobCount = fifoList.size();
	priorityInstructionCount = 0;

	for(unsigned int i = 0; i < priorityList.size(); i++)
	{
		priorityInstructionCount = priorityInstructionCount + priorityList.at(i).size;
	}

	std::sort (priorityList.begin(), priorityList.end(), byPriority);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<Job> myLongTermScheduler::exportFIFO()
{
	std::vector<Job> temp;
	temp = fifoList;
	int tempInstructionCount = fifoInstructionCount;
	int tempJobCount = fifoJobCount;

	//std::cout << "\nFIFO List being exported into RAM, please wait..." << std::endl;

	if(tempInstructionCount > ramSize || temp.size() == 1)
	{
		while(tempInstructionCount > ramSize)
		{
			tempInstructionCount = tempInstructionCount - temp.at(fifoJobCount - 1).size;
			temp.erase(temp.begin() + (fifoJobCount - 1));
			--fifoJobCount;
		}

		fifoList.erase(fifoList.begin(), fifoList.begin() + (fifoJobCount));
		fifoJobCount = fifoList.size();
		fifoInstructionCount = fifoInstructionCount - tempInstructionCount;

		//std::cout << "FIFO List has " << fifoJobCount << " jobs left\n" << std::endl;

	}
	else if(tempInstructionCount <= ramSize)
	{
		//std::cout << "FIFO List has NO jobs left\n" << std::endl;
	}
	return temp;
}

std::vector<Job> myLongTermScheduler::exportSJF()
{
	std::vector<Job> temp;
	temp = sjfList;
	int tempInstructionCount = sjfInstructionCount;
	int tempJobCount = sjfJobCount;

	//std::cout << "\nSJF List being exported into RAM, please wait..." << std::endl;
	//if(!temp.empty())
	//{
	if(tempInstructionCount > ramSize || temp.size() == 1)
	{
		while(tempInstructionCount > ramSize)
		{
			tempInstructionCount = tempInstructionCount - temp.at(sjfJobCount - 1).size;
			temp.erase(temp.begin() + (sjfJobCount - 1));
			--sjfJobCount;
		}

		sjfList.erase(sjfList.begin(), sjfList.begin() + (sjfJobCount));
		sjfJobCount = sjfList.size();
		sjfInstructionCount = sjfInstructionCount - tempInstructionCount;

		//std::cout << "SJF List has " << sjfJobCount << " jobs left\n" << std::endl;

	}
	//}
	else if(tempInstructionCount <= ramSize)
	{
		std::cout << "SJF List has NO jobs left\n" << std::endl;
	}
	return temp;
}

std::vector<Job> myLongTermScheduler::exportPriority()
{
	std::vector<Job> temp;
	temp = priorityList;
	int tempInstructionCount = priorityInstructionCount;
	int tempJobCount = priorityJobCount;

	//std::cout << "\nPriority List being exported into RAM, please wait..." << std::endl;

	if(tempInstructionCount > ramSize || temp.size() == 1)
	{
		while(tempInstructionCount > ramSize)
		{
			tempInstructionCount = tempInstructionCount - temp.at(priorityJobCount - 1).size;
			temp.erase(temp.begin() + (priorityJobCount - 1));
			--priorityJobCount;
		}

		priorityList.erase(priorityList.begin(), priorityList.begin() + (priorityJobCount));
		priorityJobCount = priorityList.size();
		priorityInstructionCount = priorityInstructionCount - tempInstructionCount;

		//std::cout << "Priority List has " << priorityJobCount << " jobs left\n" << std::endl;

	}
	else if(tempInstructionCount <= ramSize)
	{
		//std::cout << "Priority List has NO jobs left\n" << std::endl;
	}
	return temp;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void myLongTermScheduler::printFIFO()
{
	std::cout << "-----Job List: First In First Out-----\n" << std::endl;
	
	for(unsigned int i = 0; i < fifoList.size(); i++)
	{
		fifoList.at(i).print();
	}
}

void myLongTermScheduler::printSJF()
{
	std::cout << "-----Job List: Shortest Job First-----\n" << std::endl;
	
	for(unsigned int i = 0; i < sjfList.size(); i++)
	{
		sjfList.at(i).print();
	}
}

void myLongTermScheduler::printPriority()
{
	std::cout << "-----Job List: Priority-----\n" << std::endl;
	
	for(unsigned int i = 0; i < priorityList.size(); i++)
	{
		priorityList.at(i).print();
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
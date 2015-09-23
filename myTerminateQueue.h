#pragma once
#include <queue>
#include <iostream>
#include "Job.h"

#ifndef _myTerminateQueue
#define _myTerminateQueue

class myTerminateQueue
{
	public:
		
		std::queue<Job> terminateQ;
		int jobCount;
		int readyCheck;
		
		myTerminateQueue()
		{
			jobCount = 0;
			readyCheck = 0;
		}

		int getReadyCheck();

		void add(Job x);
		void remove();
		void print();
		void printWaitTimes();
		void clearQueue();
		void jobPlus();
		int getJobCount();
		Job exportJob();
		void peakNext();
		bool isEmpty();
};
#endif

void myTerminateQueue::add(Job x)
{
		terminateQ.push(x);
		jobCount++;
}

void myTerminateQueue::remove() // Removes next element in terminateQ
{
	terminateQ.pop();
	readyCheck = 0;
	jobCount--;
}

void myTerminateQueue::print()
{
	std::queue<Job> tempQ;
	tempQ = terminateQ;

	std::cout << "----Job List: in terminateQ----" << std::endl;
	
	while (!tempQ.empty())
  {
    tempQ.front().print();
    tempQ.pop();
  }
}
void myTerminateQueue::printWaitTimes()
{
	std::queue<Job> tempQ;
	tempQ = terminateQ;

	std::cout << "\n----Wait Times----" << std::endl;
	
	while (!tempQ.empty())
  {
    tempQ.front().printWaitTimes();
    tempQ.pop();
  }
}
void myTerminateQueue::clearQueue()
{
	std::queue<Job> empty;

	std::swap(terminateQ,empty);
	jobCount = 0;
	//std::cout << "\nTerminate Queue has been CLEARED" << std::endl;
}
int myTerminateQueue::getReadyCheck()
{
	return readyCheck;
}
void myTerminateQueue::jobPlus()
{
	jobCount++;
}
int myTerminateQueue::getJobCount()
{
	return jobCount;
}
Job myTerminateQueue::exportJob()
{
	std::queue<Job> tempQ;
	tempQ = terminateQ;
	remove();

	return tempQ.front();
}
void myTerminateQueue::peakNext()
{
	std::cout << "Job: " << terminateQ.front().number << "  Instructions: " << terminateQ.front().size << "  Priority: " << terminateQ.front().priority << std::endl;
}
bool myTerminateQueue::isEmpty()
{
	if(jobCount == 0)
		return 1;
	else if(jobCount > 0)
		return 0;
	else
	{
		std::cout << "Error: Job Count in myTerminateQueue can't be less than 0" << std::endl;
		return 1;
	}
}
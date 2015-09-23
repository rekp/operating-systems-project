#pragma once
#include <queue>
#include <iostream>
#include <queue>  
#include "Job.h"

#ifndef _myReadyQueue
#define _myReadyQueue

class myReadyQueue
{
	public:
		
		std::queue<Job> rdyQ;
		int jobCount;
		int instructionCount;
		int size;

		myReadyQueue()
		{
			jobCount = 0;
			instructionCount = 0;
			size = 100;
	
		}
		myReadyQueue(int a)
		{
			jobCount = 0;
			instructionCount = 0;
			size = a;
		}

		void add(Job x);
		void remove();
		void print();
		void clearQueue();
		int getJobCount();
		Job exportJob();
		void peakNext();
		bool isEmpty();
		void allWait();
};
#endif
void myReadyQueue::allWait()
{
	std::queue<Job> tempQ;
	std::queue<Job> tempQ2;
	tempQ = rdyQ;

	while (!tempQ.empty())
  {
    tempQ.front().totalWaitTime ++;
	tempQ2.push(tempQ.front());
    tempQ.pop();
  }
	rdyQ = tempQ2;
}

void myReadyQueue::add(Job x)
{
		rdyQ.push(x);
		jobCount++;
}

void myReadyQueue::remove() // Removes next element in rdyQ
{
	if(isEmpty())
	{
		
	}
	else
	{
		rdyQ.pop();
		
		jobCount--;
	}
}

void myReadyQueue::print()
{
	std::queue<Job> tempQ;
	tempQ = rdyQ;

	std::cout << "----Job List: in rdyQ----" << std::endl;
	
	while (!tempQ.empty())
  {
    tempQ.front().print();
    tempQ.pop();
  }

}
void myReadyQueue::clearQueue()
{
	std::queue<Job> empty;

	std::swap(rdyQ,empty);
	jobCount = 0;
	instructionCount = 0;
	std::cout << "\nReady Queue has been CLEARED" << std::endl;
}
int myReadyQueue::getJobCount()
{
	return jobCount;
}
Job myReadyQueue::exportJob()
{
	std::queue<Job> tempQ;
	tempQ = rdyQ;
	remove();

	return tempQ.front();
}
void myReadyQueue::peakNext()
{
	std::cout << "Job: " << rdyQ.front().number << "  Instructions: " << rdyQ.front().size << "  Priority: " << rdyQ.front().priority /*<<" **********Counter= " << rdyQ.front().counter*/ << std::endl;
}
bool myReadyQueue::isEmpty()
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
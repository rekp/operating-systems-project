// File: myIOQueue.h
// Author: Patrick Rek
// Date : Summer 2014
// Last Updated by: Patrick Rek 27/09/15
// Description: io queue class for simulated operating system.

#pragma once
#include <queue>
#include <iostream>
#include <queue>  
#include "Job.h"

#ifndef _myIOQueue
#define _myIOQueue

class myIOQueue
{
	public:
		
		std::queue<Job> ioQ;
		int jobCount;
		int readyCheck;
		int ticks;
		
		myIOQueue()
		{
			jobCount = 0;
			readyCheck = 0;
			ticks = 0;
		}

		void ready(int ticks);
		int getReadyCheck();

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

void myIOQueue::allWait()
{
	std::queue<Job> tempQ;
	std::queue<Job> tempQ2;
	tempQ = ioQ;

	while (!tempQ.empty())
  {
    tempQ.front().totalWaitTime ++;
	tempQ2.push(tempQ.front());
    tempQ.pop();
  }
	ioQ = tempQ2;
}

void myIOQueue::ready(int ticks)
{
	std::queue<Job> tempQ;
	tempQ = ioQ;
	
  while (!tempQ.empty())
  {
	  if(tempQ.front().getWaitTime() >= ticks)
	  {
		  readyCheck = 1;
	  }
    tempQ.front();
    tempQ.pop();
  }
}

void myIOQueue::add(Job x)
{
	std::queue<Job> tempQ;
	tempQ = ioQ;

	ioQ.push(x);
	jobCount++;
}

void myIOQueue::remove() // Removes next element in ioQ
{
	if(isEmpty())
	{
		
	}
	else
	{
		ioQ.pop();
		readyCheck = 0;
		jobCount--;
	}
}

void myIOQueue::print()
{
	std::queue<Job> tempQ;
	tempQ = ioQ;

	std::cout << "----Job List: in ioQ----" << std::endl;
	
	while (!tempQ.empty())
  {
    tempQ.front().print();
    tempQ.pop();
  }
}
void myIOQueue::clearQueue()
{
	std::queue<Job> empty;

	std::swap(ioQ,empty);
	jobCount = 0;
	std::cout << "\nWait Queue has been CLEARED" << std::endl;
}
int myIOQueue::getReadyCheck()
{
	return readyCheck;
}
int myIOQueue::getJobCount()
{
	return jobCount;
}
Job myIOQueue::exportJob()
{
	std::queue<Job> tempQ;
	tempQ = ioQ;
	remove();

	return tempQ.front();
}
void myIOQueue::peakNext()
{
	std::cout << "Job: " << ioQ.front().number << "  Instructions: " << ioQ.front().size << "  Priority: " << ioQ.front().priority << std::endl;
}
bool myIOQueue::isEmpty()
{
	if(jobCount == 0)
		return 1;
	else if(jobCount > 0)
		return 0;
	else
	{
		std::cout << "Error: Job Count in myIOQueue can't be less than 0" << std::endl;
		return 1;
	}
}
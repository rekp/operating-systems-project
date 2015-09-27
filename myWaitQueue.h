// File: myWaitQueue.h
// Author: Patrick Rek
// Date : Summer 2014
// Last Updated by: Patrick Rek 27/09/15
// Description: Wait queue class for simulated operating system.

#pragma once
#include <queue>
#include <iostream>
#include <queue>  
#include "Job.h"

#ifndef _myWaitQueue
#define _myWaitQueue

class myWaitQueue
{
	public:
		
		std::queue<Job> waitQ;
		int jobCount;
		int readyCheck;
		int ticks;
		
		myWaitQueue()
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

void myWaitQueue::allWait()
{
	std::queue<Job> tempQ;
	std::queue<Job> tempQ2;
	tempQ = waitQ;

	while (!tempQ.empty())
  {
    tempQ.front().totalWaitTime ++;
	tempQ2.push(tempQ.front());
    tempQ.pop();
  }
	waitQ = tempQ2;
}

void myWaitQueue::ready(int ticks)
{
	std::queue<Job> tempQ;
	tempQ = waitQ;
	
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

void myWaitQueue::add(Job x)
{
	std::queue<Job> tempQ;
	tempQ = waitQ;

	waitQ.push(x);
	jobCount++;
}

void myWaitQueue::remove() // Removes next element in waitQ
{
	if(isEmpty())
	{
		
	}
	else
	{
		waitQ.pop();
		readyCheck = 0;
		jobCount--;
	}
}

void myWaitQueue::print()
{
	std::queue<Job> tempQ;
	tempQ = waitQ;

	std::cout << "----Job List: in waitQ----" << std::endl;
	
	while (!tempQ.empty())
  {
    tempQ.front().print();
    tempQ.pop();
  }

}
void myWaitQueue::clearQueue()
{
	std::queue<Job> empty;

	std::swap(waitQ,empty);
	jobCount = 0;
	std::cout << "\nWait Queue has been CLEARED" << std::endl;
}
int myWaitQueue::getReadyCheck()
{
	return readyCheck;
}
int myWaitQueue::getJobCount()
{
	return jobCount;
}
Job myWaitQueue::exportJob()
{
	std::queue<Job> tempQ;
	tempQ = waitQ;
	remove();

	return tempQ.front();
}
void myWaitQueue::peakNext()
{
	std::cout << "Job: " << waitQ.front().number << "  Instructions: " << waitQ.front().size << "  Priority: " << waitQ.front().priority << std::endl;
}
bool myWaitQueue::isEmpty()
{
	if(jobCount == 0)
		return 1;
	else if(jobCount > 0)
		return 0;
	else
	{
		std::cout << "Error: Job Count in myWaitQueue can't be less than 0" << std::endl;
		return 1;
	}
}
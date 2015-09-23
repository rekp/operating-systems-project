#pragma once
#include <vector>
#include <string>
#include <iostream>

#ifndef _Job
#define _Job

class Job
{
	public:
		int number;
		int size;
		int priority;
		int counter;
		int waitTime;
		int totalWaitTime;

		int wasPaused;
		int wait;
		int io;

		std::vector<std::string> instructions;

		int registerValueA;
		int registerValueB;
		int registerValueC;
		int registerValueD;
		int accumulatorValue;

		Job()
		{
			number = 0;
			size = 0;
			priority = 0;
			wasPaused = 0;
			counter = 0;

			registerValueA = 0;
			registerValueB = 0;
			registerValueC = 0;
			registerValueD = 0;
			accumulatorValue = 0;

		}

		Job(int n, int s, int p)
		{
			number = n;
			size = s;
			priority = p;
			wasPaused = 0;
			counter = 0;
			totalWaitTime = 0;

			registerValueA = 0;
			registerValueB = 0;
			registerValueC = 0;
			registerValueD = 0;
			accumulatorValue = 0;
		}

		void setNumber(int a);
		void setSize(int b);
		int getSize();
		int getNumber();
		void setPriority(int c);
		void setCounter(int d);
		void setWaitTime(int w);
		void setWait(int w);
		void setIO(int w);



		void setValues(int f, int g, int h, int j, int k);
		int getValueA();
		int getValueB();
		int getValueC();
		int getValueD();
		int getAccumulatorValue();
		int getTotalWaitTime();

		int getWaitTime();
		int getWait();
		int getIO();

		int getCounter();
		void incrementCounter();
		
		void setWasPaused(int e);
		int getWasPaused();
		void add(std::string);
		void list();
		void print();
		void printWaitTimes();
		std::string getInstruction(int line);
};
#endif

void Job::setNumber(int a)
{
	number = a;
}

void Job::setSize(int b)
{
	size = b;
}
int Job::getSize()
{
	return size;
}
void Job::setPriority(int c)
{
	priority = c;
}
void Job::setCounter(int d)
{
	counter = d;
}
void Job::setWaitTime(int w)
{
	waitTime = w;
}
void Job::setWait(int w)
{
	wait = w;
}
void Job::setIO(int w)
{
	io = w;
}
int Job::getWait()
{
	return wait;
}
int Job::getIO()
{
	return io;
}
int Job::getWaitTime()
{
	return waitTime;
}
int Job::getCounter()
{
	return counter;
}
int Job::getNumber()
{
	return number;
}
void Job::setWasPaused(int e)
{
	wasPaused = e;
}
void Job::setValues(int f, int g, int h, int j, int k)
{
	registerValueA = f;
	registerValueB = g;
	registerValueC = h;
	registerValueD = j;
	accumulatorValue = k;
}
int Job::getValueA()
{
	return registerValueA;
}
int Job::getValueB()
{
	return registerValueB;
}
int Job::getValueC()
{
	return registerValueC;
}
int Job::getValueD()
{
	return registerValueD;
}
int Job::getAccumulatorValue()
{
	return accumulatorValue;
}
int Job::getTotalWaitTime()
{
	return totalWaitTime;
}
int Job::getWasPaused()
{
	return wasPaused;
}

void Job::add(std::string x)
{
	instructions.push_back(x);
}

void Job::list()
{
	for(std::vector<std::string>::const_iterator iter = instructions.begin(); iter != instructions.end(); ++iter)
	{
		std::cout << *iter << std::endl;
	}
}

void Job::print()
{
	std::cout << "Job: " << number << "  Instructions: " << size << "  Priority: " << priority << std::endl;

	for(std::vector<std::string>::const_iterator iter = instructions.begin(); iter != instructions.end(); ++iter)
	{
		std::cout << *iter << std::endl;
	}
}
void Job::printWaitTimes()
{
	std::cout << "Job: " << number << "  Wait Time: " << getTotalWaitTime() << std::endl;
}
std::string Job::getInstruction(int line)
{
	return instructions.at(line);
}
void Job::incrementCounter()
{
	counter++;
}
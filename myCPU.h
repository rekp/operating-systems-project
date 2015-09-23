#pragma once
#include <queue>
#include <iostream>
#include <vector>
#include "Job.h"
#include "myWaitQueue.h"
#include "myIOQueue.h"
#include "myTerminateQueue.h"

#ifndef _myCPU
#define _myCPU

class myCPU
{
	public:
		Job currentJob;
		myTerminateQueue tQ;

		int currentInstruction;

		int registerA;
		int registerB;
		int registerC;
		int registerD;
		int*r1;
		int*r2;

		int accumulator;
		int interuptCheck;
		int flag;
		int cpuTicks;
		
		myCPU()
		{
			currentInstruction = 0;
			registerA = 1;
			registerB = 3;
			registerC = 5;
			registerD = 7;
			accumulator = 9;
			interuptCheck = 0;
			flag = 0;
			cpuTicks = 0;
		}
		myCPU(int a)
		{
			currentInstruction = 0;
			registerA = 1;
			registerB = 3;
			registerC = 5;
			registerD = 7;
			accumulator = 9;
			interuptCheck = 0;
			flag = 0;
			cpuTicks = 0;
		}

		void continueJob();
		void runJob(Job x);
		void run(std::string a, std::string b , std::string c, int arg);

		int addOperation(int*a, int*b);
		int subOperation(int*a, int*b);
		int mulOperation(int*a, int*b);
		int divOperation(int*a, int*b);
		void _rdOperation(int arg);
		void _wrOperation(int arg);
		void _wtOperation(int arg);
		void stoOperation(int a);
		void rclOperation(int*a);

		void exportJobWait(myWaitQueue wait);
		void exportJobIO(myIOQueue io);
		myTerminateQueue exportTerminate();
		
		void resetCPU();
		int getInteruptCheck();
		void resetInteruptCheck();
		Job exportJob();
		int getCPUTicks();
		void remove();
		void print();
		void clearRAM();
};
#endif
void myCPU::continueJob()
{
	runJob(currentJob);
}

void myCPU::runJob(Job x)
{
	currentJob = x;
	
	flag = 1;
	
	std::string instruction = "";

	std::string instructionNumber = "";
	std::string opp = "";
	std::string r1 = "";
	std::string r2 = "";
	std::string argumentThing = "";
	int temp;
	
	if(currentJob.getCounter() < currentJob.getSize())
	{
		if(interuptCheck == 1)
		{
			flag = 0;
			interuptCheck = 0;
			return;
		}
	
		if (currentJob.getCounter() == 0)
		{
			resetCPU();
		}
		else if(currentJob.getWasPaused() == 1)
		{
			registerA = currentJob.getValueA();
			registerB = currentJob.getValueB();
			registerC = currentJob.getValueC();
			registerD = currentJob.getValueD();
			accumulator = currentJob.getAccumulatorValue();
			currentJob.setWasPaused(0);
			currentJob.setWait(0);
			currentJob.setIO(0);
			currentJob.setWaitTime(0);
		}
		
		instruction = currentJob.getInstruction(currentJob.getCounter());
		
		if(currentJob.getCounter() <= 9)
		{
			instructionNumber = instruction.substr(0,1);
			opp = instruction.substr(3,3);
			r1 = instruction.substr(8,1);
			r2 = instruction.substr(11,1);
			argumentThing = instruction.substr(14,2);
			temp = atoi(argumentThing.c_str());
			currentInstruction = currentJob.getCounter();
		}
		else if (currentJob.getCounter() > 9)
		{
			instructionNumber = instruction.substr(0,2);
			opp = instruction.substr(4,3);
			r1 = instruction.substr(9,1);
			r2 = instruction.substr(12,1);
			argumentThing = instruction.substr(15,2);
			temp = atoi(argumentThing.c_str());
			currentInstruction = currentJob.getCounter();
		}
		
		
		//std::cout << "--Running job " << currentJob.getNumber()<< std::endl;
		

		/*std::cout << instructionNumber << std::endl;
		std::cout << opp << std::endl;
		std::cout << r1 << std::endl;
		std::cout << r2 << std::endl;
		std::cout << temp << std::endl;*/
			
		
		run(opp,r1,r2,temp);
	}	
}

void myCPU::run(std::string a, std::string b , std::string c, int arg)
{
	std::string opperation = a;
	std::string reg1 = b;
	std::string reg2 = c;
	int argument = arg;

	if(reg1 == "A")
	{
		r1 = &registerA;
	}
	else if(reg1 == "B")
	{
		r1 = &registerB;
	}
	else if(reg1 == "C")
	{
		r1 = &registerC;
	}
	else if(reg1 == "D")
	{
		r1 = &registerD;
	}
	else
	{
		std::cout << "ERROR01: Register "<< reg1 <<" not found." << std::endl;
		currentJob.incrementCounter();
		cpuTicks ++;
		return;
	}
/////////////////////////////////////////////////////////////////////////////////////////
	if(reg2 == "A")
	{
		r2 = &registerA;
	}
	else if(reg2 == "B")
	{
		r2 = &registerB;
	}
	else if(reg2 == "C")
	{
		r2 = &registerC;
	}
	else if(reg2 == "D")
	{
		r2 = &registerD;
	}
	else
	{
		std::cout << "ERROR02: Register "<< reg2 <<" not found." << std::endl;
		currentJob.incrementCounter();
		cpuTicks ++;
		return;
	}
/////////////////////////////////////////////////////////////////////////////////////////
	if(opperation == "add")
	{
		accumulator = accumulator + addOperation(r1, r2);
	}
	else if(opperation == "sub")
	{
		accumulator = accumulator + subOperation(r1, r2);
	}
	else if(opperation == "mul")
	{
		accumulator = accumulator + mulOperation(r1, r2);
	}
	else if(opperation == "div")
	{
		accumulator = accumulator + divOperation(r1, r2);
	}
	else if(opperation == "_rd")
	{
		_rdOperation(arg);
	}
	else if(opperation == "_wr")
	{
		_wrOperation(arg);
	}
	else if(opperation == "_wt")
	{
		_wtOperation(arg);
	}
	else if(opperation == "sto")
	{
		stoOperation(argument);
	}
	else if(opperation == "rcl")
	{
		rclOperation(r1);
	}
	else
	{
		std::cout << "ERROR: Opperation "<< opperation <<" not found." << std::endl;
		currentJob.incrementCounter();
		cpuTicks ++;
		return;
	}
	
	currentJob.incrementCounter();
	cpuTicks ++;
	if(currentJob.getSize() - 1  == currentInstruction)
	{
		flag = 0;
		std::cout << "Job " << currentJob.getNumber() << "_____________________Complete___________________________ Accumulator = " << accumulator << std::endl;
		tQ.add(currentJob);
	}
}
int myCPU::addOperation(int*a, int*b)
{
	int temp = *a + *b;
	return temp;
}
int myCPU::subOperation(int*a, int*b)
{
	int temp = *a - *b;
	return temp;
}
int myCPU::mulOperation(int*a, int*b)
{
	int temp = (*a) * (*b);
	return temp;
}
int myCPU::divOperation(int*a, int*b)
{
	int temp = *a / *b;
	return temp;
}
void myCPU::_rdOperation(int arg)
{
	currentJob.setWaitTime(arg);
	currentJob.setIO(1);
	interuptCheck = 1;
	
}
void myCPU::_wrOperation(int arg)
{
	currentJob.setWaitTime(arg);
	currentJob.setIO(1);
	interuptCheck = 1;
	
}
void myCPU::_wtOperation(int arg)
{
	currentJob.setWaitTime(arg);
	currentJob.setWait(1);
	interuptCheck = 1;
	
}
void myCPU::stoOperation(int a)
{
	accumulator = a;
}
void myCPU::rclOperation(int*a)
{
	*a = accumulator;
}
int myCPU::getCPUTicks()
{
	return cpuTicks;
}
int myCPU::getInteruptCheck()
{
	return interuptCheck;
}
void myCPU::resetInteruptCheck()
{
	interuptCheck = 0;
}
Job myCPU::exportJob()
{
	currentJob.setValues(registerA,registerB,registerC,registerD,accumulator);
	currentJob.setWasPaused(1);
	flag = 0;
	//resetCPU();
	return currentJob;
}
myTerminateQueue myCPU::exportTerminate()
{
	myTerminateQueue temp;
	myTerminateQueue temp2;
	temp = tQ;
	tQ = temp2;

	return temp;
}

void myCPU::resetCPU()
{
	registerA = 1;
	registerB = 3;
	registerC = 5;
	registerD = 7;
	accumulator = 9;
}

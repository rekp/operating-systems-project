// File: myHardDrive.h
// Author: Patrick Rek
// Date : Summer 2014
// Last Updated by: Patrick Rek 27/09/15
// Description: Hard drive class for simulated operating system.

#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include "Job.h"

#ifndef _myHardDrive
#define _myHardDrive

class myHardDrive
{
	public:
		std::vector<Job> jobList;
		std::vector<std::string> jobListRaw; // debug vector
		int jobCount;

		myHardDrive()
		{
			jobCount = 0;
		}
		
		void loadJobs(std::string txt);
		void loadJobsRaw(std::string txt); // text document loaded line by line into vector<string>; debug method
		void listJobs();
		void listJobsRaw();				   // debug method
		std::vector<Job> getJobList();
		bool isEmpty();
		
};
#endif

void myHardDrive::loadJobs(std::string txt)
{
	std::ifstream infile(txt);
	std::cout << "Loading Jobs onto Hard Drive, please wait... \n" << std::endl;
	std::string s;
	//infile >> std::ws;

	int size;
	int priority;
	
	while (!infile.eof())
	{
		Job temp(-1,-1,-1);

		for( int i = 0; i < 3; i++)
		{
			if(i == 0) // ignore job number
			{
				getline(infile,s,',');
			}
			else if(i == 1)
			{
				getline(infile,s,',');
				size = atoi(s.c_str());;
				if ( size == 0) // prevents "ghost" job at the end of list
					return;
			}
			else if (i == 2)
			{
				getline(infile,s);
				priority = atoi(s.c_str());
				temp.setNumber(jobCount);
				temp.setSize(size);
				temp.setPriority(priority);
				
			}
		}
		for (int i = 0; i < size; i++)
		{
			getline(infile,s);
			temp.add(s);	
		}
		jobList.push_back(temp);
		jobCount++;	
	}
	infile.close();
}

void myHardDrive::listJobs()
{
	std::cout << "-----Job List:-----\n" << std::endl;
	
	for(unsigned int i = 0; i < jobList.size(); i++)
	{
		jobList.at(i).print();
	}
}

void myHardDrive::loadJobsRaw(std::string txt)
{
	std::fstream infile(txt);
	std::cout << "Loading Raw Jobs onto Hard Drive, please wait... \n" << std::endl;
	std::string s;
	infile >> std::ws;

	while (!infile.eof())
	{
		getline(infile,s);
		jobListRaw.push_back(s);
	}
	infile.close();
}

void myHardDrive::listJobsRaw()
{
	std::cout << "-----Job List Raw:-----\n" << std::endl;
	
	for(std::vector<std::string>::const_iterator iter = jobListRaw.begin(); iter != jobListRaw.end(); ++iter)
	{
		std::cout << *iter << std::endl;
	}
}

std::vector<Job> myHardDrive::getJobList()
{
	return jobList;
}
bool myHardDrive::isEmpty()
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
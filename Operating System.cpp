// Operating System.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "myHardDrive.h"
#include "myLongTermScheduler.h"
#include "myRAM.h"
#include "myShortTermScheduler.h"
#include "myReadyQueue.h"
#include "myWaitQueue.h"
#include "myIOQueue.h"
#include "myTerminateQueue.h"
#include "myCPU.h"
#include "myTime.h"
#include <vector>
#include <string>

int _tmain(int argc, _TCHAR* argv[])
{
	myHardDrive hardDrive;				// no size restrictions
	myLongTermScheduler LTS(100);		// Change for different RAM SIZE
	myRAM RAM(100);						// Change for different RAM SIZE
	myShortTermScheduler STS(100);		// Change for different RAM SIZE
	myReadyQueue readyQueue(100);		// Change for different READY QUEUE SIZE
	myCPU CPU;				 
	myIOQueue ioQueue;
	myWaitQueue waitQueue;
	myTerminateQueue terminateQueue;
	myTime timeTracker;
	
	std::vector<Job> temp;
	int numberOfCores = 3;				// Change for different CPU CORES
	myCPU CPUcores[3];					// Change for different CPU CORES
	int ticks;

	std::cout << "Summer 2014 Operating System Project" << std::endl;

	hardDrive.loadJobs("ugradPart1.txt"); // Change for different instruction set
	LTS.FIFO(hardDrive);
	LTS.SJF(hardDrive);
	LTS.Priority(hardDrive);

	/*LTS.printFIFO();
	LTS.printSJF();
	LTS.printPriority();*/
	
	std::string response;
	std::string response2;
	int x = 4;

	do
	{
		terminateQueue.clearQueue();
		ticks = 0;
		do
		{
			std::cout << "\nPlease enter which algorithm you would like to run.\nFIFO\nSJF\nPRIORITY\n\n>" ;
			getline(std::cin,response);
			transform(response.begin(), response.end(), response.begin(), toupper);

			if(response == "FIFO")
				x = 1;
			else if(response == "SJF")
				x = 2;
			else if(response == "PRIORITY")
				x = 3;
			else
				x = 4;
		}while(x == 4);

		switch(x)
		{
			case 1://///////////////////////////////////////////////////////////////////////////////////////////////
				timeTracker.markStart();
				temp = LTS.exportFIFO();
				
				for(unsigned int i = 0; i < temp.size(); i++)
				{
					RAM.add(temp.at(i));
				}
				STS.readRAM(RAM);
				RAM.clearRAM();

				temp = STS.exportList();

				for(unsigned int i = 0; i < temp.size(); i++)
				{
					readyQueue.add(temp.at(i));
				}
				std::cout << "\n\nNumber of Cores: " << numberOfCores << std::endl;

				while(readyQueue.getJobCount() > 0 || terminateQueue.getJobCount() < hardDrive.jobCount) 
				{
					for(int i = 0; i < numberOfCores; i++)
					{
						if(ioQueue.ticks <= 0 && ioQueue.getJobCount() > 0)
						{
							readyQueue.add(ioQueue.exportJob());
						}
						if(waitQueue.ticks <= 0 && waitQueue.getJobCount() > 0)
						{
							readyQueue.add(waitQueue.exportJob());
						}
				
						if(CPUcores[i].getInteruptCheck() == 1)
						{
							CPUcores[i].resetInteruptCheck();
							Job jobInTransition = CPUcores[i].exportJob();

							if (jobInTransition.getCounter() >= jobInTransition.getSize())
							{
							}
							else
							{
								if(jobInTransition.getWait() == 1)
								{
									waitQueue.add(jobInTransition);
									waitQueue.ticks = jobInTransition.getWaitTime();
								}
								else if(jobInTransition.getIO() == 1)
								{
									ioQueue.add(jobInTransition);
									ioQueue.ticks = jobInTransition.getWaitTime();
								}
							}			
						}
						if(CPUcores[i].flag == 0)
						{
							if(readyQueue.getJobCount() > 0)
							{			
								Job jobInTransition2 = readyQueue.exportJob();
								if (jobInTransition2.getCounter() >= jobInTransition2.getSize())
								{
								}
								else
								{
									CPUcores[i].runJob(jobInTransition2);
								}
							}
							else if(readyQueue.getJobCount() <= 0)
							{
							}
						}
						else if(CPUcores[i].flag == 1)
						{	
							CPUcores[i].continueJob();
						}	
					}
					for(int j = 0; j < numberOfCores; j++)
					{
						myTerminateQueue tempTQ;
						tempTQ = CPUcores[j].exportTerminate();
						if(tempTQ.isEmpty())
						{
						}
						else
						{
							while(!tempTQ.isEmpty())
							{
								terminateQueue.add(tempTQ.exportJob());
							}
						}
					}

					if(ioQueue.ticks > 0)
						ioQueue.ticks = ioQueue.ticks - 1;
					if(waitQueue.ticks > 0)
						waitQueue.ticks = waitQueue.ticks - 1;		

					if(RAM.jobCount == 0 && LTS.fifoJobCount > 0)
					{					
						std::vector<Job> temp;
						temp = LTS.exportFIFO();
						for(unsigned int i = 0; i < temp.size(); i++)
						{
							RAM.add(temp.at(i));
						}
						STS.readRAM(RAM);
						RAM.clearRAM();
							
						temp = STS.exportList();
						for(unsigned int i = 0; i < temp.size(); i++)
						{
							readyQueue.add(temp.at(i));
						}					
					}
				ticks++;
				readyQueue.allWait();
				waitQueue.allWait();
				ioQueue.allWait();
				}
				timeTracker.markEnd();
				break;

			case 2:////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				timeTracker.markStart();
				temp = LTS.exportSJF();
				
				for(unsigned int i = 0; i < temp.size(); i++)
				{
					RAM.add(temp.at(i));
				}
				STS.readRAM(RAM);
				RAM.clearRAM();

				temp = STS.exportList();

				for(unsigned int i = 0; i < temp.size(); i++)
				{
					readyQueue.add(temp.at(i));
				}
				std::cout << "\n\nNumber of Cores: " << numberOfCores << std::endl;

				while(readyQueue.getJobCount() > 0 || terminateQueue.getJobCount() < hardDrive.jobCount) 
				{
					for(int i = 0; i < numberOfCores; i++)
					{
						if(ioQueue.ticks <= 0 && ioQueue.getJobCount() > 0)
						{
							readyQueue.add(ioQueue.exportJob());
						}
						if(waitQueue.ticks <= 0 && waitQueue.getJobCount() > 0)
						{
							readyQueue.add(waitQueue.exportJob());
						}
				
						if(CPUcores[i].getInteruptCheck() == 1)
						{
							CPUcores[i].resetInteruptCheck();
							Job jobInTransition = CPUcores[i].exportJob();

							if (jobInTransition.getCounter() >= jobInTransition.getSize())
							{
							}
							else
							{
								if(jobInTransition.getWait() == 1)
								{
									waitQueue.add(jobInTransition);
									waitQueue.ticks = jobInTransition.getWaitTime();
								}
								else if(jobInTransition.getIO() == 1)
								{
									ioQueue.add(jobInTransition);
									ioQueue.ticks = jobInTransition.getWaitTime();
								}
							}			
						}
						if(CPUcores[i].flag == 0)
						{
							if(readyQueue.getJobCount() > 0)
							{			
								Job jobInTransition2 = readyQueue.exportJob();
								if (jobInTransition2.getCounter() >= jobInTransition2.getSize())
								{
								}
								else
								{
									CPUcores[i].runJob(jobInTransition2);
								}
							}
							else if(readyQueue.getJobCount() <= 0)
							{
							}
						}
						else if(CPUcores[i].flag == 1)
						{	
							CPUcores[i].continueJob();
						}	
					}
					for(int j = 0; j < numberOfCores; j++)
					{
						myTerminateQueue tempTQ;
						tempTQ = CPUcores[j].exportTerminate();
						if(tempTQ.isEmpty())
						{
						}
						else
						{
							while(!tempTQ.isEmpty())
							{
								terminateQueue.add(tempTQ.exportJob());
							}
						}
					}

					if(ioQueue.ticks > 0)
						ioQueue.ticks = ioQueue.ticks - 1;
					if(waitQueue.ticks > 0)
						waitQueue.ticks = waitQueue.ticks - 1;		

					if(RAM.jobCount == 0 && LTS.sjfJobCount > 0)
					{					
						std::vector<Job> temp;
						temp = LTS.exportSJF();
						for(unsigned int i = 0; i < temp.size(); i++)
						{
							RAM.add(temp.at(i));
						}
						STS.readRAM(RAM);
						RAM.clearRAM();
							
						temp = STS.exportList();
						for(unsigned int i = 0; i < temp.size(); i++)
						{
							readyQueue.add(temp.at(i));
						}					
					}
					ticks++;
					readyQueue.allWait();
					waitQueue.allWait();
					ioQueue.allWait();
				}
				timeTracker.markEnd();
				break;

			case 3:///////////////////////////////////////////////////////////
				timeTracker.markStart();
				temp = LTS.exportPriority();

				for(unsigned int i = 0; i < temp.size(); i++)
				{
					RAM.add(temp.at(i));
				}
				STS.readRAM(RAM);
				RAM.clearRAM();

				temp = STS.exportList();

				for(unsigned int i = 0; i < temp.size(); i++)
				{
					readyQueue.add(temp.at(i));
				}
				std::cout << "\n\nNumber of Cores: " << numberOfCores << std::endl;

				while(readyQueue.getJobCount() > 0 || terminateQueue.getJobCount() < hardDrive.jobCount) 
				{
					for(int i = 0; i < numberOfCores; i++)
					{
						if(ioQueue.ticks <= 0 && ioQueue.getJobCount() > 0)
						{
							readyQueue.add(ioQueue.exportJob());
						}
						if(waitQueue.ticks <= 0 && waitQueue.getJobCount() > 0)
						{
							readyQueue.add(waitQueue.exportJob());
						}
				
						if(CPUcores[i].getInteruptCheck() == 1)
						{
							CPUcores[i].resetInteruptCheck();
							Job jobInTransition = CPUcores[i].exportJob();

							if (jobInTransition.getCounter() >= jobInTransition.getSize())
							{
							}
							else
							{
								if(jobInTransition.getWait() == 1)
								{
									waitQueue.add(jobInTransition);
									waitQueue.ticks = jobInTransition.getWaitTime();
								}
								else if(jobInTransition.getIO() == 1)
								{
									ioQueue.add(jobInTransition);
									ioQueue.ticks = jobInTransition.getWaitTime();
								}
							}			
						}
						if(CPUcores[i].flag == 0)
						{
							if(readyQueue.getJobCount() > 0)
							{			
								Job jobInTransition2 = readyQueue.exportJob();
								if (jobInTransition2.getCounter() >= jobInTransition2.getSize())
								{
								}
								else
								{
									CPUcores[i].runJob(jobInTransition2);
								}
							}
							else if(readyQueue.getJobCount() <= 0)
							{
							}
						}
						else if(CPUcores[i].flag == 1)
						{	
							CPUcores[i].continueJob();
						}	
					}
					for(int j = 0; j < numberOfCores; j++)
					{
						myTerminateQueue tempTQ;
						tempTQ = CPUcores[j].exportTerminate();
						if(tempTQ.isEmpty())
						{
						}
						else
						{
							while(!tempTQ.isEmpty())
							{
								terminateQueue.add(tempTQ.exportJob());
							}
						}
					}

					if(ioQueue.ticks > 0)
						ioQueue.ticks = ioQueue.ticks - 1;
					if(waitQueue.ticks > 0)
						waitQueue.ticks = waitQueue.ticks - 1;		

					if(RAM.jobCount == 0 && LTS.priorityJobCount > 0)
					{					
						std::vector<Job> temp;
						temp = LTS.exportPriority();
						for(unsigned int i = 0; i < temp.size(); i++)
						{
							RAM.add(temp.at(i));
						}
						STS.readRAM(RAM);
						RAM.clearRAM();
							
						temp = STS.exportList();
						for(unsigned int i = 0; i < temp.size(); i++)
						{
							readyQueue.add(temp.at(i));
						}					
					}
					ticks++;
					readyQueue.allWait();
					waitQueue.allWait();
					ioQueue.allWait();
				}
				timeTracker.markEnd();
				break;

			default:
				std::cout << "ERROR: Invalid Case" << std::endl;
		}
		

		std::cout << "\nSimulated Ticks: " << ticks << std::endl;
		timeTracker.markTotal();
		terminateQueue.printWaitTimes();

		std::cout << "\nJobs Remaining in Ready Queue: " << readyQueue.getJobCount() << std::endl;
		std::cout << "Jobs Remaining in Wait Queue: " << waitQueue.getJobCount() << std::endl;
		std::cout << "Jobs Remaining in IO Queue: " << ioQueue.getJobCount() << std::endl;
		std::cout << "Jobs currently in Terminate Queue: " << terminateQueue.getJobCount() << std::endl;

		std::cout << "\nAgain?\nY/N\n\n>" ;
		getline(std::cin,response2);
		transform(response2.begin(), response2.end(), response2.begin(), toupper);

	}while(response2 == "Y" || response2 == "YES");

	std::cout << "\nCoded by Patrick Rek" << std::endl;
}


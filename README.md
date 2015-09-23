# operating-systems-project
Course: Operating Systems - Simulated operating system

This was a university project to create a simulated operating system.
Rough overview of the flow:
- ugrad.txt holds jobs for the cpu
- Based off of which algorithm you choose: First in First Out, Shortest Job First, or Priority; the long term scheduler 
loads the jobs from the "hardrive".
- RAM gets loaded with the jobs
- Short term scheduler pulls jobs from RAM and enters them into the readyQ
- After which the cpu takes the jobs and procces them, including handling interupts and sending jobs into ioQ or waitQ.

The programs main is Operating System.cpp

// File: myTime.h
// Author: Patrick Rek
// Date : Summer 2014
// Last Updated by: Patrick Rek 27/09/15
// Description: Time class for simulated operating system. Mainly for tracking performance of the program.

#include <iostream>
#include <time.h> 

#ifndef _myTime
#define _myTime

class myTime
{
	public:
		void markStart();
		void markEnd();
		void markTotal();
		clock_t start_t, end_t, total_t;
};
#endif

void myTime::markStart()
{ 
   start_t = clock();
}

void myTime::markEnd()
{
    end_t = clock();
}

void myTime::markTotal()
{
    total_t = (end_t - start_t);
	printf ("took %d clicks (%f seconds)\n",total_t,((float)total_t)/CLOCKS_PER_SEC);
}
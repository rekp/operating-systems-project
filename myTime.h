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
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

volatile int * ticketArr;
volatile int * choosingArr;
volatile int numThreads;
int * threadCSCount;
volatile int in_cs;
int stop;


void critical_section_function(void * threadID);
void lock (int threadID);
void unlock(int threadID);
int getTicketArrMax();

// Write a pthreads program that creates a number of threads that repeatedly access a critical section that is synchronized using Lamport's
// Bakery Algorithm, which we discussed in class.
//
// Your program should take two command line options.  First, the number of threads.  Second, the number of seconds to run for.
//
// Just before terminating, your program should say how many times each thread entered the critical section.  Make sure starvation does not
// occur.

int main(int argc, char* argv[])
{

	// Perform error checking for valid input
	
	if(argc != 3)
	{
		fprintf(stderr, "Must provide the correct number of arguements \n");
		return 1;
	}

	// END ERROR CHECKING
	
	
  int numSeconds = atoi(argv[2]);
	numThreads = atoi(argv[1]);
	
	int createResult = -1;
	
	pthread_t * threadArr = malloc(sizeof(pthread_t)*numThreads);
	
	ticketArr = malloc(sizeof(int) * numThreads);
	choosingArr = malloc(sizeof(int) * numThreads);
	threadCSCount = malloc(sizeof(int) * numThreads);
	in_cs = 0;
	stop = 0;

	for(int i = 0; i < numThreads; i ++)
	{
		
		int *arg = malloc(sizeof(*arg));
		*arg = i;

		createResult = pthread_create(&threadArr[i], NULL, (void *) &critical_section_function, arg);

		if(createResult != 0)
		{
			fprintf(stderr, "Thread could not be created! \n");
			exit (1);
		}
	}
	
	sleep(numSeconds);
	
	stop = 1;

	int joinResult = -1;

	for(int i = 0; i < numThreads; i ++)
	{
		joinResult = pthread_join(threadArr[i], NULL);

		if(joinResult != 0)
		{
			fprintf(stderr, "Thread could not be joined! \n");
			exit (1);
		}
	}

	for(int i = 0; i < numThreads; i++)
		printf("Thread %d entered CS %d times. \n", i, threadCSCount[i]);

	free((void*) threadArr);
	free((void*) ticketArr);
	free((void*) choosingArr);
	free((void*) threadCSCount);
	
	return 0;
}

void critical_section_function(void * threadID)
{
	int tid = *((int *) threadID);

	while(!stop)
	{
		lock(tid);
		
		threadCSCount[tid]++;	
		
		assert(in_cs == 0);
		in_cs++;
		assert(in_cs == 1);
		in_cs++;
		assert(in_cs == 2);
		in_cs++;
		assert(in_cs == 3);
		in_cs = 0;

		unlock(tid);
	}
}

void lock(int threadID)
{
	choosingArr[threadID] = 1;
	ticketArr[threadID] = getTicketArrMax()  + 1;
	choosingArr[threadID] = 0;

	for(int j = 0; j < numThreads; j++)
	{
		while(choosingArr[j]);

		while((ticketArr[j] != 0) && ((ticketArr[j] < ticketArr[threadID]) || (ticketArr[j] == ticketArr[threadID] && j < threadID)));
	}
}

void unlock(int threadID)
{
	ticketArr[threadID] = 0;
}

int getTicketArrMax()
{
	int max = 0;

	for(int c = 0; c < numThreads; c++)
	{
		if(ticketArr[c] > max)
			max = ticketArr[c];
	}

	return max;
}

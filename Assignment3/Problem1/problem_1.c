#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void foobar_function();

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
	
	// CREATE X NEW THREADS
	
  //int numSeconds = atoi(argv[2]);
	int numThreads = atoi(argv[1]);
	int createResult = -1;
	pthread_t * threadArr = malloc(sizeof(pthread_t)*numThreads);
	
	for(int i = 0; i < numThreads; i ++)
	{
		createResult = pthread_create(&threadArr[i], NULL, (void *) &foobar_function, NULL);

		if(createResult != 0)
		{
			fprintf(stderr, "Thread could not be created! \n");
			exit (1);
		}
	}

	sleep(1);

	return 0;
}

void foobar_function()
{
	printf("foobar function called! \n");
}

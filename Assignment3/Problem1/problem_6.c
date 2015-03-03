#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

volatile int in_cs;
volatile double totalCount = 0;
volatile double hitCount = 0;
int stop;
pthread_mutex_t lock;

void critical_section_function();
double rand_double( double low, double high ); 

/*
 *
 *	Problem 6
 *
 */
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
	int numThreads = atoi(argv[1]);
	
	int createResult = -1;
	
	pthread_t * threadArr = malloc(sizeof(pthread_t)*numThreads);
	
	in_cs = 0;
	stop = 0;

	for(int i = 0; i < numThreads; i ++)
	{
		
		createResult = pthread_create(&threadArr[i], NULL, (void *) &critical_section_function, NULL);

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

	printf("Total Number of Points: %f \n", totalCount);
	printf("Number of points inside circle: %f \n", hitCount);
	printf("Pie is roughly equivalent to: %f \n", 4.0 * hitCount / totalCount); 

	free((void*) threadArr);
	
	return 0;
}

void critical_section_function()
{
	//int tid = *((int *) threadID);

	while(!stop)
	{
		pthread_mutex_lock(&lock);

		in_cs++;
		assert(in_cs == 1);
		in_cs++;
		assert(in_cs == 2);
		in_cs++;
		assert(in_cs == 3);
		in_cs = 0;
		
		// Generate a random point
		double randomX = rand_double(-1, 1);
		double randomY = rand_double(-1, 1);
		
		totalCount++;

		if(((randomX * randomX) + (randomY*randomY)) < 1)
		{
			hitCount++;
		}

		pthread_mutex_unlock(&lock);
	}
}

double rand_double( double low, double high ) 
{
	return ( ( double )rand() * ( high - low ) ) / ( double )RAND_MAX + low;
}

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

int * threadCSCount;
volatile int in_cs;
int stop;

void critical_section_function(void * threadID);
static inline int atomic_xadd (volatile int *ptr);

struct fair_spin_lock_t {
	volatile int ticketNum;
	volatile int numBeingServed;
};

struct fair_spin_lock_t s;

void fair_spin_lock (struct fair_spin_lock_t *s);
void fair_spin_unlock (struct fair_spin_lock_t *s);

/*
 *
 *	Problem 5
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
	threadCSCount = malloc(sizeof(int) * numThreads);
	in_cs = 0;
	stop = 0;
	
	s.ticketNum = 0;
	s.numBeingServed = 0;

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
	free((void*) threadCSCount);
	
	return 0;
}

void critical_section_function(void * threadID)
{
	int tid = *((int *) threadID);

	while(!stop)
	{
		fair_spin_lock(&(s));

		threadCSCount[tid]++;	
		
		assert(in_cs == 0);
		in_cs++;
		assert(in_cs == 1);
		in_cs++;
		assert(in_cs == 2);
		in_cs++;
		assert(in_cs == 3);
		in_cs = 0;

		fair_spin_unlock(&(s));
	}
}

void fair_spin_lock(struct fair_spin_lock_t *s)
{
	// Take the next ticket value and then atomically add 1
	volatile int myTicket = atomic_xadd(&(s -> ticketNum));

	// Wait.  While my ticket value is not equal to the one currently being served.
	while(myTicket != (s -> numBeingServed)); 
}

void fair_spin_unlock(struct fair_spin_lock_t *s)
{
	// Upon unlocking increment the number being served to allow the next thread to now enter the critical section.
	atomic_xadd(&(s -> numBeingServed));
}

/*
 * atomic_xadd
 *
 * equivalent to atomic execution of this code:
 *
 * return (*ptr)++;
 * 
 */
static inline int atomic_xadd (volatile int *ptr)
{
	  register int val __asm__("eax") = 1;
		__asm volatile ("lock xaddl %0,%1"
		: "+r" (val)
		: "m" (*ptr)
		: "memory"
		);  
		return val;
}

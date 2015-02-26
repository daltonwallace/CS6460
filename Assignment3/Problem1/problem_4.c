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
static inline int atomic_cmpxchg (volatile int *ptr, int old, int new);

struct spin_lock_t {

	volatile int lock;

};

struct spin_lock_t s;

void spin_lock (struct spin_lock_t *s);
void spin_unlock (struct spin_lock_t *s);

/*
 *
 *  Problem 4.  Implemented using a spin lock for multiple cores.  Moving away from Lamport Bakery Algorithm..
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
	
		spin_lock(&(s));

		threadCSCount[tid]++;	
		
		assert(in_cs == 0);
		in_cs++;
		assert(in_cs == 1);
		in_cs++;
		assert(in_cs == 2);
		in_cs++;
		assert(in_cs == 3);
		in_cs = 0;

		spin_unlock(&(s));
	}
}

void spin_lock(struct spin_lock_t *s)
{
	while(atomic_cmpxchg(&(s->lock), 0, 1));		
}

void spin_unlock(struct spin_lock_t *s)
{
	atomic_cmpxchg(&(s->lock), 1, 0);
}

/*
 * atomic_cmpxchg
 * 
 * equivalent to atomic execution of this code:
 *
 * if (*ptr == old) {
 *   *ptr = new;
 *   return old;
 * } else {
 *   return *ptr;
 * }
 *
 */
static inline int atomic_cmpxchg (volatile int *ptr, int old, int new)
{
	  int ret;
		
		__asm volatile ("lock cmpxchgl %2,%1"
			: "=a" (ret), "+m" (*ptr)     
			: "r" (new), "0" (old)      
			: "memory");         
	
		return ret;                            
}

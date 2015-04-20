#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/types.h>


void* sleepy_write_0(void* x)
{
	int filedesc = open("/dev/sleepy0", O_RDWR);
	
	if(filedesc < 0)
	{
		printf("Could not access file in sleep_write_0 %s \n", strerror(errno));
		return x;
	}

	// Could not get to this point without modifying sleepy permissions
	printf("Sleepy0 going to sleep.. \n");
	int retval = write(filedesc, "0005", 4);	
	
	//printf("WRITE ERRNO: %s \n", strerror(errno));	
	printf("sleepy 0 AFTER BEING AWOKEN, (should be 0): %d \n", retval);
	
        
	close(filedesc);
 	
	return x;	
}


void* sleepy_write_1(void* x)
{
	int filedesc = open("/dev/sleepy1", O_RDWR);
	
	if(filedesc < 0)
	{
		printf("Could not access file in sleep_write_0 %s \n", strerror(errno));
		return x;
	}

	// Could not get to this point without modifying sleepy permissions
	printf("Sleep1 going to sleep.. \n");
	int retval = write(filedesc, "0010", 4);	
	
	//printf("WRITE ERRNO: %s \n", strerror(errno));	
	printf("sleepy 1 AFTER BEING AWOKEN, (should not be 0): %d \n", retval);
	
	close(filedesc);


	return x;	
}

void* sleepy_read_1(void* x)
{
	int filedesc2 = open("/dev/sleepy1", O_RDONLY);
	
	if(filedesc2 < 0)
	{
		printf("Could not access file %s \n", strerror(errno));
		return x;
	}
	
	printf("Waking up Sleepy1...\n");
	
	char data[128];
	ssize_t size = read(filedesc2, data, 128);
	
	//printf("READ ERRNO: %s \n", strerror(errno));	
	printf("IGNORE Read return value: %zd \n", size);
	return x;
}

void* sleepy_read_0(void* x)
{
	int filedesc2 = open("/dev/sleepy0", O_RDONLY);
	
	if(filedesc2 < 0)
	{
		printf("Could not access file %s \n", strerror(errno));
		return x;
	}
	
	printf("Waking up Sleepy0...\n");
	
	char data[128];
	ssize_t size = read(filedesc2, data, 128);
	
	//printf("READ ERRNO: %s \n", strerror(errno));	
	printf("IGNORE Read return value: %zd \n", size);
	return x;
}

int main( int argc, const char* argv[] )
{

	pthread_t * threadArr = malloc(sizeof(pthread_t)*4);
	
	int createResult;
	
	int *arg = malloc(sizeof(*arg));
	*arg = 0;

	createResult = pthread_create(&threadArr[0], NULL, sleepy_write_0, arg);

	if(createResult != 0)
	{
		fprintf(stderr, "Thread could not be created! \n");
		return 1;
	}

	createResult = pthread_create(&threadArr[1], NULL, sleepy_write_1, arg);

	if(createResult != 0)
	{
		fprintf(stderr, "Thread could not be created! \n");
		return 1;
	}
	
	sleep(2);

	createResult = pthread_create(&threadArr[2], NULL, sleepy_read_0, arg);
	
	if(createResult != 0)
	{
		fprintf(stderr, "Thread could not be created! \n");
		return 1;
	}
	
	sleep(6);

	createResult = pthread_create(&threadArr[3], NULL, sleepy_read_1, arg);
	
	if(createResult != 0)
	{
		fprintf(stderr, "Thread could not be created! \n");
		return 1;
	}
	
	int joinResult = -1;

	for(int i = 0; i < 4; i ++)
	{
		joinResult = pthread_join(threadArr[i], NULL);

		if(joinResult != 0)
		{
			fprintf(stderr, "Thread could not be joined! \n");
			return 1;
		}
	}

	//sleepy_test_1();
	return 0;
}

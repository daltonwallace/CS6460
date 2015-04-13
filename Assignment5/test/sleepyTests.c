#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/types.h>

volatile int filedesc;

void* sleepy_write_0(void* x)
{
	filedesc = open("/dev/sleepy0", O_RDWR);
	
	if(filedesc < 0)
	{
		printf("Could not access file in sleep_write_0 %s \n", strerror(errno));
		return x;
	}

	// Could not get to this point without modifying sleepy permissions
	printf("Calling write.. \n");
	int retval = write(filedesc, "0005", 4);	
	
	printf("WRITE ERRNO: %s \n", strerror(errno));	
	printf("WRITE AFTER BEING AWOKEN, (should not be 0): %d \n", retval);
	
	return x;	
}

void* sleepy_read_0(void* x)
{
	//int filedesc2 = open("/dev/sleepy0", O_RDONLY);
	
	if(filedesc < 0)
	{
		printf("Could not access file %s \n", strerror(errno));
		return x;
	}
	
	printf("Calling read...\n");
	
	char data[128];
	ssize_t size = read(filedesc, data, 128);
	
	printf("READ ERRNO: %s \n", strerror(errno));	
	printf("Read return value: %zd \n", size);
	return x;
}

void sleepy_test_1(void)
{
	int fd = open("/dev/sleepy0", O_RDWR);

	if(fd < 0)
	{
		printf("Could not access file %s \n", strerror(errno));
		return;
	}
	
	pid_t childpid;

	childpid = fork();
	
	if(childpid == 0)
	{
		// We are in the child
		
		// Could not get to this point without modifying sleepy permissions
		printf("Calling write.. \n");
		int retval = write(fd, "0005", 4);	
	
		printf("WRITE ERRNO: %s \n", strerror(errno));	
		printf("WRITE AFTER BEING AWOKEN, (should not be 0): %d \n", retval);
	}
	else
	{
		// We are in the parent
	
		sleep(5);	
		printf("Calling read...\n");
	
		char data[128];
		ssize_t size = read(fd, data, 128);
	
		printf("READ ERRNO: %s \n", strerror(errno));	
		printf("Read return value: %zd \n", size);
		
	}
}

int main( int argc, const char* argv[] )
{

	pthread_t * threadArr = malloc(sizeof(pthread_t)*2);
	
	int createResult;
	
	int *arg = malloc(sizeof(*arg));
	*arg = 0;

	createResult = pthread_create(&threadArr[0], NULL, sleepy_write_0, arg);

	if(createResult != 0)
	{
		fprintf(stderr, "Thread could not be created! \n");
		return 1;
	}
	
	sleep(2);

	createResult = pthread_create(&threadArr[1], NULL, sleepy_read_0, arg);
	
	if(createResult != 0)
	{
		fprintf(stderr, "Thread could not be created! \n");
		return 1;
	}
	
	int joinResult = -1;

	for(int i = 0; i < 2; i ++)
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

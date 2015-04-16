#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/types.h>

volatile int filedesc;

void shady_test_1(void)
{
	int fd = open("shady_test.txt", O_RDWR);

	if(fd < 0)
	{
		printf("Could not access file %s \n", strerror(errno));
		return;
	}
}

int main( int argc, const char* argv[] )
{
	shady_test_1();	
	return 0;
}

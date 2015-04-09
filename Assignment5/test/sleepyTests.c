#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void sleepy_test_1(void)
{
	
	int filedesc = open("/dev/sleepy0", O_RDWR);
	
	if(filedesc < 0)
	{
		printf("Could not access file %s \n", strerror(errno));
		return;
	}

	// Could not get to this point without modifying sleepy permissions

	
	char data[128];
	ssize_t x = read(filedesc, data, 128);
	printf("read result: %s \n", strerror(errno));	
	printf("file size: %zd \n", x);
	//ssize_t sleepy_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
	
}

int main( int argc, const char* argv[] )
{
	sleepy_test_1();
	return 0;
}

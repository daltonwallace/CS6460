//#include "assign1.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
//#include "../sleepy.h"

/* The structure to represent 'sleepy' devices. 
 *  data - data buffer;
 *  buffer_size - size of the data buffer;
 *  block_size - maximum number of bytes that can be read or written 
 *    in one call;
 *  sleepy_mutex - a mutex to protect the fields of this structure;
 *  cdev - ñharacter device structure.
 */
//struct sleepy_dev {
//  unsigned char *data;
//  struct mutex sleepy_mutex; 
//  struct cdev cdev;
//};

void sleepy_test_1(void)
{
	
	FILE *fp = fopen("/dev/sleepy0", "w");
		
	if(fp == NULL)
		printf("Could not access file %s \n", strerror(errno));

	// Could not get to this point without modifying sleepy permissions

	//sleepy_dev *pd;
	//pthread_mutex_init(&pd->sleepy_mutex);
	//fp -> private_data = pd;
	
	ssize_t x = fread(fp, 0, 0, 0);
	printf("fread result: %s \n", strerror(errno));	
	printf("file size: %zd \n", x);
	//ssize_t sleepy_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
	
}

int main( int argc, const char* argv[] )
{
	sleepy_test_1();
	return 0;
}

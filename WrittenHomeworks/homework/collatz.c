#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


void printCollatz(long startValue)
{
	// Verify that the number is positive
	if(startValue <= 0)
	{
		printf("Invalid Input: Please input positive integer \n");
		return;
	}
	else if(startValue == 1)
	{
		printf("%ld \n", startValue);
		return;
	}


	printf("%ld, ", startValue);
	
	while(startValue > 1)
	{
		if(startValue % 2 == 0)
		{
			startValue = startValue / 2;
		}		
		else
		{
			startValue = (3*startValue) + 1;
		}
		
		if(startValue == 1)
			printf("%ld \n", startValue);
		else
			printf("%ld, ", startValue);
	}

}

//int isLong(char const* input)
//{
//	return strcmp(ltoa(atol(input)), input) == 0;
//}

int main(int argc, char *argv[])
{
	if(argc <= 1)
	{
		// No arguments
		printf("Invalid Input: Please input positive integer \n");
		return 0;
	}

	//if(!isLong(argv[1]))
	//{
	//	printf("Invalid Input: Please input positive integer \n");
	//	return 0;
	//}

	long value = atol(argv[1]);

	pid_t pid;
	
	pid = fork();
	
	if (pid == 0) 
	{ 
		/* child process */
		printCollatz(value);
		return 0;
	}
	else if (pid > 0) 
	{ 
		/* parent process */
		int status;
		wait(&status);

		if(status != 0)
		{
			printf("Error occurred! \n");
			exit(EXIT_FAILURE);
		}
		
		return 0;
	}

}



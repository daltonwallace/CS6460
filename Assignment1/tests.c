#include "assign1.h"
#include <stdio.h>

void test_byte_sort(void)
{
        unsigned long result = byte_sort(0x0403deadbeef0201);
	
	if(result == 0xefdebead04030201)
	{
		printf("test_byte_sort PASSED \n");
	} 
	else
	{
		printf("test_byte_sort FAILED \n");
	}
}

void test_nibble_sort(void)
{
	// EXAMPLE: nibble_sort (0x0403deadbeef0201) returns 0xfeeeddba43210000
	unsigned long result = nibble_sort(0x0403deadbeef0201);
	
	if(result == 0xfeeeddba43210000)
	{
		printf("test_nibble_sort PASSED \n");
	} 
	else
	{
		printf("test_nibble_sort FAILED \n");
	}
}

void test_convert(void)
{
	printf("test_convert results:\n");	

	printf("\n");	
	enum format_t mode = HEX;
	
	printf("===========HEX TEST============\n");
	printf("Expected Output: 00000000deadbeef\n");
	printf("Actual Output  : ");
	convert(mode, 0xdeadbeef);
	printf("\n");	
	
	mode = BIN;
	printf("===========BINARY TEST============\n");
	printf("Expected Output: 0000000000000000000000000000000011011110101011011011111011101111\n");
	printf("Actual Output  : ");
	convert(mode, 0xdeadbeef);
	printf("\n");	
	
	mode = OCT;
	printf("===========OCTAL TEST============\n");
	printf("Expected Output: 0000000000033653337357\n");
	printf("Actual Output  : ");
	convert(mode, 0xdeadbeef);
	printf("\n");	
}

void test_name_list(void)
{
	struct elt *start = name_list();	
	
	struct elt *temp=start;
	
	while(temp!=NULL)
	{
	     	// do something
		printf("Letter is: %c\n", temp->val);
		temp = temp->link;	           
	}
}

void test_draw_me(void)
{
		draw_me();
}

int main( int argc, const char* argv[] )
{
	test_byte_sort();
	test_nibble_sort();
	test_convert();
	test_name_list();
	test_draw_me();
	return 0;
}

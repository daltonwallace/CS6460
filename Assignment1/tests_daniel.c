#include "assign1.h"
#include <stdio.h>

int test_byte_sort();
int test_convert();
int test_nibble_sort();
int test_name_list();
int test_convert();
int test_draw_me();
/**
 * Tester file for assign1.c.
 */
int main()
{
  if (test_byte_sort())
  {
    printf("test_byte_sort passed!\n");
  }
  else 
	{
    printf("failed test_byte_sort\n");
    return 0;
  }
	if (test_nibble_sort())
	{
		printf("test_nibble_sort passed!\n");
	}
	else
	{
    printf("failed test_nibble_sort\n");
		return 0;
	}
	if (test_name_list())
	{
		printf("test_name_list passed!\n");
	}
	else
	{
		printf("failed test_name_list\n");
		return 0;
	}
	test_convert();
	test_draw_me();
	return 1;
}

int test_byte_sort(){
	if (0xFFCEAB9854321200 != byte_sort(0x1254CE320098FFAB))
	{
		return 0;
	}
	if (0xFFFFFFFFFFFFFFFF != byte_sort(0xFFFFFFFFFFFFFFFF))
	{
		return 0;
	}
	if (0x0000000000000000 != byte_sort(0x0000000000000000))
	{
		return 0;
	}
	if (0x0807060504030201 != byte_sort(0x0102030405060708))
	{
		return 0;
	}
	if (0xefdebead04030201 != byte_sort (0x0403deadbeef0201))
	{
		return 0;
	}


  return 1; 
}

int test_nibble_sort(){
	if (0xFFECBA9854322100 != nibble_sort(0x1254CE320098FFAB))
	{
		return 0;
	}
	if (0xFFFFFFEEEEEDD410 != nibble_sort(0xFE4E10EDFFDFEFFE))
	{
		return 0;
	}
	if (0xFFFFFFFFFFFFFFFF != nibble_sort(0xFFFFFFFFFFFFFFFF))
	{
		return 0;
	}
	if (0x0000000000000000 != nibble_sort(0x0000000000000000))
	{
		return 0;
	}
	return 1;	
}

int test_name_list(){
	char name_arr[6];
  struct elt *list = name_list();
	
	if(list != NULL)
	{
		name_arr[0] = list->val;
		list = list->link;

		name_arr[1] = list->val;
		list = list->link;

		name_arr[2] = list->val;
		list = list->link;

		name_arr[3] = list->val;
		list = list->link;

		name_arr[4] = list->val;
		list = list->link;

		name_arr[5] = list->val;

		if (0 == strcmp(&name_arr, "DANIEL")){
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 1;
}

int test_convert()
{
	printf("=======OCTAL TESTS:=======\n");
	printf("EXPECTED: 0000000000000000000070\n");
	convert (OCT, 56);

	unsigned long big_num = 0xFFFFFFFFFFFFFFFF;
  printf("EXPECTED: \n1777777777777777777777\n");
	printf("ACTUAL:\n");
	convert (OCT, big_num);

	printf("EXPECTED: \n0000000000033653337357\n");
	printf("ACTUAL:\n");
	convert (OCT, 0xDEADBEEF);

	printf("EXPECTED: \n1677365752640400601001\n");
	printf("ACTUAL:\n");
	convert (OCT, 0xEFDEBEAD04030201);

	printf("EXPECTED: \n00000000000000000000000\n");
	printf("ACTUAL:\n");
	convert (OCT, 0);

	printf("\n=======BINARY TESTS:=======\n\n");
	printf("EXPECTED: \n0000000000000000000000000000000000000000000000000000000000001111\n");
	printf("ACTUAL:\n");
	convert (BIN, 15);

  printf("EXPECTED: \n1111111111111111111111111111111111111111111111111111111111111111\n");
	printf("ACTUAL:\n");
	convert (BIN, big_num);

  printf("EXPECTED: \n0000000000000000000000000000000011011110101011011011111011101111\n");
	printf("ACTUAL:\n");
	convert (BIN, 0xDEADBEEF);

  printf("EXPECTED: \n1110111111011110101111101010110100000100000000110000001000000001\n");
	printf("ACTUAL:\n");
	convert (BIN, 0xEFDEBEAD04030201);

  printf("EXPECTED: \n0000000000000000000000000000000000000000000000000000000000000000\n");
	printf("ACTUAL:\n");
	convert (BIN, 0);

	printf("\n=======HEX TESTS:=======\n\n");
	printf("EXPECTED: \n0x00000000000024\n");
	printf("ACTUAL:\n");
	convert (HEX, 36);

	printf("EXPECTED: \n00000000DEADBEEF\n");
	printf("ACTUAL:\n");
	convert (HEX, 0xDEADBEEF);

 	printf("EXPECTED: \nFFFFFFFFFFFFFFFF\n");
	printf("ACTUAL:\n");
	convert (HEX, 0xFFFFFFFFFFFFFFFF);

  printf("EXPECTED: \n0000000000000000\n");
	printf("ACTUAL:\n");
	convert (HEX, 0);

	printf("EXPECTED: \nEFDEBEAD04030201\n");
	printf("ACTUAL:\n");
	convert (HEX, 0xEFDEBEAD04030201);


	return 1;
}

int test_draw_me()
{
	draw_me();
	printf("Ran draw_me\n");	
	return 1;
}



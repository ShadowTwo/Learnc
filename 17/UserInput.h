#ifndef __UserInput_h_
#define __UserInput_h_

#include <stdio.h>
#include <string.h>

#define str_LengthofInt 16

int Read_Int(int *Number)
{
	//Reaqd the user input
	char *UserInput = malloc(sizeof(char) * str_LengthofInt);
	
	char *rc;
	
	rc = fgets(UserInput, str_LengthofInt, stdin);

	//Check that each input is a number
	

	//Convert String to Integer
	if (rc) 
	{
		*Number = atoi(UserInput);	
		return 1;
	}
	
	//Failed to Read
	return 0;
}

#endif

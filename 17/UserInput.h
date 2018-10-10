#ifndef __UserInput_h_
#define __UserInput_h_

#include <stdio.h>
#include <string.h>

#define str_LengthofInt 16

int Read_Int(int *Number)
{
	//Reaqd the user input
	char *UserInput = fgets(Number, strLengofInt, stdin);

	//Check that each input is a number
	

	//Convert String to Integer
	Number = atoi(UserInput);
	
	return 1
}

#endif

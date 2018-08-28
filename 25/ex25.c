#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "dbg.h"

#define MAX_DATA 100

int read_string(char **out_string, int max_buffer)
{
	*out_string = calloc(char **out_string, max_buffer + 1);

	check_mem(*out_string);

	char *result = fgets(*out_string, max_buffer, stdin);
	check(result != NULL, "Input Error.");

	return 0;

	error:
		if (*out_string) {free(*outstring);}
		*out_string = NULL;
		return -1;
}//end of Read_String

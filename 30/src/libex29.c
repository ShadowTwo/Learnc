#include <stdio.h>
#include <ctype.h>
#include "../shared/dbg.h"

int print_a_message(const char *msg)
{
	printf("A String: %s\n", msg);
	return 0;
}//end of print_a_message

int uppercase(const char *msg)
{
	int i = 0;
	//BUG: \0 Terminated String Issues
	for (i = 0; msg[i] != '\0'; i++)
	{
		printf("%c", toupper(msg[i]));
	}
	printf("\n");
	return 0;
} //end of uppercase

int lowercase(const char *msg)
{
	int i = 0;
	//bug use os null term
	for(i=0; msg[i] != '\0'; i++)
	{
		printf("%c", tolower(msg[i]));
	}
	printf ("\n");
	return 0;
}//end of lowercase

int fail_on_purpose(const char *msg)
{
	return 1;
} //end of fail_on_purpose



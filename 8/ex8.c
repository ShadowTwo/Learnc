#include <stdio.h>

int main(int argc, char *argv[])
{
	int i = 0;
	
	if (argc == 1)	{printf("You not entered any args to count.\nex8 arg1 [arg2]\n");}
	else if (argc > 1 && argc < 4)
	{
		printf("Here are the Args:\n");
		for (i = 0; i<argc; i++) {printf("Arg %d: %s\n", i, argv[i]);}
		printf("Total ARGS: %d\n", i);
	}
	else {printf("Too many args!\n");}

	return 0;		
}

#include <stdio.h>

int main (int argc, char *argv[])
{
	int i = 0;
	//int x=0;
	char *states[] = {"OK", "CA", "MA", "Ryan"};
	
	if (argc > 2) 
	{
 		argv[2] = states[0]; 
		states[1] = argv[0];
	}

	for (i = 1; i < argc; i++)
	{
		printf("Argv[%d]: %s\n", i, argv[i]);
	}

	// Make our own Array
	
	
	printf("Sizeof Char: %d\n", sizeof(char));
	printf("Sizeof States: %d\n", sizeof(states));
	printf("Sizeof *char: %d\n", sizeof(char*));
	printf("Length of states: %d\n", sizeof(states) / sizeof(char*));
	printf("States: %x\n", states);

	//for(x =0; states[x] != 0; x++) printf("%d\n", x);

	for (i=0; i < 4; i++)
		{printf("State[%d]: %s\n", i, states[i]);}

	return 0;
}

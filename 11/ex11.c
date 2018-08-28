#include <stdio.h>

void printtemp(char mystring[])
{
	for(int i = 0; i < sizeof(mystring)/sizeof(char); i++)
	{printf("%d: %c\n", i, mystring[i]);}
	printf("\n");
}

int main(int argc, char *argv[])
{
	char temp[] = "Start Much longer";

	printf("Temp: %s.\nSize: %lo\nChar: %ld\n", temp, sizeof(temp)/sizeof(char), sizeof(char));

	printtemp(temp);
	temp[(sizeof(temp) / sizeof(char))-1] = '1';
	printtemp(&temp);

	printf("Temp Mod: %s\n", temp);

	return 0;
}



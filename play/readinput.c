#include <stdio.h>
#include "dbg.h"
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	int rc =0;
	int rs = 0;
	
	long unsigned int UserInput = 15;
	int Saveme = 0;
	char *Path = NULL;
	long int sizepath = 0;

	while(1)
	{
		//fflush(stdin);
		printf("Welcome to my test App.\n");
		
		printf("Lets try a String>> ");
		if(Path) {free(Path);}
		Path = malloc(UserInput * sizeof(char));
		rs = getline(&Path, &UserInput, stdin);
		check(rs != -1, "Failed to Read Path.");
		printf("We Got: '%s'\nThe int is %d\n", Path, (int)Path[0]);
		
		printf("Lets try a String2>> ");
		rs = getline(&Path, &UserInput, stdin);
		check(rs != -1, "Failed to Read Path.");
		printf("We Got 2: '%s'\n", Path);
		
		printf("Lets try a int>> ");
		rs = getline(&Path, &UserInput, stdin);
		check(rs != -1, "Failed to Read Path.");
		sizepath = sizeof(*Path);
		printf("Size of Value of Path: %ld\n", sizepath);
		rc = fscanf(&Path, "%ld", &sizepath);		
		check (rc, "Invaild Entry. Please enter a number not %ld.\nRC was %d.\n", UserInput, rc);
		
		
		
		if((UserInput == 999) || Saveme == 35) {goto out;}
		else {printf("Not the right input\nPath: %s", Path);}
		
		Saveme++;
	} //end of while
	
	out:
	if(Path) {free(Path);}
	return 1;
	error:
		if(Path) {free(Path);}
		return 0;
} //endof Main

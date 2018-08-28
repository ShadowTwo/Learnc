#include <stdio.h>
#include "dbg.h"

#define MAX_DATA 100

typedef enum EyeColor {BLUE_EYE, GREEN_EYE, BROWN_EYE, BLACK_EYE, OTHER_EYE} EyeColor;

const char *EYE_COLOR_NAME[] = {"Blue", "Green", "Brown", "Black", "Other"};

typedef struct Person {
	int age;
	char first_name[MAX_DATA];
	char last_name[MAX_DATA];
	EyeColor eyes;
	float income;
} Person;

int main(int argc, char *argv[])
{
	Person you = {.age = 0};
	int i =0;
	char *in = NULL;

	printf("What's you First Name? ");
	in = fgets(you.first_name, MAX_DATA-1, stdin);
	check( in != NULL, "Failed to read First Name.");

	printf("What's you Last Name? ");
	in = fgets(you.last_name, MAX_DATA-1, stdin);
	check( in != NULL, "Failed to read Last Name.");

	printf("How old are you? ");
	int rc = fscanf(stdin, "%d", &you.age);
	check( rc > 0, "You have to enter a number.");

	printf("what color are your eyes?\n");
	for (i = 0; i <= OTHER_EYE; i++) 
	{
		printf("%d) %s\n", i + 1, EYE_COLOR_NAME[i]);
	}	
	
	int eyes = -1;
	rc = fscanf(stdin, "%d", &eyes);
	check (rc > 0, "You have to enter a number.");
	
	you.eyes = eyes -1;
	
	check(you.eyes <= OTHER_EYE && you.eyes >= 0, "Do it right, that's not an option");
	
	printf("How much do you make an hours? ");
	rc = fscanf(stdin, "%f", &you.income);
	check(rc > 0, "Enter a floating point number.");
	
	printf("----- Results -----\n");
	printf("First Name: %s", you.first_name);
	printf("Last Name: %s", you.last_name);
	printf("Age: %d\n", you.age);
	printf("Eyes: %s\n", EYE_COLOR_NAME[you.eyes]);
	printf("Income %f\n", you.income);
	
	return 0;
	error:
	return -1;
}//End of Main


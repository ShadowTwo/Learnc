#include <stdio.h>

int main ( int argc, char *argv[])
{
	int distance = 100;
	float power = 2.345f;
	double super_power = 56789.4532;
	char iniitial = 'A';
	char first_name[] = "Ryan";
	char last_name[] = "Davis";
	
	printf("We will start here.\n");
	printf("You are %d miles away.\n", distance);
	printf("You have %f levels of power.\n", power);
	printf("You have %f awesome super powers.\n", super_power);
	printf("I have initial %c.\n", iniitial);
	printf("My whole name is %s %c. %s.\n",first_name, iniitial, last_name );
	int bugs = 100;
	double bug_rate = 1.2;
	printf("You have %d bugs at the imaginary rate of %f.\n", bugs, bug_rate );
	
	char nul_byte = '\1';
	int care_var = bugs * nul_byte;
	printf("Odd Math: %d%%.\n", care_var);
	printf("nul_byte: %s.\n", nul_byte);
	return 0;
}

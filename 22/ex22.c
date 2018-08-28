#include <stdio.h>
#include "ex22.h"
#include "dbg.h"

int THE_SIZE = 1000;

static int THE_AGE = 37;

int get_age()
{
	return THE_AGE;
}//end of the get_age

void set_age(int age)
{
	THE_AGE = age;
}//end of set_age

double update_ratio(double new_ratio)
{
	static double ratio = 1.0;
	double old_ratio = ratio;
	ratio = new_ratio;
	return old_ratio;
}//end of udpate_ratio

void print_size()
{
	log_info("I think THE_SIZE is : %d", THE_SIZE);
}//end of print_size


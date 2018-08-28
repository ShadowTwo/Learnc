#include "ex22.h"
#include "dbg.h"

const char *MY_NAME = "Ryan A. Davis";

void scope_demo(int count)
{
	log_info("count is : %d", count);

	if (count >10) 
	{
		int count = 100;
		log_info("Count in the if scope is %d", count);
	}

	log_info("Count outside the if scope is %d", count);
	count = 1000;

	log_info("Count after the assign is %d", count);
}

int main(int argc, char *argv[])
{
	log_info("My name is %s, age: %d.", MY_NAME, get_age());

	set_age(100);

	log_info("Age is now: %d", get_age());

	log_info("THE_SIZE is %d", THE_SIZE);
	print_size();

	THE_SIZE = 9;

	log_info("THE_SIZE is now %d", THE_SIZE);

	log_info("Ratio at first: %f", update_ratio(2.0));
	log_info("Ratio again: %f", update_ratio(10.0));
	log_info("Ratio Once More: %f", update_ratio(300.0));

	int count = 4;
	scope_demo(count);
	scope_demo(count *20);
	log_info("Count after scope_demo: %d", count);

	return 0;
}//end of main


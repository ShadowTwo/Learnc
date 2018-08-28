#include "dbg.h"
#include <stdlib.h>
#include <stdio.h>

void test_debug()
{
	debug("I have Brown Hair.");

	debug("I am %d years old.", 34);
}//end of test_debug

void test_log_err()
{
	log_err("i think everything is broken.");
	log_err("there are %d problem in %s.", 0 , "space");
} //end of test_log_err()

void test_log_warn()
{
	log_warn("You can Safely ignore this.");
	log_warn("Maybe cond=sider logging at: %s.", "/etc/passwd");
}//End of test_log_warn

void test_log_info()
{
	log_info("Well I did someting mundane.");
	log_info("It happended %f times today.", 1.3f);
}//End of test_log_info

int test_check(char *file_name)
{
	FILE *input = NULL;
	char *block = NULL;

	block = malloc(100);
	check_mem(block);

	input = fopen(file_name, "r");
	check(input, "Failed to open %s.", file_name);

	free(block);
	free(input);
	return 0;
	
	error:
	if (block) free(block);
	if (input) free(input);
	return 0;
}// end of test_check

int test_sentinel(int code)
{
	char *temp = malloc(100);
	check_mem(temp);

	switch (code)
	{
		case 1:
			log_info("It Worked.");
			break;
		default:
			sentinel("I shouldn't run");
	}
	
	free(temp);
	return 0;
	
	error:
	if (temp) {free(temp);}
	return -1;
} //end of test_sentinel

int  test_check_mem()
{
	char *test = NULL;
	check_mem(test);
	
	free(test);
	return 1;
	error:
	return -1;
} //end of test_check_mem

int test_check_debug()
{
	int i = 0;
	check_debug(i !=0, "Opps, I was 0.");
	return 0;
	
	error:
	return -1;
}//end of test_check_debug

int main(int argsc, char *argsv[])
{
	
}//end of main

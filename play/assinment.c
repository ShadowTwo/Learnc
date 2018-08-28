#include <stdio.h>
#include <string.h>
#include "dbg.h"

int main(int argc, char *argv[])
{
	int count = 0;
	log_info("Count is %d.", count);
	log_info("++n = %d, After ++n = %d", ++count, count);
	log_info("n++ = %d, After n++ = %d", count++, count);

	log_info("(15+7)/8 = %d", (15+7)/8);
	log_info("(15 mod 8) = %d", 15%8);
	return 0;
}

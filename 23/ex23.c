#include <stdio.h>
#include <string.h>
#include "dbg.h"

int normal_copy(char *from, char *to, int count)
{
	int i = 0;
	for (i = 0; i<count; i++) { to[i] = from[i]; }
	
	return i;
} //end of normnal_copy

int duffs_device(char *from, char *to, int count)
{
	int n = (count + 7) / 8;
	
	switch (count % 8)
	{
		case 0:
			do {
				*to++  = *from++;
				case 7:
					*to++  = *from++;
				case 6:
					*to++  = *from++;
				case 5:
					*to++  = *from++;
				case 4:
					*to++  = *from++;
				case 3:
					*to++  = *from++;
				case 2:
					*to++  = *from++;
				case 1:
					*to++  = *from++;
				} while (--n > 0);
	}
	return count;
} // end of duffs_device

int zeds_device ( char *from, char *to, int count)
{
	int n =  (count + 7) / 8;
	
	switch(count % 8)
	{
		case 0:
		again: *to++ = *from++;
		case 7:
				*to++  = *from++;
		case 6:
				*to++  = *from++;
		case 5:
				*to++  = *from++;
		case 4:
				*to++  = *from++;
		case 3:
				*to++  = *from++;
		case 2:
				*to++  = *from++;
		case 1:
				*to++  = *from++;
				if (--n > 0) {goto again;}
	}// end of switch
	return count;
}// end of zeds_device

int valid_copy(char *data, char expects, int count)
{
	int i = 0;
	for(i =0; i <count; i++)
	{
		if (data[i] != expects)
		{
			log_err("[%d] %c != %c", i, data[i], expects);
			return 0;
		}
	}
	return 1;
} //end of valid_copy

int main(int argc, char *argv[])
{
	char from[1000] = { 'a'};
	char to[1000] = {'c'};
	int rc = 0;
	
	memset(from, 'x', 1000);
	check(valid_copy(from, 'x', 1000), "Failed to Initalize x.");
	
	memset(to, 'y', 1000);
	check(valid_copy(to, 'y', 1000), "Failed to Initalize y.");
	
	rc = normal_copy(from, to, 1000);
	check(rc = 1000, "Normal Copy Faled: %d", rc);
	check(valid_copy(to, 'x', 1000), "Normal Copy Failed.");
	
	memset(to, 'y', 1000);
	
	rc = duffs_device(from, to, 1000);
	check(rc = 1000, "Duffs Copy Faled: %d", rc);
	check(valid_copy(to, 'x', 1000), "Duffs Copy Failed.");
	
	memset(to, 'y', 1000);
	
	rc = zeds_device(from, to, 1000);
	check(rc = 1000, "Zeds Copy Faled: %d", rc);
	check(valid_copy(to, 'x', 1000), "zeds Copy Failed.");
	
	return 0;
	error:
	return 1;
}//end of main

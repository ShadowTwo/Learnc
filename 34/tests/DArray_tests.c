#include "minunit.h"
#include "../shared/dbg.h"
#include "../src/DArray.h"
#include <stdio.h>

static DArray *array = NULL;
static int *val[2] = {NULL, NULL};

char *test_create()
{
	array = DArray_create(sizeof(int), 100);
	mu_assert(array != NULL, "DArray_create Failed.");
    	mu_assert(array->contents != NULL, "Contetns are wrong in DAraay.");
	mu_assert(array->end == 0, "End isn't at the right spot.");
	mu_assert(array->element_size == sizeof(int), "Element size is wrong.");
	mu_assert(array->max == 100, "Wrong max length on initial size.");

	return NULL;
}


void Print_Array(DArray *array)
{
	
	debug("Array(%p:%p) Max: %d End: %d Ele_Size: %d ExpandRate: %d", &array, &array->contents, array->max, array->end, array->element_size, array->expand_rate);
	//debug("Base array: %p", (void *)(array->contents));
	int x = 0;
	for(x = 0; x < DArray_max(array); x++)
	{
		debug(" (%d) %p : %p", x, &array->contents[x], array->contents[x]); 
	}
	debug("End Array");
}

char *test_ryan()
{
	array = DArray_create(sizeof(int), 5);
	array->expand_rate = 5;
	
	debug("Before adding:");
	Print_Array(array);

	int i = 0;
	int z = 0;
	 
	debug("Pushing Values into Array(%d)...", array->max);
	for(i=0; i<15; i++)
	{
		debug("Pushing: %d", i);
		
		if(i == 5)
		{
			z++;
			debug("Before expand");
			Print_Array(array);
		}

		int *val = DArray_new(array);
		*val = i;
		DArray_push(array, val);

		if(z)
		{
			debug("After expand:");
			Print_Array(array);
			z = 0;
		}
	}

	debug("...Done\nChecking Size....");

	debug("Current max: %d", array->max); 
	mu_assert(array->max == 16, "Wrong max size.");

	
	debug("...Done\nPoping...."); 

	for(i = 14; i >= 0; i--)
	{
		int *val = DArray_pop(array);
		mu_assert(val != NULL, "Shouldn't be NULL.");
		mu_assert(*val == i, "Wrong Value.");
		DArray_free(val);
	}
	debug("...Done.");

	return NULL;
}

char *test_destroy()
{
	DArray_destroy(array);

	return NULL;
}

char *test_new()
{
	val[0] = (int *) DArray_new(array);
	mu_assert(val[0] != NULL, "1: Failed to make a new element.");

	val[1] = (int *) DArray_new(array);
	mu_assert(val[1] != NULL, "2: Failed to make a new element.");

	return NULL;
}

char *test_set()
{
	DArray_set(array, 0, val[0]);
	DArray_set(array, 1, val[1]);

	return NULL;
}

char *test_get()
{
	mu_assert(DArray_get(array, 0) == val[0], "Wrong first Value.");
	mu_assert(DArray_get(array, 1) == val[1], "Wrong second Value.");

	return NULL;
}

char *test_remove()
{
	int x = 0;

	for(x = 0; x<2; x++)
	{
		int *val_check = DArray_remove(array, x);
		mu_assert(val_check != NULL, "Should not get NULL.");
		mu_assert(*val_check == *val[x], "Should get the correct value.");
		mu_assert(DArray_get(array, x) == NULL, "Should be gone.");
		DArray_free(val_check);
	}

	return NULL;
}

char *test_expand_contract()
{
	int old_max = array->max;

	DArray_expand(array);
	mu_assert((unsigned int) array->max == old_max + array->expand_rate, "Wrong size after expand.");

	DArray_contract(array);
	mu_assert((unsigned int) array->max == array->expand_rate + 1, "Should stay at the expand_rate at least");

	DArray_contract(array);
	mu_assert((unsigned int) array->max == array->expand_rate + 1, "Should stay at the expand_rate at least");

	return NULL;
}

char *test_push_pop()
{
	int i =0;
	    
	debug("Pushing Values into Array...");
	for(i=0; i<1000; i++)
	{
		debug("Pushing: %d", i);
		
		if(i == 299)
		{
			int z = 0;
			z++;
		}

		int *val = DArray_new(array);
		*val = i * 333;
		DArray_push(array, val);
	}

	debug("...Done\nChecking Size....");
	mu_assert(array->max == 1201, "Wrong max size.");
	debug("...Done\nPoping...."); 

	for(i = 999; i >= 0; i--)
	{
		int *val = DArray_pop(array);
		mu_assert(val != NULL, "Shouldn't be NULL.");
		mu_assert(*val == i * 333, "Wrong Value.");
		DArray_free(val);
	}
	debug("...Done.");

	return NULL;
}

char *test_ryan_1()
{
	array = DArray_create(sizeof(int), 5);
	array->expand_rate = 5;

	//debug("Array(%p:%p) Max: %d End: %d Ele_Size: %d ExpandRate: %d", &array, &array->contents, array->max, array->end, array->element_size, array->expand_rate);

	debug("Before adding:");
	Print_Array(array);

	int *val = DArray_new(array);
	*val = 1;
	DArray_push(array, &val);

	debug("Val: %d", *val);

	Print_Array(array);

	val = DArray_new(array);
	*val = 2;
	DArray_push(array, &val);

	debug("Val: %d", *val);

	Print_Array(array);

	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_create);
	mu_run_test(test_new);
	mu_run_test(test_set);
	mu_run_test(test_get);
	mu_run_test(test_remove);
	mu_run_test(test_expand_contract);
	mu_run_test(test_push_pop);
	mu_run_test(test_destroy);

	//mu_run_test(test_ryan);
	//mu_run_test(test_ryan_1);

	return NULL;
}

RUN_TESTS(all_tests);

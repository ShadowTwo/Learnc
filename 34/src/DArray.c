#include <stdlib.h>
#include "../shared/dbg.h"

#include "DArray.h"


int DArray_copy_contents(DArray *array, void **new_contents)
{
	check(array, "Array cannot be NULL.");
	check(array->end < array->max, "Array end past max.");
	
	void **old_contents = array->contents;
	array->contents = new_contents;

	int x = 0;
	for(x = 0; x < array->end; x++)
	{
		array->contents[x] = old_contents[x];
	}

	//free(old_contents);

	return 1;
	error:
	return 0;
}

DArray *DArray_create(size_t element_size, size_t initial_max)
{
	check(element_size > 0, "Elements size must be greater then 0");
	check(initial_max > 0, "Initial size must be greater then 0");

	DArray *new = calloc(1, sizeof(DArray));

	check(new, "Failed to create new array.");

	new->contents = calloc(initial_max, sizeof(void *));

	check(new->contents, "Failed to create Contents.");

	new->max = initial_max;
	new->element_size = element_size;

	new->expand_rate = DEFAULT_EXPAND_RATE;

	return new;

	error:
	
	if(new)
	{
		free(new);
	}

	return NULL;
}


void DArray_destroy(DArray *array)
{
	free(array->contents);
}


void DArray_clear(DArray *array)
{
	int x = 0;
	for(x = 0; x< array->max; x++)
	{
		free(array->contents[x]);
	}
}

void DArray_clear_destroy(DArray *array)
{
	DArray_clear(array);
	DArray_destroy(array);
}

int DArray_expand(DArray *array)
{
	check(array, "Array cannot be Null.");
	
	array->max = array->max + array->expand_rate;
    
	void **new_c = calloc(array->max, array->element_size);
	check(new_c, "Failed to create new array.");
	
	DArray_copy_contents(array, new_c);
    
	return 1;
	error:
	return 0;
}

int DArray_contract(DArray *array)
{
	check(array, "Array cannot be Null.");
	
	int newmax = array->end < array->expand_rate ? (int) array->expand_rate : array->end;

	void **new_c = calloc(newmax + 1, array->element_size);
	check(new_c, "Failed to create new contetns.");
	
	array->max = newmax + 1;
	
	DArray_copy_contents(array, new_c);
	
	return 1;

	error:
	return 0;
}

int DArray_push(DArray *array, void *el)
{
    if(array->end < (array->max))
	{
		array->contents[array->end] = el;
		array->end++;
		
		if(array->end == array->max)
		{
			return DArray_expand(array);
		}
		
		return 1;
	}
	return 0;
}

void *DArray_pop(DArray *array)
{
	check(array, "Array is Null.");

	if(array->end > 0)
	{
		array->end--;
		
		if((unsigned int) array->end < (array->max - array->expand_rate))
		{
			if(!DArray_contract(array))
			{
				return NULL;
			}
		}

		return array->contents[array->end];
	}
	
	error:
	return NULL;
}

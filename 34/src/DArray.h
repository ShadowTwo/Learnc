#ifndef _DArray_h
#define _DArray_h
#include <stdlib.h>
#include <assert.h>
#include "../shared/dbg.h"

typedef struct DArray
{
	int end; //used like count
	int max;
	size_t element_size;
	size_t expand_rate;
	void **contents;
} DArray;

DArray *DArray_create(size_t element_size, size_t initial_max);

void DArray_destroy(DArray *array);
void DArray_clear(DArray *array);

int DArray_expand(DArray *array);
int DArray_contract(DArray *array);

int DArray_push(DArray *array, void *el);
void *DArray_pop(DArray *array);

void DArray_clear_destroy(DArray *array);

#define DArray_Last(A) ((A)->contents[(A)->end - 1])
#define DArray_first(A) ((A)->Contents[0])
#define DArray_end(A) ((A)->end)
#define DArray_count(A) DArray_end(A)
#define DArray_max(A) ((A)->max)
#define DArray_free(A) free((A))

#define DEFAULT_EXPAND_RATE 300


static inline void DArray_set(DArray *array, int i, void *el)
{
	check(i<array->max, "Darray attemp set past max(%d)(%d)!", array->max, i);

	if(i > array->end)
	{
		array->end = i;
	}

	array->contents[i] = el;
	error:
	return;
}

static inline void *DArray_get(DArray *array, int i)
{
	check(i < array->max, "Attemp access outside of DArray.");
	return array->contents[i];
	
	error:
	return NULL;
}

static inline void *DArray_remove(DArray *array, int i)
{
	check(i < array->max, "Attemp access outside of DArray.");
	void *el = array->contents[i];

	array->contents[i] = NULL;

	return el;
	error:
	return NULL;
}

static inline void *DArray_new(DArray *array)
{
	check(array->element_size > 0, "Can't use DArray on 0 size elements.");

	return calloc(1, array->element_size);

	error:
	return NULL;
}

#endif

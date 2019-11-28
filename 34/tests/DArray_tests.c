#include "miniunit.h"
#include "../shared/dbg.h"

static DArray *array = NULL;
static int *val1 = NULL;
static int *val2 = NULL;

char *test_create()
{
	array = DArray_create(sizeof(int, 100);
	mu_assert(array != NULL, "DArray_create Failed.");

}

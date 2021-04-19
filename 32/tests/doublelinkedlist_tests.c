#include "minunit.h"
#include "../src/doublelinkedlist.h"
#include <stdlib.h>

List *list = NULL;

int *Create_INTPointer(int x)
{
	int *value = malloc(sizeof(int));
	*value = x;
	
	return value;
}

char *Test_Free()
{
	void *test = NULL;
	
	debug("Testing how free works...\nTest: %p", test);
	test = calloc(1, sizeof(int));
	debug("Test: %p", test);
	free(test);
	debug("Test: %p", test);
	debug("Done testing free.");
	
	return NULL;
}

char *test_List_create()
{
	list = List_create();
	mu_assert(list != NULL, "Failed to create list.")

	return NULL;
}

char *test_List_destroy()
{
	debug("Pre List (Address: %p)(Value: %p)", &list, list); 
	List_destroy(list);
	debug("Post List (Address: %p)(Value: %p)", &list, list);
	mu_assert(list->first == NULL, "List->first does not equal Null");
	mu_assert(list->last == NULL, "List->last does not equal Null");
	//mu_assert(list == NULL, "List does not point at NULL.");
	
	return NULL;
}

char *test_List_clear()
{
	int count = 0;
	List_clear(list);
	LIST_FOREACH(list, first, next, cur)
	{
		check(cur->value == NULL, "Failed to clear %d Value.", count);
		count++; 
	}
	error:
	return NULL;
}

char *test_functions()
{
	int i = 1;
	int *rc = 0;
	
	//mu_assert(fucntionscall(), "Failed String");
	//check(list != NULL, "Cannot test List is not created.");
	
	debug("Checking for Null list. (%p)", list);
	mu_assert(list, "Cannot test List is not created.");
	
	//mu_assert(0, "This is 0"); //Displayes the message
	//mu_assert(1, "This is 1"); //Does not Display Message
	
	debug("Checking List count: %d", list->count);
	mu_assert(list->count == 0, "List must be empty to test.");
	debug("Testing Push...");
	List_push(list, Create_INTPointer(0));
	
	mu_assert(list->count == 1, "Failed to add item to list.");
	mu_assert(*((int *)list->first->value) == 0, "Failed to Value on First Node.");
	mu_assert(*((int *)list->last->value) == 0, "Failed to Value on Last Node.");

	debug("Pushing more Items to list...");
	for(i =1; i <= 9; i++)
	{
		debug("Adding %d to list.", i);
		List_push(list, Create_INTPointer(i));
		mu_assert(*(int *)list->last->value == i, "Failed to Add Correct Value.");
	}
	
	debug("Testing list count: %d", List_count(list));
	mu_assert(List_count(list) == 10, "Failed to Push all new Items to List");
	mu_assert(list->first->next != NULL, "Failed to updated next.");
	mu_assert(list->last->prev != NULL, "Failed to update prev.");
	
	debug("Testing pop...");
	for(i=9; i >= 0; i--)
	{
		debug(" Removing: %d", i);
		rc = (int *) List_pop(list);
		mu_assert(*rc == i, "Failed to add correct value.");
		mu_assert(List_count(list) == i, "Failed to Remove Item on pop.");
	}
	
	debug("Testing that list is empty.");
	mu_assert((list->first == NULL) && (list->last == NULL), "Failed to Empty List.");
	
	 
	debug("Testing Unshift.");
	for(i = 0; i <= 9; i++)
	{
		List_unshift(list, Create_INTPointer(i));
		mu_assert(*((int *)list->first->value) == i, "Failed to Unshift");
	}
	
	mu_assert(list->count == 10, "Failed to Unshift");
	
	debug("Testing  Shift...");
	for(i=9; i >= 0; i--)
	{
		debug(" Shifting: %d", i);
		mu_assert(*((int *) List_shift(list)) == i, "Failed to add correct value.");
	}
	
	return NULL;
}

char *test_List_clear_destroy()
{
	int i = 0;
	debug("Creating a new List.");
	list = List_create();
	
	debug("Pushing new Items to list.");
	for(i =1; i <= 10; i++)
	{
		List_push(list, Create_INTPointer(i));
	}
	debug("Clearing/Destorying list...(%p::%p)", &list,list);
	mu_assert(list->first, "New List is NULL");
	mu_assert(list->last, "New List is NULL");
	List_clear_destroy(list);
	debug("Done clearing list.");
	//check(list == NULL, "Failed to Clear and Destroy List");
	
	//error:
	return NULL;
}


char *test_failures()
{
	//pass all functions a NULL List.
	
	
	return NULL;
}

char *all_tests()
{
	mu_suite_start();
	
	mu_run_test(Test_Free);
	mu_run_test(test_List_create);
	mu_run_test(test_functions);
	mu_run_test(test_List_clear);
	mu_run_test(test_List_destroy);
	mu_run_test(test_List_clear_destroy);
	
	return NULL;
}

RUN_TESTS(all_tests);

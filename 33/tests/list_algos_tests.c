#include "minunit.h"
#include "../src/doublelinkedlist.h"
#include <assert.h>
#include <string.h>

char *values[] = {"XXXX", "1234", "abcd", "xjvef", "NDSS"};

#define NUM_VALUES 5

List *Create_words()
{
	int i = 0;
	List *words = List_create();
	
	for(i =0; i < NUM_VALUES; i++)
	{
		List_push(words, values[i]);
	}
	
	return words;
}

int is_sorted(List *words)
{
	LIST_FOREACH(words, first, next, cur)
	{
		if (cur->next && strcmp(cur->value, cur->next->value) > 0 )
		{
			debug("%s %s %d", (char *)cur->value, (char *)cur->next->value, strcmp(cur->value, cur->next->value));
			return 0;
		}
	}
	return 1;
}

void Print_List(List *list)
{
	int x= 0;
	LIST_FOREACH(list, first, next, cur)
	{
		debug("%d %s", x, (char *)cur->value);
		x++;
	}
}

char *test_bubble_sort()
{
	List *words = Create_words();
	
	debug("Pre Bubble:");
	Print_List(words);
	
	int rc = List_bubble_sort(words, (List_compare) strcmp);
	
	debug("Post Bubble: %d", rc);
	Print_List(words);
	
	debug("Testing Inital sort...");
	mu_assert(rc == 1, "Bubble Sort Failed");
	mu_assert(is_sorted(words), "Words are not Sorted after Bubble Sort");
	debug("...Passed");
	
	debug("Testing PreSorted sort...");
	rc = List_bubble_sort(words, (List_compare) strcmp);
	mu_assert(rc == 1, "Bubble sort Failed of already sorted failed.");
	mu_assert(is_sorted(words), "Words should be already sorted by bubble sort.");
	debug("...Passed");

	List_destroy(words);
	
	debug("Testing Empty List sort...");
	words = List_create();
	
	rc = List_bubble_sort(words, (List_compare) strcmp);
	mu_assert(rc == 1, "Bubble sort failed on empty list.");
	mu_assert(is_sorted(words), "Words should be sorted if empty.");
	debug("...Passed");

	List_destroy(words);
	
	return NULL;
}

char *test_merge_sort()
{
	List *words = Create_words();
	
	List *res = List_merge_sort(words, (List_compare) strcmp);
	mu_assert(is_sorted(res), "Words are not sorted after merge sort.");
	
	List *res2 = List_merge_sort(res, (List_compare) strcmp);
	mu_assert(is_sorted(res2), "Should still be sorted after merge sort.");
	
	List_destroy(res2);
	List_destroy(res);
	List_destroy(words);
	
	return NULL;
}

char *all_tests()
{
	mu_suite_start();
	
	mu_run_test(test_bubble_sort);
	mu_run_test(test_merge_sort);
	
	return NULL;	
}

RUN_TESTS(all_tests);

#include "../shared/dbg.h"
#include "doublelinkedlist.h"

int List_bubble_sort(List *list, List_compare cmp)
{
	
	int rc = 0;
	void *temp = NULL;

	check(list, "List can not be NULL");
	check(list->count, "List is Empty.");

	debug("Start of Bubble Sort...");
	int x = 0;
	ListNode *cur = list->last;
	ListNode *next = list->last->prev;
	
	for(x=0;x<(List_count(list)-1);x++)
	//LIST_FOREACH(list, first, next, cur)
	{
		while(cur != list->first)
		//for(y=List_count(list);y > x; y--)
		//LIST_FOREACH(list, cur, next, cur2)
		{
			rc = cmp(cur->value, cur->prev->value);
			debug("Cur is '%s', Cur2 is '%s' rc is %d", (char *) cur->value, (char *)cur->prev->value, rc);
			if(rc < 0) 
			{
				debug("Exchanging Value: %s %s", (char *) cur->value, (char *) cur->prev->value);
				temp = cur->value;
				//debug("Temp Created");
				cur->value = cur->prev->value;
				//debug("Cur2 value moved to cur");
				cur->prev->value = temp;
				//debug("Cur value set to temp");
				debug("Exchanged Value: %s %s", (char *) cur->value, (char *) cur->prev->value);
			}
			else{debug("Not exchanging value.");}
			cur = cur->prev;
		}
		cur = next;
		next = next->prev;
		debug("Loop %d Complete!", x);

	} //end of Foreach Loop
	
	debug("End of bubble sort");
	error:
	return 1;
}

List *List_merge_sort(List *list, List_compare cmp)
{
	return NULL;
}

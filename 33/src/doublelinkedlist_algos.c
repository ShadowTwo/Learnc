#include "../shared/dbg.h"
#include "doublelinkedlist.h"

int List_bubble_sort(List *list, List_compare cmp)
{
	
	int rc = 0;
	void *temp = NULL;
	check(list, "List can not be NULL");
	debug("Start of Bubble Sort...");
	LIST_FOREACH(list, first, next, cur)
	{
		LIST_FOREACH(list, cur, next, cur2)
		{
			if(cur2 != cur) // no need to check values twice.
			{
				rc = cmp(cur->value, cur2->value);
				debug("Cur is '%s', Cur2 is '%s' rc is %d", (char *) cur->value, (char *)cur2->value, rc);
				if(rc > 0) 
				{
					debug("Exchanging Value");
					temp = cur->value;
					debug("Temp Created");
					cur->value = cur2->value;
					debug("Cur2 value moved to cur");
					cur2->value = temp;
					debug("Cur value set to temp");
				}
				else{debug("Not exchanging value.");}
			}
			else
			{
				debug("Jumping to end of sort");
				cur2 = list->first;
			} //just to end to end loop
		}
	} //end of Foreach Loop
	
	debug("End of bubble sort");
	return 1;
	error:
	debug("Error end of bubble sort");
	return 0;
}

List *List_merge_sort(List *list, List_compare cmp)
{
	return NULL;
}

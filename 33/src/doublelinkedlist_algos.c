#include "../shared/dbg.h"
#include "doublelinkedlist.h"

int List_bubble_sort(List *list, List_compare cmp)
{
	
	int rc = 0;
	void *temp = NULL;
	check(list, "List can not be NULL");
	debug("Start of Bubble Sort...");
	int x = 0;
	//ListNode *Current = list->first;
	//LIST_FOREACH(list, first, next, cur)
	for(x =0; x< List_count(list); x++)
	{
		LIST_FOREACH(list, last, prev, cur)
		{
			if(list->first != cur) // no need to check values twice.
			{
				rc = cmp(cur->value, cur->prev->value);
				debug("Cur is '%s', Cur2 is '%s' rc is %d", (char *) cur->value, (char *)cur->prev->value, rc);
				if(rc < 0) 
				{
					debug("Exchanging Value");
					temp = cur->value;
					debug("Temp Created");
					cur->value = cur->prev->value;
					debug("Cur2 value moved to cur");
					cur->prev->value = temp;
					debug("Cur value set to temp");
				}
				else{debug("Not exchanging value.");}
			}
			else
			{
				debug("Jumping to end of sort");
				cur = list->first;
			} //just to end to end loop
		}
		//Current = Current->next;
	} //end of Foreach Loop
	
	debug("End of bubble sort");
	return 1;
	error:
	debug("Error end of bubble sort");
	return 0;
}

List *List_merge_sort(List *left, List *right, List_compare cmp)
{
	List *result = List_create();
	
	check(result, "Failed to create Result.");
	debug("Sorting list (left and right)");
	debug("SizeofLeft(%d), SizeofRight(%d):", List_count(left), List_count(right));
	while(List_count(right) && List_count(left))
	{
		debug("Check 1 Start. %p", left->first);
		if(left->first->value == NULL) {debug("Left value = NULL");}
		
		debug("Check 2 Start. %p", right->first);
		if(right->first->value == NULL) {debug("Right value = NULL");}
		
		debug("Check 2 End.");
		debug("Left(%p) First(%p) Value(%p:%d)", left, left->first, left->first->value, (int *)left->first->value);
		debug("Right(%p) First(%p) Value(%p:%p::%d)", right, right->first, right->first->value, &right->first->value, (int *)right->first->value);
		debug("Merge CMP (%s),(%s)", (char *)(left->first->value), (char *)(right->first->value));//, cmp(left->first->value, right->first->value));
		debug("Check CMP End");		  
		
		if(cmp(left->first->value, right->first->value) >= 0)
		{
			debug("Pushing Left(%s)", (char *)left->first->value);
			List_push(result, ((ListNode *)List_shift(left))->value);		
		}
		else
		{
			debug("Pushing Right(%s)", (char *)right->first->value);
			List_push(result, ((ListNode *)List_shift(right))->value);
		}
	}
	
	debug("Done inital sort lists");
	
	List *NotDone = NULL;
	if(List_count(left) != 0)
	{
		NotDone = left;
	}
	else
	{
		NotDone = right;
	}
	
	debug("Found which list is not empty.");
	
	while(List_count(NotDone) > 0)
	{
		debug("Pushing NotDone(%s)", (char *)NotDone->first->value);
		List_push(result, ((ListNode *)(List_shift(NotDone)))->value);
	}
	
	debug("Finished sorting both lists.\n Starting Destroy.");
	
	List_destroy(left);
	List_destroy(right);
	
	debug("Done with destroying Left and right.");
	
	return result;
	
	error:
	debug("In Error: List_merge_Sort.");
	List_destroy(left);
	List_destroy(right);
	return NULL;
} //end of LIst_merge_sort

List *List_merge(List *list, List_compare cmp)
{
	debug("Start of list_merge s(%d)", List_count(list));
	if(List_count(list) <= 1) {return list;}
	
	List *left = List_create();
	List *right = List_create();
	int x = 0;
	ListNode *cur = list->first;
	check(left, "Failed to create Left.");
	check(right, "Failed to create Right.");
	
	debug("Start of List Merge Split");
	for(x = 0; x< List_count(list); x++)
	{
		if(x < (List_count(list)/2))
		{
			List_push(left, cur->value);
		}
		else
		{
			List_push(right, cur->value);
		}
		
		cur = cur->next;
	}
	
	debug("List Splite complete: l(%d)r(%d)", List_count(left), List_count(right));
	left = List_merge(left, cmp);
	check(left, "Error in Merge");
	
	right = List_merge(right, cmp);
	check(right, "Error in Merge");
	
	debug("Start of Merge_sort");
	return List_merge_sort(left, right, cmp);
	error:
	return NULL;
}//end of List_merge












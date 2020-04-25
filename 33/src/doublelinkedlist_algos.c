#include "../shared/dbg.h"
#include "doublelinkedlist.h"

int List_bubble_sort(List *list, List_compare cmp)
{
	
	int rc = 0;
	void *temp = NULL;

	check(list, "List cannot be NULL");
	check(list->count, "List is Empty.");

	debug("Start of Bubble Sort...");
	int x = 0;
	ListNode *cur = list->last;
	ListNode *next = list->last->prev;
	
	for(x=0;x<(List_count(list)-1);x++)
	{
		while(cur != list->first)
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

List *List_merge_merge(List *r, List *l, List_compare cmp)
{
	List *Combined = List_create();

	int totalnodes = r->count + l->count;
	int x= 0;

	ListNode *cur_r = r->first;
	ListNode *cur_l = l->first;

	for(x=0; x < totalnodes; x++)
	{
		if(cur_l == NULL)
		{
			List_push(Combined, cur_r->value);
			cur_r = cur_r->next;
		}
		else if(cur_r == NULL)
		{
			List_push(Combined, cur_l->value);
			cur_l = cur_l->next;
		}
		else if(cmp(cur_l->value, cur_r->value) < 0)
		{
			List_push(Combined, cur_l->value);
			cur_l = cur_l->next;
		}
		else
		{
			List_push(Combined, cur_r->value);
			cur_r = cur_r->next;
		}
	}

	List_destroy(r);
	List_destroy(l);

	return Combined;

}

List *List_merge_sort(List *list, List_compare cmp)
{
	//List *sorted = NULL;
	check(list, "List cannot be NULL");
	check(list->count, "List is Empty.");

	
	if(list->count > 1)
	{
		List *l = List_create();
		List *r = List_create();
		
		int x = 0;
		ListNode *cur = list->first;

		for(x=0; x < (list->count/2); x++)
		{
			List_push(l, cur->value);
			cur = cur->next;
		}
		for(; x < list->count; x++)
		{
			List_push(r, cur->value);
			cur = cur->next;
		}

		l = List_merge_sort(l, cmp);
		r = List_merge_sort(r,cmp);

		return List_merge_merge(r, l, cmp);
	}

	error:
	return list;
}

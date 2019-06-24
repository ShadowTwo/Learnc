#include "doublelinkedlist.h"
#include "../shared/dbg.h"

List *List_create()
{
	return calloc(1, sizeof(List));
} //end of List_create

void List_destroy(List *list)
{
	check(list, "List is NULL");
	debug("Starting destroy proccess...(%p::%p)", &list,list);
	LIST_FOREACH(list, first, next, cur)
	{
		if (cur->prev) {free(cur->prev);}	
	}//end of List_FOREACH
	debug("Done Freeing All nodes");
	free(list->last);
	debug("Done Freeing Last");
	free(list);
	debug("Done Freeing List");
	error:
	return;
}//end of List_destroy

void List_clear(List *list)
{
	LIST_FOREACH(list, first, next, cur) {free(cur->value);}
}//end of List_clear

void List_clear_destroy(List *list)
{
	check(list, "List cannot not be NULL");
	debug("Starting Clean (%p::%p)", &list,list);
	List_clear(list);
	debug("Starting Destory (%p::%p)", &list,list);
	List_destroy(list);
	debug("Clear Destroy Complete.");
	error:
	return;
}//end of list_clear_destory

void List_push(List *list, void *value)
{
	debug("In Push.");
	ListNode *node = calloc(1, sizeof(ListNode));
	check_mem(node);
	
	node->value = value;
	
	if(list->last == NULL)
	{
		debug("Adding to an Empty List. First(%p), Last(%p)", list->first, list->last);
		list->first = node;
		list->last = node;
		debug("Fishing updating first,last");
	}
	else
	{
		debug("Adding to end of List.");
		list->last->next = node;
		node->prev = list->last;
		list->last = node;
		debug("Finished updating Last.");
	}
	
	debug("Increasing Count");
	list->count++;
	
	debug("Finished adding.");
	error:
	return;
}//end of List_push

void *List_pop(List *list)
{
	ListNode *node = list->last;
	return node !=NULL ? List_remove(list, node) : NULL;
} //end of List_pop

void List_unshift(List *list, void *value)
{
	ListNode *node = calloc(1, sizeof(ListNode));
	check_mem(node);
	
	node->value = value;
	
	if(list->first == NULL)
	{
		list->first = node;
		list->last = node;
	}
	else
	{
		node->next = list->first;
		list->first->prev = node;
		list->first = node;
	}
	
	list->count++;
	
	error:
	return;
} //end of List_unshift

void *List_shift(List *list)
{
	ListNode *node =  list->first;
	return node != NULL ? List_remove(list, node) : NULL;
} //end of List_shift

void *List_remove(List *list, ListNode *node)
{
	void *result = NULL;
	
	debug("In List_remove.");
	
	check(list->first && list->last, "List is Empty.");
	check(node, "Node cannot be NUll.");
	
	if(node == list->first && node == list->last)
	{
		debug("Last Node in the list.");
		list->first = NULL;
		list->last = NULL;
	}
	else if(node == list->first)
	{
		debug("First Node in the List.");
		//should check that next node is not null.
		list->first = node->next;
		check(list->first != NULL, "Error state List first equal null");
		list->first->prev = NULL;
	}
	else if(node == list->last)
	{
		debug("Last Node in the list. PrevNode(%p)", node->prev);
		list->last = node->prev;
		check(list->last != NULL, "Error state: List Last equal NULL.");
		
		list->last->next = NULL;
	}
	else
	{
		debug("Node in the list");
		ListNode *after = node->next;
		ListNode *before = node->prev;
		
		after->prev = before;
		before->next = after;
	}
	
	list->count--;
	result = node->value;
	free(node);
	
	debug("Finished Removing Node.");
	error:
	return result;
} //end of List_remove

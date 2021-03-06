#ifndef doublelinkedlist_h
#define doublelinkedlist_h

#include <stdlib.h>

struct ListNode;

typedef struct ListNode
{
	struct ListNode *next;
	struct ListNode *prev;
	void *value;
} ListNode; //end of ListNode

typedef struct List
{
	int count;
	ListNode *first;
	ListNode *last;
} List;//end of List

typedef int (*List_compare)( void *a, void *b);
//typedef int (*List_compare) (List *Node1, List *Node2, Compair_func cmp);

List *List_create();
void List_destroy(List *list);
void List_clear(List *list);
void List_clear_destroy(List *list);

#define List_count(A) ((A)->count)
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)

void List_push(List *list, void *value);
void *List_pop(List *list);
void List_unshift(List *list, void *value);
void *List_shift(List*list);

void *List_remove(List *list, ListNode *node);

int List_bubble_sort(List *list, List_compare cmp); //??
List *List_merge(List *list, List_compare cmp); //??

#define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL; ListNode *V = NULL; for(V = _node = L->S; _node != NULL; V = _node = _node->M)
#endif 

#ifndef __btree_c__
#define __btree_c__

#include <stdio.h>
#include <stdlib.h>
#include "debug.h"

typedef int (*cmp_func)(void *a, void *b)

struct btnode
{
	struct node *parent;
	struct node *right;
	struct node *left;
	void *data;
	
} BTNODE;

struct btree
{
	
	BTNODE *head;
	int Total;
	typedef cmp_func cmp;
	
} BTREE;


#endif

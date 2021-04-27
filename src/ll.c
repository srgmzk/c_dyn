/*
 * =====================================================================================
 *
 *       Filename:  ll.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/15/2021 10:22:15 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

/*
	+ Add
	+ Insert
	+ Print
	+ RemoveLast
	+ RemoveFirst
	+ Iterate
	- Sorting 
	- Priority
*/

#include "../include/ll.h"



/*
int add_node(list_head *head, list_head *new_item) 
{
	list_head *tmp	= head;

	#if 0
	printf("\n\n\n=================================================\n");	
	printf("!   new_item (input)           :%p\n", new_item);
	printf("-------------------------------------------------\n");
	printf("!   node->ll_int               :%p\n",  &node->ll_int);
	printf("!   node->val                  :%d\n",  node->val);
	printf("!   node->val(ptr)             :%p\n",  &node->val);
	printf("-------------------------------------------------\n");
	printf("!   list->next :%p\n",  list_next);
	printf("!   tmp (head) :%p\n",tmp);
	
	printf("!   tmp->next (head->next) :%p\n",tmp->next);
	#endif

	while ( tmp->next )
	{
		tmp = tmp->next;
	}

	tmp->next = new_item;
	new_item->prev = tmp;
	new_item->next = NULL;	


	return 0;	
}
*/

		

int insert_node(list_head *head, list_head *new_node)
{
	list_head *tmp;
	if ( head->next == NULL)
	{
		head->next = new_node;
		new_node->next = NULL;
		new_node->prev = head;
		return 0;
	}	
	
	tmp = head->next;
	head->next = new_node;
	new_node->next = tmp;
	new_node->prev = head;
	tmp->prev = new_node;	
	return 0;
}

ll_node_A *new_int_node(int val)
{
	
	ll_node_A *node = malloc(sizeof(ll_node_A));
	node->val = rand() % val;
	return node;
}

int remove_last(list_head *head, ll_node_A *ret)
{
	ll_node_A *node = NULL; 

	if (head->next == NULL)
		return 0;
	
	while ( head->next )
		head = head->next;

	list_head *tmp = head->prev; 
	tmp->next = NULL;

	node = (ll_node_A*)list_entry(*head, ll_node_A, ll_int );

	if (ret)
	{
		memcpy(ret, node, sizeof(ll_node_A));
	}
	
	free(node);
	return 0;
}

int remove_first(list_head *head, ll_node_A *ret)
{
	ll_node_A *node = NULL; 
	list_head *lnode = NULL;
	
	if (head->next == NULL)
		return 0;

	node = (ll_node_A*)list_entry( *head->next, ll_node_A, ll_int );
	lnode = node->ll_int.next;
	head->next = lnode;


	if (ret)
		memcpy(ret, node, sizeof(ll_node_A));


	free(node);
	return 0;
}

void print_int_node(list_head *head)
{
	
	ll_node_A *node;
 	list_head *tmp;// = head->next;

	for_each_entry( tmp, ll_node_A, head )
	{
		node = list_entry( *tmp, ll_node_A, ll_int );
		printf("[ %d ]->", node->val);
	}

	printf("[NULL]\n");
	
	return; 
}



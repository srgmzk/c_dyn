/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/16/2021 12:58:32 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "ll.h"
#include "tree.h"

int main()
{
	int res;
	int count = 0;
	unsigned int depth = MAX_LIST_SIZE;

	ll_node_A *a_item, tmp_item;
	
	list_head *ll_node = NULL;
	branch_tree *root = NULL; 

	// init int head 
	list_head *head_int = malloc(sizeof(list_head));
	head_int->next = NULL;
	head_int->prev = NULL;

	list_head *new_item = NULL;

	int i;
	#if 0
	for (i = 0; i < depth; i++)
	{
		a_item = malloc(sizeof(ll_node_A));
		a_item->val = rand() % depth;

		new_item = &(a_item->ll_int);
		add_node( head_int, new_item );
		
	}

	


	for (i=10; i<20; i++)
	{
		a_item = malloc(sizeof(ll_node_A));
		a_item->val = rand() % depth;
		new_item = &(a_item->ll_int);
		insert_node(head_int, new_item);
	}

	print_int_node( head_int );	

	printf("Remove list:\n");
	count = 0;	
	for_each_entry( ll_node, ll_node_A, head_int)
		count++;
	printf("count: %d\n", count);

	for (i = 0; i < count; i++)
	{
		//res = remove_first( head_int, &tmp_item );
		res = remove_last( head_int, &tmp_item );
		//printf("removed: %d \n", tmp_item.val);
	}
	printf("**************************\n");
	#endif

	/*
		BUILD TREE
	*/
	unsigned int A = (rand() % depth);
	init_root_tree(&root, (void *)(&A));
	for (i = 1; i < depth; i++)
	{
		A = (rand() % depth);
		init_node_tree(root, (void *)(&A));
	}

	#if 0
	tmp_item = (*list_entry( *head_int->next, ll_node_A, ll_int ));
	init_root_tree(&root, (void *)&tmp_item.val);


	for_each_entry( ll_node, ll_node_A, head_int->next )
	{

		tmp_item = (*list_entry( *ll_node, ll_node_A, ll_int ));
		init_node_tree(root, (void *)&tmp_item.val);
		count++;
	}
	#endif
	print_tree(root, depth);
	delete_tree(root, depth);

	free(head_int);


	return 0;
}
	


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

	//printf("head_int: %p\n", head_int);
	int i;
	for (i = 0; i < depth; i++)
	{
		a_item = malloc(sizeof(ll_node_A));
		a_item->val = rand() % depth;

		new_item = &(a_item->ll_int);
		add_node( head_int, new_item );
		
	}

	//print_int_node(head_int);	


	for (i=10; i<20; i++)
	{
		a_item = malloc(sizeof(ll_node_A));
		a_item->val = rand() % depth;

		new_item = &(a_item->ll_int);

		insert_node(head_int, new_item);
	}

/*
	remove_last( head_int, NULL );
	tmp_A_item = malloc(sizeof(ll_node_A));
	remove_first( head_int, &tmp_A_item );
*/


	/*
		BUILD TREE
	*/
	tree_node *MyTree = calloc(1, sizeof(tree_node));


	root = &(MyTree->branch);

	tmp_item = (*list_entry( *head_int->next, ll_node_A, ll_int ));
	MyTree->val = tmp_item.val;	

	count = 0;
	#if 1 
	for_each_entry( ll_node, ll_node_A, head_int )
	{
		tmp_item = (*list_entry( *ll_node, ll_node_A, ll_int ));
		MyTree = calloc(1,sizeof(tree_node));
		MyTree->val = tmp_item.val;
		add_node_tree( root, &MyTree->branch ); 
		count++;
	}

	branch_tree *arr[depth];
	#endif
	//walk_tree_postorder(root, arr, depth, NULL);	
	//walk_tree_inorder(root, arr, depth, NULL);	
	//walk_tree_preorder(&root, arr, depth, NULL);	
	//walk_tree_preorder(root, arr, depth, print_item, NULL);	
	//print_tree(root, arr, depth);

	printf("Remove all:\n");

	count = 0;	
	for_each_entry( ll_node, ll_node_A, head_int)
	{
		count++;
	}

	printf("count: %d\n", count);


	for (i = 0; i < count; i++)
	{
		//res = remove_first( head_int, &tmp_item );
		res = remove_last( head_int, &tmp_item );
		//printf("removed: %d \n", tmp_item.val);
	}
		


	printf("**************************\n");
	print_int_node( head_int );	

	free(MyTree);
	free(head_int);



	return 0;
}
	


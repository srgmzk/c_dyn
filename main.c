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
	unsigned int depth = MAX_LIST_SIZE;
	ll_node_A *A_node = NULL;
	ll_node_A *tmp_node = NULL;
	list_head *ll_node = NULL;

	list_head *head_int;

	list_head *walked_tree = malloc(sizeof(list_head));
	walked_tree->next = NULL;
	walked_tree->prev = NULL;


	list_head *new_item;

	// init int head 
	head_int = malloc(sizeof(list_head));
	head_int->next = NULL;
	head_int->prev = NULL;

	printf("head_int: %p\n", head_int);
	int i;
	for (i = 0; i < depth; i++)
	{
		A_node = new_A_node(depth);
		new_item = &A_node->ll_int;

		A_node = malloc(sizeof(ll_node_A));
		A_node->val = rand() % depth;
		new_item = &A_node->ll_int;
/*
		tmp_node = container_of( *new_item, ll_node_A, ll_int );
		
		printf("!   A_node           :%p\n",  A_node);
		printf("-------------------------------------------------\n");
		printf("!   A_node->ll_int   :%p\n",  &A_node->ll_int);
		printf("!   ll_int           :%p\n",  new_item);
		printf("-------------------------------------------------\n");
		printf("!   A_node->val(ptr) :%p\n",  &A_node->val);
		printf("!   node->val:       :%d \n", tmp_node->val);
		printf("!   A_node->val:     :%d \n", A_node->val);
*/
		res = add_node( head_int, new_item );
		
	}
#if 0 
		new_item = &A_node->ll_int;

		A_node = malloc(sizeof(ll_node_A));
		A_node->val = 100;
		new_item = &A_node->ll_int;
		res = add_node( head_int, new_item );
#endif
//	print_int_node( head_int );	
/*
	for (i=10; i<20; i++)
	{
		A_node = new_A_node(200);
		new_item = &A_node->ll_int;

		insert_node(head_int, new_item);
	}
*/
/*
	print_node( head_int );	
	remove_last( head_int, NULL );
	print_node( head_int );	
	tmp_node = malloc(sizeof(ll_node_A));
	remove_first( head_int, &tmp_node );
*/
//	print_node( head_int );	


	/*
		BUILD TREE
	*/
	
	tree_node *MyTree = malloc(sizeof(tree_node));
	branch_tree *root = &(MyTree->branch);
	tmp_node = list_entry( *head_int->next, ll_node_A, ll_int );
	
	MyTree->val = tmp_node->val;	
//	printf("Root: %d\n", MyTree->val );	

	int count = 0;
	for_each_entry( ll_node, ll_node_A, head_int )
	{

		tmp_node = list_entry( *ll_node, ll_node_A, ll_int );

		MyTree = malloc(sizeof(tree_node));
	
		MyTree->val = tmp_node->val;
		add_node_tree( root, &MyTree->branch ); 
	//	printf("ORIG NODE ADDRESS: %p\n", &MyTree->branch);	
		count++;
	}

	branch_tree* arr[depth];
	
	walk_tree_postorder(root, arr, depth, NULL);	
	//walk_tree_inorder(root, arr, depth, NULL);	
	//walk_tree_preorder(&root, arr,depth, NULL);	
	print_tree(root, arr, depth);
	


/*
	printf("Remove all:\n");
	int count = 0;
	for_each_entry( ll_node, ll_node_A, head_int)
	{
		count++;
	}

	while(count)
	{
		remove_first( head_int, &tmp_node );
		count--;
	}

	print_node( head_int );	
*/
	


	return 0;
}
	


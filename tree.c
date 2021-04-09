/*
 * =====================================================================================
 *
 *       Filename:  tree.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/12/2021 05:07:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "tree.h"
#include <assert.h>

#define MAX_PREFIX_SIZE(depth) ((depth)*4)

void add_node_tree(branch_tree *root, branch_tree *new)
{
	assert(root);

	branch_tree *curr = root;	
	branch_tree *parent = root;	

	tree_node *curr_node =	list_entry( *curr, tree_node, branch );
	tree_node *new_node  =	list_entry( *new, tree_node, branch );
	
	while(curr)
	{
		if (curr_node->val > new_node->val)
		{	 
			/*
			printf("curr val: %d, new val: %d ( -> to left)\n", curr_node->val, new_node->val);
			printf("curr p: %p, new p: %p ( -> to left)\n", &curr_node->branch, &new_node->branch);
			*/
			parent = curr;
			curr = TO_LEFT(curr);			
	
		}
		else if (curr_node->val < new_node->val)
		{
//			printf("curr val: %d, new val: %d ( -> to right)\n", curr_node->val, new_node->val);
//			printf("curr p: %p, new p: %p ( -> to right)\n", &curr_node->branch, &new_node->branch);

			//printf("curr val: %d, new val: %d ( -> to right)\n", curr_node->val, new_node->val);
			parent = curr;
			curr = TO_RIGHT(curr);

		}
		else return;
		if (curr)
			curr_node =	list_entry( *curr, tree_node, branch );
	}
		
	curr = new;	
	curr->left = NULL;
	curr->right = NULL;

	if (curr_node->val > new_node->val)
	{
		parent->left = curr;
	}
	else if (curr_node->val < new_node->val)
	{
		parent->right = curr;
	}
	else return;

	return;
}

void push_node_to_ll(list_head *head, branch_tree **node, unsigned offset )
{	
	ll_node_tree *ll_node = malloc(sizeof(ll_node_tree));
	ll_node->node = *node;
	ll_node->offset = offset;

//	PRINT_IN_STACK(node);
	add_node( head, &ll_node->ll_tree );
}

int pop_node_from_ll(list_head *head, ll_node_tree **ret)
{
	ll_node_tree *node = NULL; 
	if (head->next == NULL)
		return 0;

	while ( head->next )
		head = head->next;

	list_head *tmp = head->prev; 

	node = list_entry(*head, ll_node_tree, ll_tree );

	tmp->next = NULL;

	if (ret)
		memcpy(*ret, node, sizeof(ll_node_A));

	free(node);
	return 0;
}

int pop_parent_from_ll(list_head *head, ll_node_tree **ret)
{
	ll_node_tree *node = NULL; 

	if (head->next == NULL)
		return 0;

	while ( head->next )
		head = head->next;

	node = list_entry(*head, ll_node_tree, ll_tree );
	//PRINT_OUT_STACK(node);

	if (ret)
		memcpy(*ret, node, sizeof(ll_node_A));

	return 0;
}

void fill_stack(list_head **head, branch_tree **node )
{
	while( *node )
	{
		push_node_to_ll(*head, node, 0);
		if (TO_LEFT(*node))
		{ 
			
			*node = TO_LEFT(*node);
			#if 0
			PRINT_IN_STACK(*node);
			#endif

		}
		else if (TO_RIGHT(*node))
		{
			*node = TO_RIGHT(*node);
			#if 0
			PRINT_IN_STACK(*node);
			#endif
		}
		else break;	
	}
}



void walk_tree_preorder(branch_tree **root, 
						branch_tree **arr,
						unsigned int depth, 
						void (*action)(branch_tree *))
{
	int idx = 0;
	int val = 0;
 	ll_node_tree *list_node = malloc(sizeof(ll_node_tree));

	list_head *phead = calloc(1, sizeof(list_head));
	INIT_HEAD(phead);

	branch_tree *parent = *root;
	branch_tree *curr = *root;

	arr[idx] = *root;
	idx++;
	printf("\n");	
	while ( TO_RIGHT(curr) || (TO_LEFT(curr)) || !STACK_IS_NULL(phead))
	{
		if ( HAVE_TWINS(curr) )
			push_node_to_ll(phead, &curr, 0);

		if (TO_LEFT(curr))
		{
			curr = TO_LEFT(curr);
		}
		else if (TO_RIGHT(curr))
		{
			curr = TO_RIGHT(curr);
		}
		else
		{
			pop_node_from_ll(phead, &list_node);
			parent = list_node->node; 
			curr = TO_RIGHT(parent); 
		}	
		if (curr)
		{
			arr[idx++] = curr;
		}
	}	
    #if 0 
	int i = 0;
	for (i = 0; i < idx ; i++)
	{


			val = (int)GET_NODE_VAL(arr[i]);
			printf(" %d ", val);
	
	}
	printf("\n");
	#endif
}

void walk_tree_postorder(branch_tree *root, 
						branch_tree **arr,
						unsigned int depth, 
						void (*action)(branch_tree *))
{
	int idx = 0;
 	ll_node_tree *list_node = malloc(sizeof(ll_node_tree));

	list_head *head = malloc(sizeof(list_head));
	INIT_HEAD(head);
	list_head *phead = malloc(sizeof(list_head));
	INIT_HEAD(phead);

	//tree_node *arr[depth]; // 100 - num of nodes in tree

	branch_tree *node = root;
	branch_tree *parent = root;
	branch_tree *pnode = NULL;
	branch_tree *curr = NULL;

	fill_stack(&head, &node);
	while (curr != root)
	{
		pop_node_from_ll(head, &list_node);	
		curr = list_node->node;  
		arr[idx++] = curr;
		/*
		 *	Get parent node (without destroy stack)
		*/

		pop_parent_from_ll(head, &list_node);	
		parent = list_node->node;

		/*
		 * Check parent node have another branch
		*/			

		if ( IS_LEFT(curr, parent) && curr != root )	
		{
			node = TO_RIGHT(parent);
			fill_stack(&head, &node);
			curr = node;
		}

		if ( HAVE_TWINS(parent) && parent != root )
		{ 
			if ( parent == pnode )
			{
				pop_node_from_ll(phead, &list_node);
				node = list_node->node;	
				pnode = NULL;
			}	
			else
			{
				push_node_to_ll(phead, &parent, 0);
				pnode = parent;
			}
		}
		
	}
	for (int i = 0; i < idx ; i++)
	{

   #if 0  
		if (arr[i])
		{
			val = (int)GET_NODE_VAL(arr[i]);
			printf(" %d ", val);
		//	PRINT_ARRAY_TREE(arr[i]);
		 }
	#endif
	}
	printf("\n");

	return;
}

void walk_tree_inorder(branch_tree *root, 
						branch_tree **arr,
						unsigned int depth, 
						void (*action)(branch_tree *))
{
	int idx = 0;
 	ll_node_tree *list_node = malloc(sizeof(ll_node_tree));

	list_head *head = malloc(sizeof(list_head));
	INIT_HEAD(head);
	list_head *phead = malloc(sizeof(list_head));
	INIT_HEAD(phead);

	//tree_node *arr[depth]; // 100 - num of nodes in tree

	branch_tree *node = root;
	branch_tree *parent = root;
	branch_tree *pnode = NULL;
	branch_tree *curr = NULL;

	fill_stack(&head, &node);
	while (curr != root)
	{
		pop_node_from_ll(head, &list_node);	
		curr = list_node->node;  
	
		arr[idx++] = curr;
		/*
		 *	Get parent node (without destroy stack)
		*/

		pop_parent_from_ll(head, &list_node);	
		parent = list_node->node;

		/*
		 * Check parent node have another branch
		*/			

		if ( IS_LEFT(curr, parent) && curr != root )	
		{
			node = TO_RIGHT(parent);
			fill_stack(&head, &node);
			curr = node;
		}

		if ( HAVE_TWINS(parent) && parent != root )
		{ 
			if ( parent == pnode )
			{
				pop_node_from_ll(phead, &list_node);
				node = list_node->node;	
				pnode = NULL;
			}	
			else
			{
				push_node_to_ll(phead, &parent, 0);
				pnode = parent;
			}
		}
		
	}

	return;
}


void print_tree(branch_tree *root, branch_tree **arr, unsigned int depth)
{
	int i = 0, x_offset = 0, val = 0;

 	ll_node_tree *list_node = malloc(sizeof(ll_node_tree));
	list_head *phead = calloc(1, sizeof(list_head));
	INIT_HEAD(phead);

	char val_str[100] = "\0";
	char offset[100]="\0";


 	char dfl_prefix[MAX_PREFIX_SIZE(depth)];
 	char new_prefix[MAX_PREFIX_SIZE(depth)];
// 	char new_prefix[100];

 	//char one_branch[MAX_PREFIX_SIZE(depth)];
	char *one_branch;// = malloc(sizeof(char));
	memset(dfl_prefix, '\0', (MAX_PREFIX_SIZE(depth)));
	branch_tree *parent = root, *curr = root; 

	walk_tree_preorder(&root, arr, depth, NULL);

	val = (int)GET_NODE_VAL(root);
	printf("%d .\n", val);
	i = 0;
	curr = root;

	while( curr->left || curr->right  || (!STACK_IS_NULL(phead)) )
	{	
		
		curr = arr[i];
		i++;

		if (!STACK_IS_NULL(phead))
		{
			pop_parent_from_ll(phead, &list_node);	
			parent = list_node->node;
		}
		#if 0 
		printf("Parent: %d ", (int)GET_NODE_VAL(parent));
		printf("Current: %d ", (int)GET_NODE_VAL(curr));
		printf("Left:");
		(curr->left)?(printf(" %d ", (int)GET_NODE_VAL(curr->left))):(printf(" - "));
		printf("Right:");
		(curr->right)?(printf(" %d ", (int)GET_NODE_VAL(curr->right))):(printf(" - "));
		printf("Stack: %d",(!STACK_IS_NULL(phead)));

		printf("\n");
		#endif

		sprintf(dfl_prefix, "%s", new_prefix);
		PRINT_OFFSET(x_offset, offset);

		if (HAVE_TWINS(parent))
		{
			if (IS_RIGHT(curr, parent))
			{
				pop_node_from_ll(phead, &list_node);
				x_offset = list_node->offset;
				dfl_prefix[x_offset] = '\0';

				PRINT_OFFSET(x_offset, offset);

				val = (int)GET_NODE_VAL(curr);
				sprintf(val_str, "[%d]R", val );
				one_branch = malloc((500 + strlen(dfl_prefix) + strlen(val_str) + strlen(val_str))*sizeof(char)); 
					
				PRINT_LEAF(dfl_prefix, one_branch, "", val_str); 
				
				printf("%s\n", one_branch);
				sprintf(new_prefix, "%s", dfl_prefix);
				x_offset = 4;
				free(one_branch);
			}

		}

		if (curr->left)
		{
			PRINT_OFFSET(x_offset, offset);
			x_offset += 4;
			val = (int)GET_NODE_VAL(curr->left);
			sprintf(val_str, "[%d]L", val );
			one_branch = malloc((500 + strlen(offset) + strlen(dfl_prefix) + strlen(val_str))*sizeof(char)); 
			PRINT_LEAF(dfl_prefix, one_branch, offset, val_str); 
			printf("%s\n", one_branch);
			sprintf(one_branch, "%s", dfl_prefix );
			free(one_branch);
		}	
		else
		{	
			PRINT_OFFSET(x_offset, offset);
			x_offset += 4;

			if ( IS_LEAF(curr) )
			{

				one_branch = malloc((500 + strlen(offset) + strlen(dfl_prefix) + strlen("[NN]L"))*sizeof(char)); 
	
				PRINT_LEAF(dfl_prefix, one_branch, offset, "[NN]L" ); 
				printf("%s\n", one_branch);
				sprintf(one_branch, "%s", dfl_prefix );
				free(one_branch);

			}

		}

		
		if (curr->right)
		{
			if (!HAVE_TWINS(curr))
			{
				val = (int)GET_NODE_VAL(curr->right);
				sprintf(val_str, "[%d]R", val );
				one_branch = malloc((500 + strlen(offset) + strlen(dfl_prefix) + strlen(val_str))*sizeof(char)); 
				PRINT_LEAF(dfl_prefix, one_branch, offset, val_str); 

		
				printf("%s\n",  one_branch);
				free(one_branch);
			}

		}	
		else
		{
			if ( IS_LEAF(curr) )
			{

				one_branch = malloc((500 + strlen(offset) + strlen(dfl_prefix) + strlen("[NN]R"))*sizeof(char)); 
				PRINT_LEAF(dfl_prefix, one_branch, offset, "[NN]R"); 
				printf("%s\n",  one_branch);
				free(one_branch);
			}

		}

		
		if (HAVE_TWINS(curr))
		{
			sprintf(new_prefix, "%s%s%s", dfl_prefix, offset, "|");
			val = (curr == root) ? 0 : strlen(new_prefix)-1;
			push_node_to_ll(phead, &curr, val);
			x_offset = 3;
		}
				
	}

}




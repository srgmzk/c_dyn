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

#include "../include/tree.h"
#include <sys/types.h>
#include <stdint.h>

#include <assert.h>
#include <stdbool.h>

#define MAX_PREFIX_SIZE(depth) ((depth)*4)

/* private methods */

static void push_node_to_ll(list_head *head, branch_tree **node, unsigned offset )
{	
	ll_node_tree *ll_node = malloc(sizeof(ll_node_tree));
	ll_node->node = *node;
	ll_node->offset = offset;
	add_node( head, &ll_node->ll_tree );
}

static int pop_node_from_ll(list_head *head, ll_node_tree **ret)
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

static int pop_parent_from_ll(list_head *head, ll_node_tree **ret)
{
	ll_node_tree *node = NULL; 

	if (head->next == NULL)
		return 0;

	while ( head->next )
		head = head->next;

	node = list_entry(*head, ll_node_tree, ll_tree );

	if (ret)
		memcpy(*ret, node, sizeof(ll_node_A));

	return 0;
}

static void fill_stack(list_head **head, branch_tree **node )
{
	while( *node )
	{
		push_node_to_ll(*head, node, 0);
		if (TO_LEFT(*node))
		{ 
			*node = TO_LEFT(*node);
		}
		else if (TO_RIGHT(*node))
		{
			*node = TO_RIGHT(*node);
		}
		else break;	
	}
}

/* basic methods */
void init_tnode(branch_tree *root, void *val)
{
	int *new_val = (int *)(val);
	branch_tree *branch;
	tree_node *Tree = calloc(1, sizeof(tree_node));
	branch = &(Tree->branch);
	Tree->val = *new_val;	

	if (add_tnode( root, branch ))
	{
//		printf("Double detected. Drop val %d\n", Tree->val);
		free(Tree);  
	}

}

void init_troot(branch_tree **root, void *val)
{
	int *new_val = (int *)(val);
	tree_node *Tree = calloc(1, sizeof(tree_node));
	*root = &(Tree->branch);
	Tree->val = *new_val;	
	add_tnode(*root, *root);
}

int add_tnode(branch_tree *root, branch_tree *new)
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
			parent = curr;
			curr = TO_LEFT(curr);			
		}
		else if (curr_node->val < new_node->val)
		{
			parent = curr;
			curr = TO_RIGHT(curr);
		}
		else return 1;

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
	else return 1;

	return 0;
}

unsigned get_num_nodes(branch_tree *root)
{
	return walk_tree_preorder(root, NULL, NULL);
}


void search_tnode(branch_tree *root, unsigned key, branch_tree **node, branch_tree **parent)
{
	*node = root;
	*parent = root;
	while ( *node )
	{
		if (GET_NODE_KEY(*node) > key )
		{
			*parent = *node;
			*node = TO_LEFT(*node);
		}
		else if (GET_NODE_KEY(*node) < key )
		{
			*parent = *node;
			*node = TO_RIGHT(*node);
		}
		else return;
	}
	if (!(*node))
		printf("Key %d not found\n", key);
	return;
}

void destroy_tree(branch_tree *root, unsigned depth)
{
	walk_tree_postorder(root, destroy_tnode, NULL);
}

branch_tree *delete_tnode(branch_tree *root, unsigned int key)
{
	branch_tree *onode = NULL;
	branch_tree *nnode = NULL; 
	branch_tree *oparent = NULL;
	branch_tree *nparent = NULL;
	
	search_tnode(root, key, &onode, &oparent);
	if (onode)
	{
		printf(">> old_node: %d, old_parent: %d\n", GET_NODE_KEY(onode), GET_NODE_KEY(oparent));   

		if (IS_LEAF(onode) && (onode!=root))
		{
			if (IS_LEFT(onode, oparent))
			{
				oparent->left = NULL;
			}
			if (IS_RIGHT(onode, oparent))
			{
				oparent->right = NULL;
			}
			goto out;
		}

		nnode = onode;

		if (GET_NODE_KEY(onode) > GET_NODE_KEY(root)) 
		{	
			NEXT_FROM_RIGHT(nnode, nparent);		
		}
		else if (GET_NODE_KEY(onode) < GET_NODE_KEY(root)) // key left from root  
		{
			NEXT_FROM_LEFT(nnode, nparent);			
		}
		else // key is root
		{
			if (TO_LEFT(onode))
			{
				nnode = onode->left;
				NEXT_FROM_LEFT(nnode, nparent);
			}
			else if (TO_RIGHT(onode))
			{
				nnode = onode->right;
				NEXT_FROM_RIGHT(nnode, nparent); 
			}
			else 
			{
				nnode = onode;
				nparent = onode;
			}
		}  
	}
	else return root;

	if (!nparent) 
	{
		root = nnode;
		nparent = nnode;
	}

	printf(">> new_node: %d, new parent: %d, old_node: %d, old_parent: %d\n", 
		GET_NODE_KEY(nnode), GET_NODE_KEY(nparent), GET_NODE_KEY(onode), GET_NODE_KEY(oparent));   
	
	if (IS_RIGHT(onode, oparent))
	{
		oparent->right = nnode;
	}
	else if (IS_LEFT(onode, oparent))	
	{
		oparent->left = nnode;
		nnode->right = TO_RIGHT(onode);
	}
	else //delete parent 
	{
		if ( oparent != nparent )
		{
			nnode->left = TO_LEFT(root);
			nnode->right = TO_RIGHT(root);
			root = nnode;
		}
		else return NULL;
	}
	if (IS_LEFT(nnode, nparent)) 
	{
		nparent->left = NULL;
	}
	if (IS_RIGHT(nnode, nparent))
	{
		nparent->right = NULL;
	}

out:
destroy_tnode(onode, NULL);
return root;

}

unsigned int walk_tree_preorder(branch_tree *root, 
						void (*action)(branch_tree *, void *arg),
						void *arg)
{
	
	unsigned int idx=0;
 	ll_node_tree *list_node = malloc(sizeof(ll_node_tree));

	list_head *phead = calloc(1, sizeof(list_head));
	INIT_HEAD(phead);

	branch_tree *parent = root;
	branch_tree *curr = root;

	if (action)
		action(root, arg);	
	idx++;
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
			if (action)
				action( curr, arg);	
			idx++;
		}
	}	

	while (phead->next) 
		pop_node_from_ll(phead, NULL);

 	free(list_node);
	free(phead);
	return idx;
}

unsigned  walk_tree_postorder(branch_tree *root, 
						void (*action)(branch_tree *, void *arg),
						void *arg)
{
	assert(root);
	int idx = 0;
	bool is_left = false, have_twins = false;
 	ll_node_tree *list_node = malloc(sizeof(ll_node_tree));

	list_head *head = malloc(sizeof(list_head));
	INIT_HEAD(head);
	list_head *phead = malloc(sizeof(list_head));
	INIT_HEAD(phead);

	branch_tree *node = root;
	branch_tree *parent = root;
	branch_tree *pnode = NULL;
	branch_tree *curr = NULL;

	fill_stack(&head, &node);

	while (curr != root)
	{
		pop_node_from_ll(head, &list_node);	
		curr = list_node->node;  

		/*
		 *	Get parent node (without destroy stack)
		*/

		pop_parent_from_ll(head, &list_node);	
		parent = list_node->node;

		if ( IS_LEFT(curr, parent) && curr != root )	
			is_left = true;
		else is_left = false;

		if ( HAVE_TWINS(parent) && parent != root )
			have_twins = true;
		else have_twins = false;

		if (action)
			action(curr, NULL);	

		idx++;


		/*
		 * Check parent node have another branch
		*/			
		if (is_left)
		{
			node = TO_RIGHT(parent);
			fill_stack(&head, &node);
			curr = node;
		}

		if (have_twins)
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

	while (head->next) 
		pop_node_from_ll(head, NULL);
	while (phead->next) 
		pop_node_from_ll(phead, NULL);

	free(head);
	free(phead);
	free(list_node);
	return idx;
}

unsigned walk_tree_inorder(branch_tree *root, 
						void (*action)(branch_tree *, void *arg),
						void *arg)
{
	int idx = 0;
 	ll_node_tree *list_node = malloc(sizeof(ll_node_tree));

	list_head *head = malloc(sizeof(list_head));
	INIT_HEAD(head);
	list_head *phead = malloc(sizeof(list_head));
	INIT_HEAD(phead);

	branch_tree *node = root;
	branch_tree *parent = root;
	branch_tree *pnode = NULL;
	branch_tree *curr = NULL;

	fill_stack(&head, &node);
	while (curr != root)
	{
		pop_node_from_ll(head, &list_node);	
		curr = list_node->node;  
	
		idx++;
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

	return idx;
}

void print_tree(branch_tree *root,  unsigned int depth)
{
	ptree_struct ptree;

 	ll_node_tree *list_node = malloc(sizeof(ll_node_tree));
	list_head *phead = calloc(1, sizeof(list_head));
	INIT_HEAD(phead);


 	char *dfl_prefix = malloc((MAX_PREFIX_SIZE(depth)/2) * sizeof(char));
 	char *new_prefix = malloc((MAX_PREFIX_SIZE(depth)/2) * sizeof(char));

	memset(dfl_prefix, 0, MAX_PREFIX_SIZE(depth)/2);
	memset(new_prefix, 0, MAX_PREFIX_SIZE(depth)/2);

	int	val = (int)GET_NODE_KEY(root);
	printf("%d .\n", val);

	ptree.x_offset = 0;
	ptree.depth = depth;
	ptree.root = root;
	ptree.parent = root;
	ptree.list_node = list_node;
	ptree.phead = phead;
	ptree.dfl_prefix = dfl_prefix;
	ptree.new_prefix = new_prefix;

	walk_tree_preorder(root, print_tnode, (void *)&ptree );

	while (phead->next) 
		pop_node_from_ll(phead, NULL);

	free(list_node); 
	free(phead);
 	free(dfl_prefix);
 	free(new_prefix);
}

/*
	Callbacks routines
*/
void destroy_tnode(branch_tree *node, void *arg)
{
	tree_node *item = list_entry(*node, tree_node, branch);
	free(item);
}

extern void printf_tb(int x, int y, uint16_t fg, uint16_t bg, const char *fmt, ...);
//			printf_tb(2, i+1, TB_WHITE, TB_GREEN, strcmd);

void print_tnode(branch_tree *curr, void *arg)
{
		unsigned int val = 0, len = 0;

		ptree_struct *ptree = (ptree_struct *)arg;

		char val_str[100]= "\0";
		char offset[1000] = "\0";
		char *one_branch = NULL;

	 	ll_node_tree *list_node = ptree->list_node;
		list_head *phead = ptree->phead;
	 	char *dfl_prefix = ptree->dfl_prefix;
	 	char *new_prefix = ptree->new_prefix; 
		unsigned int x_offset = ptree->x_offset;
		branch_tree *parent = ptree->parent;
		branch_tree *root = ptree->root; 
		
		if (!STACK_IS_NULL(phead))
		{
			pop_parent_from_ll(phead, &list_node);	
			parent = list_node->node;
		}
		#if 0 
		printf("Parent: %d ", (int)GET_NODE_KEY(parent));
		printf("Current: %d ", (int)GET_NODE_KEY(curr));
		printf("Left:");
		(curr->left)?(printf(" %d ", (int)GET_NODE_KEY(curr->left))):(printf(" - "));
		printf("Right:");
		(curr->right)?(printf(" %d ", (int)GET_NODE_KEY(curr->right))):(printf(" - "));
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

				val = (int)GET_NODE_KEY(curr);
				sprintf(val_str, "[%d]R", val );

				len = 2 * (2 * strlen(offset) + 1 + strlen(dfl_prefix) + 1 + strlen(val_str) + 1);
				one_branch = malloc(sizeof(char)*len + 1); 

				PRINT_LEAF(dfl_prefix, one_branch, "", val_str); 
				
				printf_tb(2, 1, 8, 0, one_branch);
				//printf("%s\n", one_branch);
				sprintf(new_prefix, "%s", dfl_prefix);
				x_offset = 4;
				free(one_branch);
			}

		}

		if (curr->left)
		{
			PRINT_OFFSET(x_offset, offset);
			x_offset += 4;
			val = (int)GET_NODE_KEY(curr->left);
			sprintf(val_str, "[%d]L", val );

			len = 2*(2 * strlen(offset) + 1 + strlen(dfl_prefix) + 1 + strlen(val_str) + 1);

			one_branch = malloc(len * sizeof(char) + 1); 
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

				len = 2 * ( 2 * strlen(offset) + 1 + strlen(dfl_prefix) + 1 + strlen("[NN]L" + 1));
				one_branch = malloc(len * sizeof(char) + 1); 
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
				val = (int)GET_NODE_KEY(curr->right);
				sprintf(val_str, "[%d]R", val );

				len = 2 * ( 2 * strlen(offset) + 1 + strlen(dfl_prefix) + 1 + strlen(val_str) + 1);
				one_branch = malloc(len * sizeof(char) + 1); 
				PRINT_LEAF(dfl_prefix, one_branch, offset, val_str); 
				printf("%s\n",  one_branch);
				free(one_branch);
			}

		}	
		else
		{
			if ( IS_LEAF(curr) )
			{

				int len = 2 * ( 2 * strlen(offset) + 1 + strlen(dfl_prefix) + 1 + strlen("[NN]R") + 1);
				one_branch = malloc(len * sizeof(char) + 1); 
				PRINT_LEAF(dfl_prefix, one_branch, offset, "[NN]R"); 
				printf("%s\n",  one_branch);
				free(one_branch);
			}

		}

		
		if (HAVE_TWINS(curr))
		{
			sprintf(new_prefix, "%s%s%s", dfl_prefix, offset, "|");
			val = (curr == root) ? 0 : strlen(new_prefix) - 1;
			push_node_to_ll(phead, &curr, val);
			x_offset = 3;
		}
				
	ptree->x_offset = x_offset;
	ptree->root = root;
	ptree->parent = parent;
	ptree->list_node = list_node;
	ptree->phead = phead;
	ptree->dfl_prefix = dfl_prefix;
	ptree->new_prefix = new_prefix;

}



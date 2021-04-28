/*
 * =====================================================================================
 *
 *       Filename:  tree.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/12/2021 05:07:11 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef TREE_H
#define TREE_H

#include "ll.h"
#include <stddef.h>
#include <math.h>


#define TO_LEFT(_node_) ((_node_)->left)

#define TO_RIGHT(_node_) ((_node_)->right)

#define NEXT_FROM_LEFT(_node_, _parent_)\
	while(TO_RIGHT((_node_)) && IS_NODE(TO_RIGHT(_node_)))\
	{\
		(_parent_) = (_node_);\
		(_node_)=TO_RIGHT((_node_));\
	}\
	if (TO_LEFT((_node_)))\
	{\
		(_parent_) = (_node_);\
		(_node_)=TO_LEFT((_node_));\
	}\
	
		
#define NEXT_FROM_RIGHT(_node_, _parent_)\
	if (TO_RIGHT(_node_))\
	{\
		while(TO_RIGHT(_node_))\
		{\
			(_parent_) = (_node_);\
			(_node_)=TO_RIGHT((_node_));\
		}\
	}\
	else if (TO_LEFT(_node_))\
	{\
		(_parent_) = (_node_);\
		(_node_) = (TO_LEFT(_node_));\
		if (TO_RIGHT(_node_))\
		while(TO_RIGHT(_node_))\
		{\
			(_parent_) = (_node_);\
			(_node_)=TO_RIGHT((_node_));\
		}\
	}

#define IS_LEAF(_node_) (( (_node_)->left || (_node_)->right ) ? 0:1)

#define HAVE_TWINS(_node_) (( (_node_)->left && (_node_)->right ) ? 1:0)

#define IS_NODE(_node_) (!IS_LEAF((_node_)))

#define CHANGE_NODE(_old_node_, _parent_, _new_node_) ({\
	_new_node_->left = _old_node_->left;\
	_parent_->right = _new_node_;\
});

#define IS_RIGHT(_child_, _parent_) \
	(((_parent_)->right == (_child_))?1:0)

#define IS_LEFT(_child_, _parent_) \
	(((_parent_)->left == (_child_))?1:0)

#define LEFT_TRAV(_node_, _head_)\
	while( TO_LEFT(_node_) )\
		{\
			_parent_ = _node_;\
			add_node_to_list(_node_, _head_);\
			_node_ = TO_LEFT(_node_);\
		}\

#define RIGHT_TRAV(_node_, _head_)\
	while( TO_RIGHT(_node_) )\
		{\
			_parent_ = _node_;\
			add_node_to_list(_node_, _head_);\
			_node_ = TO_RIGHT(_node_);\
		}\


#define GET_NODE_KEY(_node_)({\
		tree_node *_curr_node_ = list_entry( (*_node_), tree_node, branch );\
		_curr_node_->val;})


#define NODE_VAL(_node_, _buf_)({\
	tree_node *_curr_node_ = list_entry( (*_node_), tree_node, branch );\
	if (_node_){\
	if (_curr_node_->val)\
		sprintf((_buf_), "%d", (_curr_node_->val));\
	else sprintf((_buf_), "%c", '-');}\
    	(_buf_);})


#define IS_PARENT(_child_, _parent_)\
	((_parent_->left == _child_) || (_parent_->right == _child_))? 1:0

#define STACK_IS_NULL(_head_)\
	(((_head_)->next)?0:1)



#define GET_NODE_OFFSET(_node_)({\
		tree_node *_curr_node_ = list_entry( (*_node_), tree_node, branch );\
		_curr_node_->offset;})

#define PRINT_TNODE_DBG(_node_)({\
	char tmpstr[100];\
    printf(" left: %s (%p) \n", (((_node_)->left)?NODE_VAL((_node_)->left, tmpstr):"NaN"), ((_node_)->left));\
	strncpy(tmpstr, "\0", strlen(tmpstr)+1);\
    printf(" right: %s (%p) \n", (((_node_)->right)?NODE_VAL((_node_)->right, tmpstr):"NaN"),((_node_)->right));\
	strncpy(tmpstr, "\0", strlen(tmpstr)+1);})

#define PRINT_OFFSET(_off_,_str_)\
	memset(offset, 0, strlen(offset));\
	int _idx_ = 0;\
	for (_idx_=0; _idx_<(_off_); _idx_++)\
		((_str_)[_idx_]) = ' ';\
	((_str_)[_idx_]) = '\0';

#define PRINT_LEAF(_prefix_, _out_, _offset_, _str_)\
	sprintf((_out_), "%s%s%s%s%s%s%s%s", (_prefix_), (_offset_), "|" , "\n", (_prefix_), (_offset_), "+--", (_str_))


typedef struct branch_tree
{
	pthread_mutex_t t_lock;
	struct branch_tree *left;
	struct branch_tree *right;

} branch_tree;

typedef struct tree_node
{
	int val;
	branch_tree branch;

} tree_node, *ptr_tree_node;

typedef struct ll_node_tree
{
	branch_tree *node; //value of linked tree node (node with branches)
	unsigned int offset;
	list_head ll_tree;
} ll_node_tree;

typedef struct ptree_struct
{
	branch_tree *root;
	branch_tree *parent;
	ll_node_tree *list_node;
	list_head *phead;
 	char *dfl_prefix;// = malloc((MAX_PREFIX_SIZE(depth)/2) * sizeof(char));
 	char *new_prefix;// = malloc((MAX_PREFIX_SIZE(depth)/2) * sizeof(char));
	unsigned int x_offset;
	unsigned int depth;
} ptree_struct;

void init_troot(branch_tree **root, void *val);
void init_tnode(branch_tree *root, void *val);
int add_tnode(branch_tree *root, branch_tree *new_nodea);
unsigned get_num_nodes(branch_tree *root);
void print_tree(branch_tree *root, unsigned int depth);
void search_tnode(branch_tree *root, unsigned int key, branch_tree **node, branch_tree **parent);
branch_tree *delete_tnode(branch_tree *root, unsigned int key);
void destroy_tree(branch_tree *root, unsigned depth);


unsigned int walk_tree_inorder(branch_tree *root, void (*action)(branch_tree *, void *arg), void *arg);
unsigned int walk_tree_postorder(branch_tree *root, void (*action)(branch_tree *, void *arg), void *arg);
unsigned int walk_tree_preorder(branch_tree *root, void (*action)(branch_tree *, void *arg), void *arg);

/* callbacks */
void destroy_tnode(branch_tree *, void *);
void print_tnode(branch_tree *,  void *);
void count_tnode(branch_tree *,  void *);

#endif

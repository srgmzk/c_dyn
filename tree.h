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

#define TO_LEFT(pos) ((pos)->left)
#define TO_RIGHT(pos) ((pos)->right)

#define IS_LEAF(_node_) (( (_node_)->left || (_node_)->right ) ? 0:1)

#define HAVE_TWINS(_node_) (( (_node_)->left && (_node_)->right ) ? 1:0)

#define IS_NODE(_node_) (!IS_LEAF((_node_)))


#define IS_RIGHT(_child_, _parent_) \
	(((_parent_)->right == (_child_))? 1:0)

#define IS_LEFT(_child_, _parent_) \
	(((_parent_)->left == (_child_))? 1:0)

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


#define GET_NODE_VAL(_node_)({\
		tree_node *_curr_node_ = list_entry( (*_node_), tree_node, branch );\
		_curr_node_->val;})

#define GET_NODE_OFFSET(_node_)({\
		tree_node *_curr_node_ = list_entry( (*_node_), tree_node, branch );\
		_curr_node_->offset;})

#define NODE_VAL(_node_, _buf_)({\
		tree_node *_curr_node_ = list_entry( (*_node_), tree_node, branch );\
		if (_node_){\
		if (_curr_node_->val)\
			sprintf((_buf_), "%d", (_curr_node_->val));\
		else sprintf((_buf_), "%c", '-');}\
        (_buf_);})

#define PRINT_ARRAY_TREE(_node_)({\
			char tmpstr[100];\
		    printf(" left: %s (%p) \n", NODE_VAL((_node_)->left, tmpstr), ((_node_)->left));\
			strncpy(tmpstr, "\0", strlen(tmpstr)+1);\
		    printf(" right: %s (%p) \n", NODE_VAL((_node_)->right, tmpstr),((_node_)->right));\
			strncpy(tmpstr, "\0", strlen(tmpstr)+1);})

#define IS_PARENT(_child_, _parent_)\
	((_parent_->left == _child_) || (_parent_->right == _child_))? 1:0

#define PRINT_IN_STACK(_node_)\
			printf("to stack: ");\
			if ((_node_))\
			PRINT_NODE((_node_));\
			printf("\n");

#define PRINT_OUT_STACK(_node_)\
			printf("from stack: ");\
			if ((_node_))\
			PRINT_NODE((_node_));\
			printf("\n");

#define STACK_IS_NULL(_head_)\
	(((_head_)->next)?0:1)


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

void init_root_tree(branch_tree **root, void *val);
void init_node_tree(branch_tree *root, void *val);

int add_node_tree(branch_tree *root, branch_tree *new_nodea);
void walk_tree_inorder(branch_tree *root, unsigned int depth, void (*action)(branch_tree *));
void walk_tree_postorder(branch_tree *root, unsigned int depth, void (*action)(branch_tree *, void *arg), void *arg);
void walk_tree_preorder(branch_tree *root, unsigned int depth, void (*action)(branch_tree *, void *arg), void *arg);

void print_tree(branch_tree *root, unsigned int depth);
void print_tree_(branch_tree *root,  unsigned int depth);
void delete_tree(branch_tree *root, unsigned depth);
void print_parent(tree_node *parent);
void print_tree_node(branch_tree *root,  void *n );
void delete_tree_node(branch_tree *root, void *n );
void print_print_node(branch_tree *root,  void *n );

#endif

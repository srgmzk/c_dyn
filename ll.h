/*
 * =====================================================================================
 *
 *       Filename:  ll.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/15/2021 10:22:11 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#ifndef LL_H
#define LL_H

//#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIST_SIZE 10

#define offsetof(type, member)\
	(size_t)((char *)&((type *)(0))->member - (char *)0)

#define container_of(ptr, type, member)({\
	(type *)((char *)&(ptr) - offsetof(type, member)); })

#define list_entry(ptr, type, member)\
		container_of(ptr,type,member)

#define for_each_entry(ptr, type, head)\
	for((ptr)=(head)->next; (ptr); (ptr)=(ptr)->next)
	
#define INIT_HEAD(_head_)\
	(_head_)->next = NULL;\
	(_head_)->prev = NULL;


typedef struct list_head
{
	struct list_head *next;
	struct list_head *prev;
} list_head, *list_ptr;

typedef struct ll_node_A
{
	int val;
	list_head ll_int;

} ll_node_A, *ptr_ll_node_A;

#define add_node(_head_, _new_item_)({\
	list_head *_tmp_ = (_head_);\
	while (_tmp_->next)\
		_tmp_ = _tmp_->next;\
	_tmp_->next = (_new_item_);\
	(_new_item_)->prev = _tmp_;\
	(_new_item_)->next = NULL;})

void print_int_node(list_head *head);
//int add_node(list_head *head, list_head *new_item); 
int insert_node(list_head *head, list_head *new_node);
int remove_last(list_head *head, ll_node_A *ret);
int remove_first(list_head *head, ll_node_A *ret);
ll_node_A *new_int_node(int val);




#endif

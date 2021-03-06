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

#include "include/ll.h"
#include "include/tree.h"
#include "include/ui.h"
#include <pthread.h>
#include <assert.h>
#include <errno.h>
#include <limits.h>

uint32_t loop = 1000;


typedef struct _t_stat_
{
	uint32_t add_el;
	uint32_t del_el;
	uint32_t curr_size;
	uint32_t loops;
		
} t_stat;


//#define RAND_RANGE(N) (int)((double)rand())/((double)RAND_MAX + 1)*(N);
#define RAND_RANGE(N) (int)((double)rand())%(N)+1;

pthread_t build_tree_thread;
pthread_t stat_tree_thread;
pthread_t delete_tree_thread;
pthread_t print_tree_thread;

branch_tree *root;

static pthread_mutex_t root_mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t vol_cond = PTHREAD_COND_INITIALIZER;

void build_tree_t(t_stat *ts)
{
	uint32_t i = 0;
	uint32_t x;
	int res;

	pthread_detach(pthread_self());
	for (;;)
	{
		sleep(0);
		x = RAND_RANGE(loop);
		init_tnode(root, (void *)(&x));
		ts->add_el++;
		
	}
}


void delete_tree_t(t_stat *ts)
{
	uint32_t x = 0;
	int res = 0;
	int i = 0;
	pthread_detach(pthread_self());
	for (;;)
	{
		sleep(0);		
		x = RAND_RANGE(loop);
		if (GET_NODE_KEY(root) == x) // TODO: remove root 
			continue;

		res = pthread_mutex_lock(&(root->t_lock));
		if (res != 0)
			printf("Error: %s:%d:%s\n",__FUNCTION__, __LINE__, strerror(errno));

		root = delete_tnode(root, x);
		ts->del_el++;

		res = pthread_mutex_unlock(&(root->t_lock));
		if (res != 0)
			printf("Error: %s:%d:%s\n",__FUNCTION__, __LINE__, strerror(errno));

	}

		printf("delete tree is over \n");
}

void stat_tree_t(t_stat *ts)
{
	int res = 0;
	int i;
	uint32_t old_tsize = 0;
	pthread_detach(pthread_self());
	for (;;)
	{
		res = pthread_mutex_lock(&(root->t_lock));
		if (res != 0)
			printf("Error: %s:%d:%s\n",__FUNCTION__, __LINE__, strerror(errno));

		old_tsize = ts->curr_size;
		ts->curr_size =	get_num_nodes(root);

		res = pthread_mutex_unlock(&(root->t_lock));
		if (res != 0)
			printf("Error: %s:%d:%s\n",__FUNCTION__, __LINE__, strerror(errno));

		res = pthread_cond_signal(&vol_cond);	

		if (res != 0)
			printf("Error: %s:%d:%s\n",__FUNCTION__, __LINE__, strerror(errno));

	}
}


void print_tree_t(t_stat *ts)
{
	int ret = 0;
	int i = 0;

	uint32_t old_tsize = 0;
	while (i < ts->loops && ts->curr_size < ts->loops/2)
	{
		i++;
		printf("\x1b[H\x1b[J");
		ret = pthread_mutex_lock(&(root->t_lock));
		if (ret != 0)
			printf("Error: %s:%d:%s\n",__FUNCTION__, __LINE__, strerror(errno));
		
		while (ts->curr_size == old_tsize) 
		{
			ret = pthread_cond_wait(&vol_cond, &(root->t_lock));
		}
		
		print_tree(root);
		old_tsize = ts->curr_size;
		ret = pthread_mutex_unlock(&(root->t_lock));
		if (ret != 0)
			printf("Error: %s:%d:%s\n",__FUNCTION__, __LINE__, strerror(errno));
		printf("loops: %d, size: %d (%d), add %d, del %d\n", 
				i, ts->curr_size, (i+ts->curr_size), ts->add_el, ts->del_el );

	}

}



int main()
{

#if 0

	int ret;
	struct tb_event ev;
	uint32_t curr_cmd = 1;

	ret = tb_init();
	if (ret) {
		fprintf(stderr, "tb_init() failed with error code %d\n", ret);
		return 1;
	}

	int w = tb_width();
	int h = tb_height();

	assert(w > 6);
	assert(h > 6);
	tb_frame ctrl_frame = {.minX = 0, .maxX = 49, .minY = 0, .maxY = h-2};
	tb_frame out_frame = {.minX = 50, .maxX = (w-2), .minY = 0, .maxY = h-2};

	sprintf(ctrl_frame.frName, "%s", "main");
	sprintf(out_frame.frName, "%s", "out");

	tb_clear();
	
	draw_frame(&ctrl_frame);
	draw_frame(&out_frame);
	draw_cmd_list(&ctrl_frame,0, &curr_cmd);

	tb_select_input_mode(0);
	tb_present();

	while (tb_poll_event(&ev)) 
	{
		switch (ev.type) {
		case TB_EVENT_KEY:
			if (ev.key == TB_KEY_ESC || ev.key == TB_KEY_CTRL_C )
			{
				tb_shutdown();
				return 0;
			}
			if (ev.key == TB_KEY_ARROW_DOWN)
			{
				curr_cmd = ((curr_cmd + 1) % 7)?:1;
				draw_cmd_list(&ctrl_frame, TB_KEY_ARROW_DOWN, &curr_cmd);
		
			}
			if (ev.key == TB_KEY_ARROW_UP)
			{
				curr_cmd = ((curr_cmd - 1) % 7)?:6;
				draw_cmd_list(&ctrl_frame, TB_KEY_ARROW_UP, &curr_cmd);
			
			}
			break;

		default:
			break;
		}

		w = tb_width();
		h = tb_height();
		ctrl_frame.maxY = out_frame.maxY = h-2;
		out_frame.maxX = w-2;

		sprintf(ctrl_frame.frName, "%s", "main");
		sprintf(out_frame.frName, "%s", "out");

		tb_clear();
		draw_frame(&ctrl_frame);
		draw_cmd_list(&ctrl_frame, 0, &curr_cmd);
		draw_frame(&out_frame);

		tb_present();

	}	

#endif
///////////////////////////////////////////////////////////////////////////////////////////



//	unsigned int tsize = MAX_LIST_SIZE;

	//ll_node_A *a_item, tmp_item;
	//list_head *new_item = NULL;
	//list_head *ll_node = NULL;
	//branch_tree *root = NULL; 
	branch_tree *node = NULL; 
	branch_tree *parent = NULL; 

	// init int head 
	list_head *head_int = malloc(sizeof(list_head));
	head_int->next = NULL;
	head_int->prev = NULL;

	t_stat ts = {.add_el=0, .del_el=0};

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

	uint32_t x = (rand() % MAX_LIST_SIZE);
	int ret = pthread_mutex_lock(&root_mtx);
	if (ret != 0)
		printf("Error: %s:%d:%s\n",__FUNCTION__, __LINE__, strerror(errno));
	
	init_troot(&root, (void *)(&x));

	ret = pthread_mutex_unlock(&root_mtx);
	if (ret != 0)
		printf("Error: %s:%d:%s\n",__FUNCTION__, __LINE__, strerror(errno));


	ts.loops = loop;

	ret = pthread_create(&build_tree_thread, NULL, build_tree_t, &ts);
	if (ret != 0)
	{
		if (ret != 0)
			printf("Error: %s:%d:%s\n",__FUNCTION__, __LINE__, strerror(errno));
		return -1;
	}

#if 0 
	ret = pthread_create(&delete_tree_thread, NULL, delete_tree, &ts);
	if (ret != 0)
	{
		if (ret != 0)
			printf("Error: %s:%d:%s\n",__FUNCTION__, __LINE__, strerror(errno));
		return -1;
	}
#endif

#if 1 
	ret = pthread_create(&stat_tree_thread, NULL, stat_tree_t, &ts);
	if (ret != 0)
	{
		if (ret != 0)
			printf("Error: %s:%d:%s\n",__FUNCTION__, __LINE__, strerror(errno));
		return -1;
	}
#endif

#if 1 
	ret = pthread_create(&print_tree_thread, NULL, print_tree_t, &ts);
	if (ret != 0)
	{
		if (ret != 0)
			printf("Error: %s:%d:%s\n",__FUNCTION__, __LINE__, strerror(errno));
		return -1;
	}
#endif


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


	void *r;
	ret = pthread_join(print_tree_thread, &r);
	if (ret != 0)
		printf("Error: %s:%d:%s\n",__FUNCTION__, __LINE__, strerror(errno));

	ret = pthread_mutex_lock(&root_mtx);
	if (ret != 0)
		printf("Error: %s:%d:%s\n",__FUNCTION__, __LINE__, strerror(errno));

	ts.curr_size = get_num_nodes(root);

	ret = pthread_mutex_unlock(&root_mtx);
	if (ret != 0)
		printf("Error: %s:%d:%s\n",__FUNCTION__, __LINE__, strerror(errno));

	destroy_tree(root, ts.curr_size);

	free(head_int);
	return 0;
}
	


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
#include <assert.h>

int main()
{

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

	tb_select_input_mode(TB_INPUT_ESC | TB_INPUT_MOUSE);
	tb_clear();

	ctrl_frame.frPid = getpid();
	sprintf(ctrl_frame.frName, "%s", "main");
	draw_frame(&ctrl_frame);
	draw_cmd_list(&ctrl_frame,0, &curr_cmd);

	out_frame.frPid = getpid();
	sprintf(out_frame.frName, "%s", "out");
	draw_frame(&out_frame);

	tb_select_input_mode(0);
	tb_present();

	while (tb_poll_event(&ev)) 
	{
		switch (ev.type) {
		case TB_EVENT_KEY:
			if (ev.key == TB_KEY_ESC || ev.key == TB_KEY_CTRL_C )
			{
				goto out;
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








///////////////////////////////////////////////////////////////////////////////////////////
/*
	unsigned int depth = MAX_LIST_SIZE;

	//ll_node_A *a_item, tmp_item;
	//list_head *new_item = NULL;
	//list_head *ll_node = NULL;
	branch_tree *root = NULL; 
	branch_tree *node = NULL; 
	branch_tree *parent = NULL; 

	// init int head 
	list_head *head_int = malloc(sizeof(list_head));
	head_int->next = NULL;
	head_int->prev = NULL;


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

	//	BUILD TREE //
	
	unsigned int A = (rand() % depth);
	init_troot(&root, (void *)(&A));

	for (i = 0; i < depth; i++)
	{
		A = (rand() % depth);
		init_tnode(root, (void *)(&A));
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
	search_tnode(root, 13, &node, &parent);
	if (node)	
		PRINT_TNODE_DBG(node);
	
	print_tree(root, depth);

	
	depth = get_num_nodes(root);
	printf("depth 1: %d\n", depth);

	root = delete_tnode(root, 2);

	
	if (root)
	{
		depth = get_num_nodes(root);
		printf("depth 2: %d\n", depth);
		print_tree(root, depth);

	}	

	destroy_tree(root, depth);
	free(head_int);

*/
out:
	tb_shutdown();


	return 0;
}
	


/*
 * =====================================================================================
 *
 *       Filename:  spot.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/27/2021 10:05:23 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <assert.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../termbox.h"
#include <signal.h>


typedef struct _tb_frame_ {
	unsigned int minX; 
	unsigned int maxX;
	unsigned int minY;
	unsigned int maxY;
	unsigned int frPid;
	unsigned int lud; // left up corner (draw begin here)
	char frName[100];
} tb_frame;


#define TB_KEY_ARROW_UP         (0xFFFF-18)
#define TB_KEY_ARROW_DOWN       (0xFFFF-19)
#define TB_KEY_ARROW_LEFT       (0xFFFF-20)
#define TB_KEY_ARROW_RIGHT      (0xFFFF-21)

#define TB_KEY_ENTER            0x0D


void print_tb(const char *str, int x, int y, uint16_t fg, uint16_t bg)
{
	while (*str) {
		uint32_t uni;
		str += tb_utf8_char_to_unicode(&uni, str);
		tb_change_cell(x, y, uni, fg, bg);
		x++;
	}
}

void printf_tb(int x, int y, uint16_t fg, uint16_t bg, const char *fmt, ...)
{
	char buf[4096];
	va_list vl;
	va_start(vl, fmt);
	vsnprintf(buf, sizeof(buf), fmt, vl);
	va_end(vl);
	print_tb(buf, x, y, fg, bg);
}

void 
draw_frame(tb_frame *fr)
{
	int i = 0;
	char title[256] = "\0";

	/* frame */
	tb_change_cell(fr->minX, fr->minY, 0x250C, TB_WHITE, TB_DEFAULT);
	tb_change_cell(fr->maxX, fr->minY, 0x2510, TB_WHITE, TB_DEFAULT);
	tb_change_cell(fr->minX, fr->maxY, 0x2514, TB_WHITE, TB_DEFAULT);
	tb_change_cell(fr->maxX, fr->maxY, 0x2518, TB_WHITE, TB_DEFAULT);

	/* horizontal */
	for (i = fr->minX+1; i < fr->maxX; ++i) {
		tb_change_cell(i, fr->minY, 0x2500, TB_WHITE, TB_DEFAULT);
		tb_change_cell(i, fr->maxY, 0x2500, TB_WHITE, TB_DEFAULT);
	}
	/* vertical */
	for (i = fr->minY+1; i < fr->maxY; ++i) {
		tb_change_cell(fr->minX, i, 0x2502, TB_WHITE, TB_DEFAULT);
		tb_change_cell(fr->maxX, i, 0x2502, TB_WHITE, TB_DEFAULT);
	}

	//sprintf(title, "[ %s. pid: %d ]", fr->frName, fr->frPid);
	sprintf(title, "[ %s ]", fr->frName);
	printf_tb(fr->minX+2, 0, TB_WHITE | TB_BOLD, TB_DEFAULT, title);

}

void
draw_cmd_list(tb_frame *fr, uint32_t key, uint32_t *curr)
{
	unsigned i = 1;
	char strcmd[256] = "\0";

	for (i = 1; i < 7; i++)
	{
		sprintf(strcmd, "%d. *********** \n", i);
		if (i == *curr)
		{
			printf_tb(2, i+1, TB_WHITE, TB_GREEN, strcmd);
		}
		else 
		{
			printf_tb(2, i+1, TB_GREEN, TB_DEFAULT, strcmd);
		}
	}
	
	 
}

int main(int argc, char **argv)
{
	(void) argc; (void) argv;
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

	if (fork())
	{
		ctrl_frame.frPid = getpid();
		sprintf(ctrl_frame.frName, "%s", "main");
		draw_frame(&ctrl_frame);
		draw_cmd_list(&ctrl_frame,0, &curr_cmd);

	}	
	else  
	{
		out_frame.frPid = getpid();
		sprintf(out_frame.frName, "%s", "out");
		draw_frame(&out_frame);
		while(1);
	}

	tb_select_input_mode(0);
	tb_present();
#if 1 
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
#endif 
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

out:
	tb_shutdown();
	return 0;
}

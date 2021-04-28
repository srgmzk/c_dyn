/*
 * =====================================================================================
 *
 *       Filename:  ui.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/27/2021 08:46:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "../include/ui.h"

#include <sys/types.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>


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

void draw_frame(tb_frame *fr)
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

void draw_cmd_list(tb_frame *fr, uint32_t key, uint32_t *curr)
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

void draw_out_buff(tb_frame *fr, char *buff)
{
	printf_tb(2, 1, TB_GREEN, TB_DEFAULT, buff);
}


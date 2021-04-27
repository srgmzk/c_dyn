/*
 * =====================================================================================
 *
 *       Filename:  ui.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/27/2021 08:18:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _UI_
#define _UI_

#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>
#include "../ui/src/include/termbox.h"


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


void print_tb(const char *str, int x, int y, uint16_t fg, uint16_t bg);
void printf_tb(int x, int y, uint16_t fg, uint16_t bg, const char *fmt, ...);
void draw_frame(tb_frame *fr);
void draw_cmd_list(tb_frame *fr, uint32_t key, uint32_t *curr);

#endif

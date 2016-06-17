#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <malloc.h>
#include "dynamic_libs/os_functions.h"
#include "dynamic_libs/fs_functions.h"
#include "dynamic_libs/gx2_functions.h"
#include "dynamic_libs/sys_functions.h"
#include "dynamic_libs/vpad_functions.h"
#include "dynamic_libs/padscore_functions.h"
#include "dynamic_libs/socket_functions.h"
#include "dynamic_libs/ax_functions.h"
#include "fs/fs_utils.h"
#include "fs/sd_fat_devoptab.h"
#include "system/memory.h"
#include "utils/logger.h"
#include "utils/utils.h"
#include "common/common.h"
#include "draw.h"

void flipBuffers()
{
	OSScreenFlipBuffersEx(0);
	OSScreenFlipBuffersEx(1);
}

void drawString(int x, int line, char * string)
{
	OSScreenPutFontEx(0, x, line, string);
	OSScreenPutFontEx(1, x, line, string);
}

void fillScreen(char r,char g,char b,char a)
{
	OSScreenClearBufferEx(0, (r << 24) | (g << 16) | (b << 8) | a);
	OSScreenClearBufferEx(1, (r << 24) | (g << 16) | (b << 8) | a);
}

//Rendering in 
void drawPixel(int x, int y, char r, char g, char b, char a)
{
	OSScreenPutPixelEx(0, x, y, (r << 24) | (g << 16) | (b << 8) | a);
	OSScreenPutPixelEx(1, x, y, (r << 24) | (g << 16) | (b << 8) | a);
}

void drawLine(int x1, int y1, int x2, int y2, char r, char g, char b, char a)
{

	int x, y;
	if (x1 == x2){
		if (y1 < y2) for (y = y1; y <= y2; y++) drawPixel(x1, y, r, g, b, a);
		else for (y = y2; y <= y1; y++) drawPixel(x1, y, r, g, b, a);
	}
	else {
		if (x1 < x2) for (x = x1; x <= x2; x++) drawPixel(x, y1, r, g, b, a);
		else for (x = x2; x <= x1; x++) drawPixel(x, y1, r, g, b, a);
	}
}

void drawDiagLine(int x_start, int y_start, int y_end, int thickness, char left_right, char up_down, char r, char g, char b, char a)
{
	int x1 = x_start, y = y_start, x2;

	if (left_right != 'l' && left_right != 'r')
		return;
	if (up_down != 'u' && up_down != 'd')
		return;

	if (left_right == 'l')
		x2 = x_start - thickness;
	else
		x2 = x_start + thickness;

	if (left_right == 'l') {
		if (up_down == 'd') {
			for (;y <= y_end; ++y) {
				drawLine(x1, y, x2, y, r, g, b, a);
				--x1;
				--x2;
			}
		}
		if (up_down == 'u') {
			for (;y >= y_end; --y) {
				drawLine(x1, y, x2, y, r, g, b, a);
				--x1;
				--x2;
			}
		}
	}
	if (left_right == 'r') {
		if (up_down == 'd') {
			for (;y <= y_end; ++y) {
				drawLine(x1, y, x2, y, r, g, b, a);
				++x1;
				++x2;
			}
		}
		if (up_down == 'u') {
			for (;y >= y_end; --y) {
				drawLine(x1, y, x2, y, r, g, b, a);
				++x1;
				++x2;
			}
		}
	}
}

void drawRect(int x1, int y1, int x2, int y2, char r, char g, char b, char a)
{
	drawLine(x1, y1, x2, y1, r, g, b, a);
	drawLine(x2, y1, x2, y2, r, g, b, a);
	drawLine(x1, y2, x2, y2, r, g, b, a);
	drawLine(x1, y1, x1, y2, r, g, b, a);
}

void drawFillRect(int x1, int y1, int x2, int y2, char r, char g, char b, char a)
{
	int X1, X2, Y1, Y2, i, j;

	if (x1 < x2){
		X1 = x1;
		X2 = x2;
	}
	else {
		X1 = x2;
		X2 = x1;
	}

	if (y1 < y2){
		Y1 = y1;
		Y2 = y2;
	}
	else {
		Y1 = y2;
		Y2 = y1;
	}
	for (i = X1; i <= X2; i++){
		for (j = Y1; j <= Y2; j++){
			drawPixel(i, j, r, g, b, a);
		}
	}
}

void drawCircle(int xCen, int yCen, int radius, char r, char g, char b, char a)
{
	int x = 0;
	int y = radius;
	int p = (5 - radius * 4) / 4;
	drawCircleCircum(xCen, yCen, x, y, r, g, b, a);
	while (x < y){
		x++;
		if (p < 0){
			p += 2 * x + 1;
		}
		else{
			y--;
			p += 2 * (x - y) + 1;
		}
		drawCircleCircum(xCen, yCen, x, y, r, g, b, a);
	}
}

void drawFillCircle(int xCen, int yCen, int radius, char r, char g, char b, char a)
{
	drawCircle(xCen, yCen, radius, r, g, b, a);
	int x, y;
	for (y = -radius; y <= radius; y++){
		for (x = -radius; x <= radius; x++)
			if (x*x + y*y <= radius*radius + radius * .8f)
				drawPixel(xCen + x, yCen + y, r, g, b, a);
	}
}

void drawCircleCircum(int cx, int cy, int x, int y, char r, char g, char b, char a)
{

	if (x == 0){
		drawPixel(cx, cy + y, r, g, b, a);
		drawPixel(cx, cy - y, r, g, b, a);
		drawPixel(cx + y, cy, r, g, b, a);
		drawPixel(cx - y, cy, r, g, b, a);
	}
	if (x == y){
		drawPixel(cx + x, cy + y, r, g, b, a);
		drawPixel(cx - x, cy + y, r, g, b, a);
		drawPixel(cx + x, cy - y, r, g, b, a);
		drawPixel(cx - x, cy - y, r, g, b, a);
	}
	if (x < y){
		drawPixel(cx + x, cy + y, r, g, b, a);
		drawPixel(cx - x, cy + y, r, g, b, a);
		drawPixel(cx + x, cy - y, r, g, b, a);
		drawPixel(cx - x, cy - y, r, g, b, a);
		drawPixel(cx + y, cy + x, r, g, b, a);
		drawPixel(cx - y, cy + x, r, g, b, a);
		drawPixel(cx + y, cy - x, r, g, b, a);
		drawPixel(cx - y, cy - x, r, g, b, a);
	}
}

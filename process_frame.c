#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int process_frame(char ***input, int height, int width)
{
	static int last_height = 0, last_width = 0;
	static char **buf = NULL;
	/* allocate and init **buf */
	if((last_height != height) || (last_width != width)) {
		free(buf);
		int ptr_off = sizeof(*buf) * height;
		char *buf_data = malloc(ptr_off + sizeof(*buf_data) * height * width);
		buf = (char **)buf_data;
		buf[0] = buf_data + ptr_off;
		for(int i = 1; i < height; ++i) {
			buf[i] = buf[i-1] + width;
		}
	}
	/* copy input*/
	for(int h = 0; h < height; ++h) {
		for(int w = 0; w < width; ++w) {
			buf[h][w] = (*input)[h][w];
		}
	}
	//for each cell check every adjacent cell and decide what to do.
	for(int h = 0; h < height; ++h) {
		for(int w = 0; w < width; ++w) {
			/* mask the edges to stay in bounds */
			char mask = 0b00000000;
			if(h == 0)
				mask |= 0b11100000; /* top    */
			if(h == height - 1)
				mask |= 0b00000111; /* bottom */
			if(w == 0)
				mask |= 0b10010100; /* left   */
			if(w == width - 1)
				mask |= 0b00101001; /* right  */

			int pop_sz = 0;
			if(mask == 0) {
				pop_sz += (buf[h - 1][w - 1] == '#');
				pop_sz += (buf[h - 1][w    ] == '#');
				pop_sz += (buf[h - 1][w + 1] == '#');
				pop_sz += (buf[h    ][w - 1] == '#');
				pop_sz += (buf[h    ][w + 1] == '#');
				pop_sz += (buf[h + 1][w - 1] == '#');
				pop_sz += (buf[h + 1][w    ] == '#');
				pop_sz += (buf[h + 1][w + 1] == '#');
			} else {
				if(!(mask & 0b10000000))
					pop_sz += (buf[h - 1][w - 1] == '#');
				if(!(mask & 0b01000000))
					pop_sz += (buf[h - 1][w    ] == '#');
				if(!(mask & 0b00100000))
					pop_sz += (buf[h - 1][w + 1] == '#');
				if(!(mask & 0b00010000))
					pop_sz += (buf[h    ][w - 1] == '#');
				if(!(mask & 0b00001000))
					pop_sz += (buf[h    ][w + 1] == '#');
				if(!(mask & 0b00000100))
					pop_sz += (buf[h + 1][w - 1] == '#');
				if(!(mask & 0b00000010))
					pop_sz += (buf[h + 1][w    ] == '#');
				if(!(mask & 0b00000001))
					pop_sz += (buf[h + 1][w + 1] == '#');
			}

			/* game rules */
			switch(pop_sz) {
			case 2:
				break;
			case 3:
				(*input)[h][w] = '#';
				break;
			default:
				(*input)[h][w] = '.';
			}
		}
	}
	return 0;
}

static void debug_print(char **f, int height, int width)
{
	for(int i = 0; i < height; ++i) {
		for(int j = 0; j < width; ++j) {
			printf("%c", f[i][j]);
		}
			printf("\n");
	}
	fflush(stdout);
}

void clear_frame(char ***f, int height, int width)
{
	for(int i = 0; i < height; ++i)
		for(int j = 0; j < width; ++j)
			(*f)[i][j] = '.';
}

void copy_frame(char ***dest, char **src, int height, int width)
{
	for(int i = 0; i < height; ++i)
		for(int j = 0; j < width; ++j)
			(*dest)[i][j] = src[i][j];
}

int cmp_frame(char **f1, char **f2, int height, int width)
{
	for(int i = 0; i < height; ++i)
		for(int j = 0; j < width; ++j)
			if(f1[i][j] != f2[i][j])
				return 1;
	return 0;
}

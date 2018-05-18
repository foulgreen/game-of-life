#include "process_frame.h"
#include "minunit.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

unsigned int random_seed;

char **alloc_array(int x, int y)
{
	char **ret = malloc(y * sizeof(&ret));
	for(int i = 0; i < y; ++i) {
		ret[i] = malloc(x * sizeof(&ret[0]));
	}
	return ret;
}

void free_array(char ***a, int x, int y)
{
	for(int i = 0; i < y; ++i) {
		free(a[i]);
		a[i] = 0;
	}
	free(a);
	a = 0;
}

unsigned int get_seed(void)
{
	FILE *f = fopen("/dev/urandom", "r");
	if(!f) {

		fprintf(stderr, "couldn't find /dev/urandom using time() to init random number generator\n");
		return time(NULL);
	}
	unsigned int out;
	fread(&out, sizeof(out), 1, f);
	if(ferror(f))
		return 0;
	fclose(f);
	return out;
}

int abs(int x) { return x > 0 ? x : -x; }

/*
 * Hand verified for all edge cases
 * TODO: is this the right way to do this?
 */
int test_process_frame(char ***input, int height, int width)
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

char const *test_5x5(void)
{
	printf("In test_5x5\n");

	srand(random_seed);
	char **in = alloc_array(5, 5);
	clear_frame(&in, 5, 5);
	for(int y = 0; y < 5; ++y)
		for(int x = 0; x < 5; ++x) {
			if(rand() > (RAND_MAX/2))
				in[y][x] = '#';
			else
				in[y][x] = '.';
		}
	char **expect = alloc_array(5,5);
	copy_frame(&expect, in, 5, 5);
	test_process_frame(&expect, 5, 5);
	process_frame(&in, 5, 5);

	static char buf[64];
	snprintf(buf, 64, "rip");
	mu_assert(buf, !cmp_frame(in, expect, 5, 5));
	return 0;
}
char const *all_process_frame_tests(void)
{
	mu_run_test(test_5x5);
	return 0;
}

int tests_run;

int main(int argc, char *argv[])
{
	if(argc < 2)
		random_seed = get_seed_posix();
	else
		random_seed = atoll(argv[1]);
	printf("Using seed: %llu\n", random_seed);
	char const *result = all_process_frame_tests();
	if(result)
		printf("%s\n", result);
	else
		printf("All tests passed.\n");
	printf("tests run: %d\n", tests_run);
	return 0;
}

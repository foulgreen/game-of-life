#include "process_frame.h"
#include "minunit.h"

int abs(int x) { return x > 0 ? x : -x; }

/*
 * take 2 point (x,y) (u,v)
 * find out what the final state should be
 * return true if final state aligns with game rules
 *
 * Note:
 * When measuring the response for 2 points, there are only 2 outcomes.
 * Cells will either all die or all live.
 */
char *test_2points_5x5(int x, int y, int u, int v)
{
	int x_dist = abs(x - u);
	int y_dist = abs(y - v);
	int all_live; /* also known as is_adjacent */
	//TODO: is there a simplification for this
	all_live  = (x_dist == 1) && (y_dist == 1); /* corner     */
	all_live |= (x_dist == 1) && (y_dist == 0); /* left right */
	all_live |= (x_dist == 0) && (y_dist == 1); /* up down    */
	char in[5][5];
	clear_frame(&in, 5, 5);
	if(x < 0 || x > 4 || y < 0 || x > 4) {
		all_live = 0; /* (x,y) is outside array bounds */
	} else {
		in[y][x] = '#';
	}
	if(u < 0 || u > 4 || v < 0 || v > 4) {
		all_live = 0; /* (u,v) is outside array bounds */
	} else {
		in[v][u] = '#';
	}
	char expect[5][5];
	if(all_live)
		copy_frame(&expect, in, 5, 5);
	else /* all_die */
		clear_frame(&expect, 5, 5);
	process_frame(&in, 5, 5);
	static char buf[64];
	snprintf(buf, 64, "result for (%d,%d) and (%d,%d) is invalid",x ,y ,u ,v);
	mu_assert(buf, cmp_frame(in, expect, 5, 5));
	return 0;
}

char *test_2points_5x5(void)
{
	const char *err;
	for(int y = 0; y < 5; ++y)
		for(int x = 0; x < 5; ++x)
			for(int v = 0; v < 5; ++v)
				for(int u = 0; u < 5; ++u)
					if((err = test_2points_5x5(x, y, u, v)))
						return err;

	return 0;
}
char *all_process_frame_tests(void)
{
	mu_run_test(test_2points_5x5);
	return 0;
}

int main(void)
{
	char *result = all_process_frame_tests();
	if(result)
		printf("%s\n", result);
	else
		printf("All tests passed.\n");
	printf("tests run: %d\n", tests_run);
	return 0;
}

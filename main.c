#include "process_frame.h"
#include "print_frame.h"
#include "test_data.h"

int main(void)
{
	char **a;
	for(int i = 0; i < 20; ++i) {
		a[i] = a_frame[i];
	}
	print_frame(stdout, a, 20, 20);
	process_frame(&a, 20, 20);
	print_frame(stdout, a, 20, 20);
	process_frame(&a, 20, 20);
	print_frame(stdout, a, 20, 20);
	process_frame(&a, 20, 20);
	print_frame(stdout, a, 20, 20);

}

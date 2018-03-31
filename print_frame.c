# include "stdio.h"
# include "test_data.h"
int main ()
    {
        int x = 401;
        //printf("%lu\n", sizeof(a_frame));
        while(x >= 0)
        {
            printf ("%c", a_frame[0][x]);
            if(x %20 == 0)
                {
                    printf("\n");
                }

            x--;
        };

    return 0;
    }
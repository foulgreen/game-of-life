# include "stdio.h"
int print_frame (char **frame, int height, int width)
    {
        int x = height*width+1;
        //printf("%lu\n", sizeof(a_frame));
        while(x >= 0)
        {
            printf ("%c", frame[0][x]);
            if(x %20 == 0)
                {
                    printf("\n");
                }

            x--;
        };

    return 0;
    }

# include "stdio.h"
int print_frame (char **a_frame, int height, int width)
    {
        int x = width;
        int y = height;
        
        //printf("%lu\n", sizeof(a_frame));
        
        while(y < 400)
        {
            x == 0;
            if(y %20 == 0)
            {
                printf("\n");
            };
            printf("%c", a_frame[y][x]);
            y++;
        }
            
        while(x < 400)
        {
            y = 0;
            if(x %20 == 0)
                {
                    printf("\n");
                }    
            
            printf ("%c", a_frame[y][x]);
            x++;
        }
    return 0;
    }

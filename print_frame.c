# include <stdio.h>
/* prints the state of the game of life grid given in a_frame */
int print_frame (FILE *output_frame,char **a_frame, int height, int width)
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
            fprintf (output_frame, "%c", a_frame[y][x]);
            y++;
        }
            
        while(x < 400)
        {
            y = 0;
            if(x %20 == 0)
                {
                    printf("\n");
                }    
            
            fprintf (output_frame, "%c", a_frame[y][x]);
            x++;
        }
    return 0;
    }

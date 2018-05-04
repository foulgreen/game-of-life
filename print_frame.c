# include "stdio.h"
# include "test_data.h"
int main ()
    {
        int x = 0;
        int y = 0;
        
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
    };
#include <stdio.h>
#include <stdlib.h>

int to_int (char* a) 
{
    int res = 0;
    char ascii = *a;
    
    while (ascii != '\0' && ascii != '\n'){

        res *= 10;
        res += (ascii - 48);
        a++;
        ascii = *a;
    } 

    return res;
}

int main() {

    FILE* file_ptr;
    char str[6];
    int dial = 50;
    int ticks;
    int pass;
    int cnt = 0;

    file_ptr = fopen("input1", "r");
    if (file_ptr == NULL) exit(1);

    while (fgets(str, 6, file_ptr) != NULL) 
    {
        printf("===========\n");
        ticks = to_int(str+1);

        printf("dial: %d\n", dial);

        pass = ticks / 100;


        printf("pass: %d\n", pass);
        ticks %= 100;

        cnt += pass;
        
        printf("ticks: %c:%d\n",str[0], ticks);
        if (str[0] == 'L') 
        {
            if (dial == 0)
            {
                dial = (ticks == 0) ? 0 : 100 - ticks;
            }
            else
            {
                ticks -= dial;
                if (ticks > 0)
                {
                    cnt++;
                    dial = 100 - ticks;
                }
                else if (ticks == 0)
                {
                    cnt++;
                    dial = 0;
                }
                else
                {
                    dial = abs(ticks);
                }
            }
        }
        else
        {
            if (dial == 0)
            {
                dial = ticks;
            }
            else
            {
                ticks -= (100 - dial);
                if (ticks > 0)
                {
                    cnt++;
                    dial = ticks;
                }
                else if (ticks == 0)
                {
                    cnt++;
                    dial = 0;
                }
                else
                {
                    dial = 100 + ticks;
                }
            }
        }
        printf("dial: %d\n", dial);
            
        printf("cnt: %d\n", cnt);
    }

    printf("%d", cnt);

    fclose(file_ptr);
    return 0;
}
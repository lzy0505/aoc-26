#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


uint64_t to_int (FILE* file_ptr) 
{
    uint64_t res = 0;
    int ascii = fgetc(file_ptr);

    if (ascii == -1) return -1;
    
    while (ascii != '-' && ascii != ',' && ascii != -1){
        res *= 10;
        res += (ascii - 48);
        ascii = fgetc(file_ptr);
    } 

    return res;
}

int check (uint64_t i) {
    int nod = 0;
    uint64_t base;
    int eq;
    uint64_t zeros;
    for (uint64_t j = i;j != 0;j/=10) nod++;

    // printf("=====i: %llu ======\n", i);
    // printf("----nod: %d----\n", nod);

    for (int nod_l=1; nod_l <= nod / 2; nod_l ++)
    {
    //    printf("----nod_l: %d----\n", nod_l);
       if (nod % nod_l != 0) continue;
       zeros = 1;
       for (int j = nod_l;j>0;j--) zeros *= 10;
       // printf("zeros: %llu", zeros);

       base = i % zeros;
       
    //    printf("base: %llu\n", base);
       eq = 1;
       for (uint64_t j = i;j>0;j/=zeros)
       {
          if (eq < 0 || j % zeros != base) 
          { eq = -1; break; } 
       }
       
       if (eq > 0) return 1;
    }

    return -1;

}

int main ()
{


    FILE* file_ptr;

    file_ptr = fopen("input", "r");
    if (file_ptr == NULL) exit(1);
    
    uint64_t left, right;
    uint64_t res = 0;

    left = to_int(file_ptr);
    right = to_int(file_ptr);


    do {
    printf("left: %llu, right: %llu\n", left, right);

    for (uint64_t j = left; j<=right; j ++)
    {
        if (check (j) > 0) 
        { res += j;
          printf("yay! %llu\n", j);
        }
    }

    left = to_int(file_ptr);
    right = to_int(file_ptr);
    
    
    }while(left !=-1);

    printf("%llu", res);

    return 0;
}
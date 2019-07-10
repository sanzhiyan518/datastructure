#include "selection_sort.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MaxN  (1e4 + 10)
static int a[100000000], b[100000000];

static void generate_array(int n)
{
    int i;
    int index, temp, rest = n;

    srand((unsigned)time(NULL));

    for(i=0; i < n; ++i)
        a[i] = i + 1;

    for(int i = 0; i < n; ++i) {
        index = rand() % rest;
        b[i] = a[index];
        temp = a[index];
        a[index] = a[rest - 1];
        a[rest - 1] = temp;
        rest--;
    }
}

static void check_array_sort(int * elements, int n)
{
    int i = 0;
    for(; i < n -1; i++)
        if(elements[i] > elements[i+1])
        {
            printf("error sort %d(%d, %d)\n", i, elements[i], elements[i+1]);
            return;
        }
}


int main(int argc, char ** argv)
{
    time_t start,stop;
    int n = 100000;
    int * array = b;
    generate_array(n);
    start = time(NULL);
    selection_sort(array, n);
    stop = time(NULL);
    printf("Use Time:%ld\n",(stop-start));
    check_array_sort(array, n);

    generate_array(n);
    start = time(NULL);
    selection_sort_asm(array, n);
    stop = time(NULL);
    printf("Use Time:%ld\n",(stop-start));
    check_array_sort(array, n);

    return 0;
}

#include "bubble_sort.h"
#include "help.h"

void bubble_sort(int * elements, int n)
{
    int i, j;

    //循环最多n-1次
    for(i = n - 1; i >= 0; i --)
    {
        //循环最多i次
        int exchangeFlag = 0;
        for(j = 0; j <= i; j++)
        {
            //比较相邻元素，大者放后
            if(elements[j] > elements[j+1])
            {
                swap_int(elements, j, j+1);
                //更改交换标志
                exchangeFlag = 1;
            }
        }
        //未发生交换,则提前退出
        if (!exchangeFlag)
            break;
    }
}

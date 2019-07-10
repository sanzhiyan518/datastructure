#include "bubble_sort.h"
#include "help.h"

void bubble_sort(int * elements, int n)
{
    int i, j;

    //ѭ�����n-1��
    for(i = n - 1; i >= 0; i --)
    {
        //ѭ�����i��
        int exchangeFlag = 0;
        for(j = 0; j <= i; j++)
        {
            //�Ƚ�����Ԫ�أ����߷ź�
            if(elements[j] > elements[j+1])
            {
                swap_int(elements, j, j+1);
                //���Ľ�����־
                exchangeFlag = 1;
            }
        }
        //δ��������,����ǰ�˳�
        if (!exchangeFlag)
            break;
    }
}

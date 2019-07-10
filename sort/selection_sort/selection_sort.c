#include "selection_sort.h"
#include <help.h>
void selection_sort(int * elements, int n)
{
    int i;
    for(i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        int j = 0;
        for(j = i + 1; j <= n - 1; j++)
        {
            if(elements[j] < elements[minIndex])
            {
                minIndex = j;
            }
        }

        if(minIndex != i)
        {
            int temp = elements[i];
            elements[i] = elements[minIndex];
            elements[minIndex] = temp;
        }
    }
}

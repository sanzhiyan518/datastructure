#ifndef HELP_H_INCLUDED
#define HELP_H_INCLUDED

static void swap_int(int * elements, int i, int j)
{
    int temp = elements[i];
    elements[i] = elements[j];
    elements[j] = temp;
}


#endif // HELP_H_INCLUDED

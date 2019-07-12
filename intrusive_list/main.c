#include <stdio.h>
#include <stdlib.h>
#include "ilist.h"

typedef struct TestStruct {
    int i;
    int j;
    IListNode node;
}TestStruct;

void ilist_print(IListNode * head)
{
    IListNode * pos;
    for(pos = head->next; pos != head; pos = pos->next) {
        TestStruct * p = ilist_entry(pos, TestStruct, node);

        printf("--%d--", p->i);
    }
    printf("\n");
}

IListNode * ilist_search(IList * head, int i, int j) {
    IListNode * pos;
    for(pos = head->prev; pos != head; pos = pos->prev) {
        TestStruct * p = ilist_entry(pos, TestStruct, node);
        if(i == p->i && j == p->j)
            return &(p->node);
    }
    return NULL;
}

int main()
{
    IList head;
    int i = 0;
    IListNode * pos;

    ilist_init(&head);
    for(; i < 5; i++) {
        TestStruct * p = (TestStruct *)malloc(sizeof(TestStruct));
        p->i = i;
        p->j = i + 100;
        ilist_add_head(&head, &(p->node));
    }

    ilist_print(&head);
    for(i = 5; i < 10; i++) {
        TestStruct * p = (TestStruct *)malloc(sizeof(TestStruct));
        p->i = i;
        p->j = i + 100;
        ilist_add_tail(&head, &p->node);
    }
    ilist_print(&head);

    pos = ilist_search(&head, 2, 102);
    ilist_remove(pos);
    ilist_print(&head);
    return 0;
}

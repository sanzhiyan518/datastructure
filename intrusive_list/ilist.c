#include "ilist.h"

void _ilist_add(IListNode * cur, IListNode * prev, IListNode * next)  {
    cur->next = next;
    cur->prev = prev;
    prev->next = cur;
    next->prev = cur;
}

void ilist_init(IList * list) {
    //成员都向本身
    list->next = list->prev = list;
}

void ilist_add_head(IList * list, IListNode * cur) {
    _ilist_add(cur, list, list->next);
}

void ilist_add_tail(IList * list, IListNode * cur) {
    _ilist_add(cur, list->prev, list);
}

void ilist_remove(IListNode * cur) {
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
    cur->prev = cur->next = NULL;
}

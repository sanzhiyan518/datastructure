#include <stdlib.h>
#include "stack_list.h"

StackList stacklist_init() {
    StackList s = (StackList )malloc(sizeof(s));
    s->next = NULL;
    return s;
}

void stacklist_destroy(StackList s) {
    if(s){
        Node * n = s->next;
        while(n != NULL) {
            Node * tmp = n;
            n = n->next;
            free(tmp);
        }
        free(s);
    }
}
int stacklist_push(StackList s, void * data) {
    if(s == NULL)
        return -1;

    //ÔªËØ·ÖÅä
    Node * n = (Node *)malloc(sizeof(*n));
    n->data = data;
    n->next = s->next;
    s->next = n;
    return 0;
}

int stacklist_pop(StackList s, void ** data) {
    if(s == NULL || s->next == NULL)
        return -1;

    Node * n = s->next;
    s->next = n->next;
    *data = n->data;
    free(n);
    return 0;
}

int stacklist_empty(StackList s){
    return (s == NULL) ? 0 : (s->next == NULL ? 0 : -1);
}

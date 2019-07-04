#include <stdio.h>
#include <stdlib.h>
#include "clist.h"

CList * clist_init(compare compare) {
    CList * l = (CList *)malloc(sizeof(*l));
    l->length = 0;
    l->head = NULL;
    l->compare = compare;
    return l;
}

void clist_destroy(CList * l) {
    if (l == NULL)
        return;
    if (l->length == 0)
        goto ok;

    CListElement * e = l->head;
    do {
        CListElement * tmp = e;
        e = e->next;
        free(tmp);
    } while(e != l->head);

ok:
    free(l);
}
//prev为空表明插入到链表头
void clist_insert(CList * l, CListElement * prev, void * data) {
    CListElement * e;

    if(l == NULL)
        return;

    e = (CListElement *)malloc(sizeof(*e));
    e->data = data;
    e->next = e->prev = e;

    //如果前驱为空
    if(prev == NULL ) {
        CListElement * head = l->head;
        l->head = e;
        //如果链表为空链表加1返回
        if(head == NULL)
            goto ok;
        prev = head->prev;
    }

    //设置前驱后继怕前驱
    prev->next->prev = e;
    //设置
    e->next = prev->next;
    e->prev = prev;
    prev->next = e;

ok:
    l->length ++;
}

CListElement *  clist_search(CList * l, void * data) {
    CListElement * e;

    if(l == NULL || l->length <= 0)
        return NULL;

    //
    e = l->head;
    //搜索元素
    do{
        if(!l->compare(e->data, data))
            return e;
        e = e->next;
    } while(e != l->head);
    return NULL;
}

//删除元素
void clist_delete(CList * l, void * data) {
    CListElement * e = clist_search(l, data);
    CListElement * prev;

    if(e == NULL)
        return;

    prev = e->prev;
    //如果前驱等于本元素表明链表将要为空
    if(prev == e) {
        l->head = NULL;
    } else {
        //链表中还有多个元素
        //元素后继的前驱改为前驱
        e->next->prev = prev;
        //元素前驱的后继改为后继
        prev->next = e->next;
        //如果为链表头，修改链表头
        if(e == l->head)
            l->head = e->next;
    }

    free(e);
    l->length--;
}

void clist_print(CList *l) {
    return;
    CListElement * e = l->head;
    do {
        printf("--%d--", *(int *)(e->data));
        e = e->next;
    } while(e != l->head);
    printf("\n");
}

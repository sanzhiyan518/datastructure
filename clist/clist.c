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
//prevΪ�ձ������뵽����ͷ
void clist_insert(CList * l, CListElement * prev, void * data) {
    CListElement * e;

    if(l == NULL)
        return;

    e = (CListElement *)malloc(sizeof(*e));
    e->data = data;
    e->next = e->prev = e;

    //���ǰ��Ϊ��
    if(prev == NULL ) {
        CListElement * head = l->head;
        l->head = e;
        //�������Ϊ�������1����
        if(head == NULL)
            goto ok;
        prev = head->prev;
    }

    //����ǰ�������ǰ��
    prev->next->prev = e;
    //����
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
    //����Ԫ��
    do{
        if(!l->compare(e->data, data))
            return e;
        e = e->next;
    } while(e != l->head);
    return NULL;
}

//ɾ��Ԫ��
void clist_delete(CList * l, void * data) {
    CListElement * e = clist_search(l, data);
    CListElement * prev;

    if(e == NULL)
        return;

    prev = e->prev;
    //���ǰ�����ڱ�Ԫ�ر�������ҪΪ��
    if(prev == e) {
        l->head = NULL;
    } else {
        //�����л��ж��Ԫ��
        //Ԫ�غ�̵�ǰ����Ϊǰ��
        e->next->prev = prev;
        //Ԫ��ǰ���ĺ�̸�Ϊ���
        prev->next = e->next;
        //���Ϊ����ͷ���޸�����ͷ
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

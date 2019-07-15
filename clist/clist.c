#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clist.h"

void clist_init(CList * list, destroy destroy) {
    list->size = 0;
    list->match = NULL;
    list->destroy = destroy;
    list->head = NULL;
}

//����
void clist_destroy(CList * list) {
    if(clist_size(list) > 0) {
        //����Ϊ���ͷ������ڸ�Ԫ����ռ�ڴ�
        CListElement * head = list->head;
        CListElement * pos = head;
        CListElement * prev;
        destroy destroy = list->destroy;

        do {
            prev = pos;
            pos = pos->next;
            if(destroy != NULL)
                destroy(prev->data);
            free(prev);
        } while(pos != head);
    }

    memset(list, 0, sizeof(CList));
}

//����
int clist_ins_next(CList * list, CListElement * element, void * data) {
    CListElement * new_element;

    //�������ǰ��Ϊ���������Ȳ�Ϊ��
    if(element == NULL && clist_size(list) > 0)
        return -1;

    //��Ԫ�ط����ڴ�
    new_element  = (CListElement *)malloc(sizeof(CListElement));
    if(new_element == NULL)
        return -1;

    new_element->data = data;

    if(clist_size(list) == 0) {
        //������Ϊ�㣬����Ԫ��Ϊ����ͷ,��������ѭ��
        new_element->prev = new_element;
        new_element->next = new_element;
        list->head = new_element;
    } else {
        //��ǰ��Ԫ������
        new_element->next = element->next;
        new_element->prev = element;

        element->next->prev = new_element;
        element->next = new_element;
    }

    list->size ++;
    return 0;
}

//ɾ��
int clist_rem_next(CList * list, CListElement * element, void ** data) {
    CListElement * old_element;

    //������Ϊ0������-1
    if(clist_size(list) == 0)
        return -1;

    old_element = element->next;

    if(old_element == element) {
        //��ʱ����ֻ��һ��Ԫ�أ���������ͷΪ��
        list->head = NULL;
    } else {
        //��ɾ��Ԫ�ضϿ�����
        element->next = old_element->next;
        old_element->next->prev = element;
        //���ɾ��Ԫ��Ϊ����ͷ�����޸�����ͷΪ���Ԫ��
        if(clist_head(list) == old_element)
            list->head = old_element->next;
    }

    //��������
    *data = old_element->data;
    //
    list->size --;
    //�ͷ�Ԫ���ڴ�
    free(old_element);

    return 0;
}

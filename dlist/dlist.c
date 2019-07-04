#include <stdlib.h>
#include <stdio.h>

#include "dlist.h"

//�����ʼ��
DList * dlist_init(compare compare) {
    DList * dlist = (DList *)malloc(sizeof(*dlist));
    dlist->length = 0;
    dlist->head = dlist->tail = NULL;
    dlist->compare = compare;
    return dlist;
}

//��������
void dlist_destroy(DList * dlist) {
    DListElement * element = dlist_head(dlist);
    while(element != NULL) {
        DListElement * temp = element;
        element = element->next;
        free(temp);
    }
    if(dlist != NULL)
        free(dlist);
}

//��������������µ�����Ԫ�أ�����������Ԫ�ز��뵽��������Ԫ�ز���֮�󣬿���Ϊ��
void dlist_insert(DList * dlist, DListElement * prev, void * data) {
    DListElement * new_element = (DListElement *)malloc(sizeof(*new_element));
    new_element->data = data;
    new_element->next = new_element->prev = NULL;

    //�����Ƿ���ǰ������Ԫ�ؽ��д���
    if(prev) {
        //���Ԫ��Ϊβ�����޸�β
        if(dlist_is_tail(prev))
            dlist->tail = new_element;
        else
            //�����豸Ԫ�ص�ǰ��Ԫ��Ϊ��Ԫ��
            prev->next->prev = new_element;
        //��Ԫ�صĺ��ΪԪ�صĺ��
        new_element->next = prev->next;
        //��Ԫ�ص�ǰ����Ԫ��
        new_element->prev = prev;
        //Ԫ�صĺ��Ϊ��Ԫ��
        prev->next = new_element;
    } else {
        //������������Ԫ�أ�����뵽����ͷ
        if(dlist_size(dlist) == 0)
            dlist->tail = new_element;

        //�����ͷ
        new_element->next = dlist->head;
        //�ǿձ��޸�ԭ��ͷ��ǰ��Ϊ��Ԫ��
        if(dlist->head != NULL)
            dlist->head->prev = new_element;
        //�޸ı�ͷ
        dlist->head = new_element;
    }
    dlist->length++;
}

//���ݴ����������ݣ���������Ԫ��
DListElement * dlist_search(DList * dlist, void * data) {
    DListElement * element;
    for_each(element, dlist) {
        if(dlist->compare(dlist_data(element), data))
            break;
    }
    return element;
}

//ɾ��������ɾ���봫������������ȵ�����Ԫ��
void dlist_delete(DList * dlist, void * data) {
    DListElement * element = dlist_search(dlist, data);
    DListElement * prev;
    if(element == NULL)
        return;

    //��ʼɾ��Ԫ��
    prev = element->prev;
    //�����Ϊ����ͷ,�޸�ǰ���ĺ�̣������޸�����ͷΪԪ�صĺ��
    if(prev != NULL)
        prev->next = element->next;
    else
        dlist->head = element->next;

    //���Ϊ����β�����޸�����βΪǰ��������Ϊ��ָ�룩,�����޸ĺ�̵�ǰ��ΪԪ�ص�ǰ��
    if(dlist_is_tail(element))
        dlist->tail = prev;
    else
        element->next->prev = prev;

    dlist->length--;
    free(element);
}

//��ӡ
void dlist_print(DList * dlist) {
    return;
    DListElement * element;
    for_each(element, dlist) {
        printf("--%d--", *(int *)(element->data));
    }
    printf("\n");
}

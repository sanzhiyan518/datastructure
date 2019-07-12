#include <stdlib.h>
#include <string.h>

#include "dlist.h"

//�����ʼ��
void dlist_init(DList * list, destroy destroy) {
    list->size = 0;
    list->match = NULL;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
}

//��������
void dlist_destroy(DList * list) {
    DListElement * prev, * element = dlist_head(list);
    destroy destroy = list->destroy;

    while (element != NULL) {
        //���浱ǰ����Ԫ�����ڸ�Ԫ�ؼ������ݳ�Ա��ɾ������
        prev = element;
        element = element->next;
        //���ݳ�Ա��ɾ������
        if(destroy != NULL)
            destroy(prev->data);

        free(prev);
    }

    memset(list, 0, sizeof(DList));
}

//�������
int dlist_ins_next(DList * list, DListElement * element, void * data) {
    DListElement * new_element;

    //�������Ԫ��Ϊ���������Ȳ�Ϊ���򷵻�-1
    if(element == NULL && dlist_size(list) > 0)
        return -1;

    //��Ԫ�ط����ڴ�
    new_element  = (DListElement *)malloc(sizeof(DListElement));

    //�ڴ����ʧ�ܷ���-1
    if(new_element == NULL)
        return -1;

    //
    new_element->data = data;

    if(dlist_size(list) == 0) {
        //���Ϊ������������Ԫ��Ϊ�����ͷ��β
        new_element->next = NULL;
        new_element->prev = NULL;
        list->head = new_element;
        list->tail = new_element;
    } else {
        //�������ǰ��Ԫ�أ�����Ԫ����ǰ��Ԫ������
        new_element->next = element->next;
        new_element->prev = element;

        //���ǰ��Ԫ��Ϊ����β����������Ԫ��Ϊ����β
        if(element->next == NULL)
            list->tail = new_element;
        else
            element->next->prev = new_element;
        element->next = new_element;
    }

    list->size++;
    return 0;
}

int dlist_ins_prev(DList * list, DListElement * element, void * data) {
    DListElement * new_element;

    //�������Ԫ��Ϊ���������Ȳ�Ϊ���򷵻�-1
    if(element == NULL && dlist_size(list) > 0)
        return -1;

    //��Ԫ�ط����ڴ�
    new_element  = (DListElement *)malloc(sizeof(DListElement));

    //�ڴ����ʧ�ܷ���-1
    if(new_element == NULL)
        return -1;

    //
    new_element->data = data;

    if(dlist_size(list) == 0) {
        //���Ϊ������������Ԫ��Ϊ�����ͷ��β
        new_element->next = NULL;
        new_element->prev = NULL;
        list->head = new_element;
        list->tail = new_element;
    } else {
        //���������Ԫ�أ�����Ԫ������Ԫ������
        new_element->next = element;
        new_element->prev = element->prev;

        //������Ԫ��Ϊ����ͷ����������Ԫ��Ϊ����ͷ
        if(element->prev == NULL)
            list->head = new_element;
        else
            element->prev->next = new_element;
        element->prev = new_element;
    }

    list->size++;
    return 0;
}

int dlist_remove(DList * list, DListElement * element, void ** data) {
    if(element == NULL || dlist_size(list) == 0)
        return -1;

    //���Ԫ��Ϊ����ͷ������������ͷΪԪ�غ��Ԫ��,�����޸�ǰ��Ԫ�صĺ��Ԫ��
    if(element->prev == NULL)
        list->head = element->next;
    else
        element->prev->next = element->next;

    //���Ԫ��Ϊ����β������������βΪԪ�ص�ǰ��Ԫ�أ������޸ĺ��Ԫ�ص�ǰ��Ԫ��
    if(element->next == NULL)
        list->tail = element->prev;
    else
        element->next->prev = element->prev;

    //����Ԫ������
    *data = element->data;
    //�ͷ�Ԫ���ڴ�
    free(element);
    list->size--;

    return 0;
}

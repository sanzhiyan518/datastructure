#include <stdlib.h>
#include <stdio.h>
#include "slist.h"

//��������
List * list_init(compare compare) {
    List * list = (List *)malloc(sizeof(*list));
    list->length = 0;
    list->head = list->tail = NULL;
    list->compare = compare;
    return list;
}

//��������
void list_destroy(List * list) {
    ListElement * element;

    if(list == NULL)
        return;

    element = list_head(list);

    while (element != NULL) {
        ListElement * tmp = element;
        element = list_next(element);
        free(tmp);
    }

    free(list);
}

//��������������µ�����Ԫ�أ�����������Ԫ�ز��뵽��������Ԫ�ز���֮�󣬿���Ϊ��
void list_insert(List * list, ListElement *prev, void * data) {
    //������Ԫ��
    ListElement * element = (ListElement *)malloc(sizeof(*element));
    element->next = NULL;
    element->data = data;

    //������ǰһ������Ԫ��
    if(prev) {
        //�ж��Ƿ�Ϊ����β,����β���޸�������Ԫ��Ϊ����βԪ��
        if(list_is_tail(prev))
            list->tail = element;
        //��������
        element->next = prev->next;
        prev->next = element;
    } else {
        //����Ϊ����������Ԫ��ҲͬʱΪβ
        if(list_length(list) == 0)
            list->tail = element;
        //���뵽������Ϊͷ
        element->next = list->head;
        list->head = element;
    }
    //����Ԫ����1
    list->length++;
}

//���ݴ����������ݣ���������Ԫ��
ListElement * list_search(List * list, void * data) {
    ListElement * element;

    for_each(element, list) {
        if(list->compare(element->data, data))
            break;
    }
    return element;
}

//ɾ��������ɾ���봫������������ȵ�����Ԫ��
void list_delete(List * list, void * data) {
    ListElement * element;
    ListElement * prev = NULL;

    for_each(element, list) {
        if(list->compare(element->data, data)) {
            //���ǰһ��Ԫ��Ϊ��
            if(prev == NULL)
                //Ϊ�ձ�����Ԫ��Ϊ����ͷ���޸�����ͷ
                list->head = element->next;
            else
                //�������в��
                prev->next = element->next;

            //�жϴ�Ԫ���Ƿ�Ϊ����β���޸�����βΪǰһ������Ԫ��
            if(list_is_tail(element))
                list->tail = prev;
            //�����1
            list->length--;
            free(element);
            return;
        }
        prev = element;
    }
}

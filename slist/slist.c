#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "slist.h"

//链表初始化
void list_init(List * list, destroy destroy) {
    list->size = 0;
    list->match = NULL;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
}

//销毁链表
void list_destroy(List * list) {
    ListElement * prev, * element = list_head(list);
    destroy destroy = list->destroy;

    while (element != NULL) {
        //保存当前链表元素用于该元素及其数据成员的删除操作
        prev = element;
        element = element->next;
        //数据成员的删除操作
        if(destroy != NULL)
            destroy(prev->data);

        free(prev);
    }

    memset(list, 0, sizeof(List));
}

//插入操作
int list_ins_next(List * list, ListElement * prev, void * data) {
    //新链表元素
    ListElement * element = (ListElement *)malloc(sizeof(ListElement));

    if(element == NULL)
        return -1;

    element->next = NULL;
    element->data = data;

    if(prev) {
        //判断是否为链表尾,链表尾则修改新链表元素为链表尾元素
        if(list_is_tail(list, prev))
            list->tail = element;

        //加入链表
        element->next = prev->next;
        prev->next = element;
    } else {
        //链表为空则新链表元素也同时为尾
        if(list_size(list) == 0)
            list->tail = element;

        //加入到链表，成为头
        element->next = list->head;
        list->head = element;
    }

    list->size++;

    return 0;
}


//删除操作
int list_rem_next(List * list, ListElement * prev, void ** data) {
    ListElement * element;

    if(list_size(list) == 0)
        return -1;

    if(prev) {
        //判断传入链表元素是否为链表尾，为尾则无删除元素
        if(list_is_tail(list, prev))
            return -1;

        //获取删除链表元素
        element = prev->next;

        //若删除元素为链表尾，修改链表尾为传入链表元素
        if(list_is_tail(list, element))
            list->tail = prev;

        //修改链接关系
        prev->next = element->next;
    } else {
        //传入链表元素为空表明要删除链表头元素
        element = list->head;

        //如果链表只有一个元素，则需要修改链表尾为空
        if(list_is_tail(list, element))
            list->tail = NULL;

        //修改链接关系
        list->head = element->next;
    }

    //传出数据成员
    *data = element->data;
    free(element);
    list->size --;

    return 0;
}

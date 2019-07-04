#include <stdlib.h>
#include <stdio.h>
#include "slist.h"

//构建链表
List * list_init(compare compare) {
    List * list = (List *)malloc(sizeof(*list));
    list->length = 0;
    list->head = list->tail = NULL;
    list->compare = compare;
    return list;
}

//销毁链表
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

//插入操作，构建新的链表元素，并将此链表元素插入到传入链表元素参数之后，可以为空
void list_insert(List * list, ListElement *prev, void * data) {
    //新链表元素
    ListElement * element = (ListElement *)malloc(sizeof(*element));
    element->next = NULL;
    element->data = data;

    //若传入前一个链表元素
    if(prev) {
        //判断是否为链表尾,链表尾则修改新链表元素为链表尾元素
        if(list_is_tail(prev))
            list->tail = element;
        //加入链表
        element->next = prev->next;
        prev->next = element;
    } else {
        //链表为空则新链表元素也同时为尾
        if(list_length(list) == 0)
            list->tail = element;
        //加入到链表，成为头
        element->next = list->head;
        list->head = element;
    }
    //链表元素增1
    list->length++;
}

//根据传入卫星数据，搜索链表元素
ListElement * list_search(List * list, void * data) {
    ListElement * element;

    for_each(element, list) {
        if(list->compare(element->data, data))
            break;
    }
    return element;
}

//删除操作，删除与传入卫星数据相等的链表元素
void list_delete(List * list, void * data) {
    ListElement * element;
    ListElement * prev = NULL;

    for_each(element, list) {
        if(list->compare(element->data, data)) {
            //如果前一个元素为空
            if(prev == NULL)
                //为空表明此元素为链表头，修改链表头
                list->head = element->next;
            else
                //从链表中拆除
                prev->next = element->next;

            //判断此元素是否为链表尾，修改链表尾为前一个链表元素
            if(list_is_tail(element))
                list->tail = prev;
            //链表减1
            list->length--;
            free(element);
            return;
        }
        prev = element;
    }
}

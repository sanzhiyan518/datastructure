#include <stdlib.h>
#include <stdio.h>

#include "dlist.h"

//链表初始化
DList * dlist_init(compare compare) {
    DList * dlist = (DList *)malloc(sizeof(*dlist));
    dlist->length = 0;
    dlist->head = dlist->tail = NULL;
    dlist->compare = compare;
    return dlist;
}

//链表销毁
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

//插入操作，构建新的链表元素，并将此链表元素插入到传入链表元素参数之后，可以为空
void dlist_insert(DList * dlist, DListElement * prev, void * data) {
    DListElement * new_element = (DListElement *)malloc(sizeof(*new_element));
    new_element->data = data;
    new_element->next = new_element->prev = NULL;

    //依据是否传入前驱链表元素进行处理
    if(prev) {
        //如果元素为尾，则修改尾
        if(dlist_is_tail(prev))
            dlist->tail = new_element;
        else
            //否则设备元素的前驱元素为新元素
            prev->next->prev = new_element;
        //新元素的后继为元素的后继
        new_element->next = prev->next;
        //新元素的前驱的元素
        new_element->prev = prev;
        //元素的后继为新元素
        prev->next = new_element;
    } else {
        //如果传入空链表元素，则插入到链表头
        if(dlist_size(dlist) == 0)
            dlist->tail = new_element;

        //链入表头
        new_element->next = dlist->head;
        //非空表，修改原表头的前驱为新元素
        if(dlist->head != NULL)
            dlist->head->prev = new_element;
        //修改表头
        dlist->head = new_element;
    }
    dlist->length++;
}

//根据传入卫星数据，搜索链表元素
DListElement * dlist_search(DList * dlist, void * data) {
    DListElement * element;
    for_each(element, dlist) {
        if(dlist->compare(dlist_data(element), data))
            break;
    }
    return element;
}

//删除操作，删除与传入卫星数据相等的链表元素
void dlist_delete(DList * dlist, void * data) {
    DListElement * element = dlist_search(dlist, data);
    DListElement * prev;
    if(element == NULL)
        return;

    //开始删除元素
    prev = element->prev;
    //如果不为链表头,修改前驱的后继，否则修改链表头为元素的后继
    if(prev != NULL)
        prev->next = element->next;
    else
        dlist->head = element->next;

    //如果为链表尾，则修改链表尾为前驱（可能为空指针）,否则修改后继的前驱为元素的前驱
    if(dlist_is_tail(element))
        dlist->tail = prev;
    else
        element->next->prev = prev;

    dlist->length--;
    free(element);
}

//打印
void dlist_print(DList * dlist) {
    return;
    DListElement * element;
    for_each(element, dlist) {
        printf("--%d--", *(int *)(element->data));
    }
    printf("\n");
}

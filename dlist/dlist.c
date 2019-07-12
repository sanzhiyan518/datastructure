#include <stdlib.h>
#include <string.h>

#include "dlist.h"

//链表初始化
void dlist_init(DList * list, destroy destroy) {
    list->size = 0;
    list->match = NULL;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
}

//链表销毁
void dlist_destroy(DList * list) {
    DListElement * prev, * element = dlist_head(list);
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

    memset(list, 0, sizeof(DList));
}

//插入操作
int dlist_ins_next(DList * list, DListElement * element, void * data) {
    DListElement * new_element;

    //如果传入元素为空且链表长度不为空则返回-1
    if(element == NULL && dlist_size(list) > 0)
        return -1;

    //新元素分配内存
    new_element  = (DListElement *)malloc(sizeof(DListElement));

    //内存分配失败返回-1
    if(new_element == NULL)
        return -1;

    //
    new_element->data = data;

    if(dlist_size(list) == 0) {
        //如果为空链表则设置元素为链表的头和尾
        new_element->next = NULL;
        new_element->prev = NULL;
        list->head = new_element;
        list->tail = new_element;
    } else {
        //如果传入前驱元素，则将新元素与前驱元素链接
        new_element->next = element->next;
        new_element->prev = element;

        //如果前驱元素为链表尾，则设置新元素为链表尾
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

    //如果传入元素为空且链表长度不为空则返回-1
    if(element == NULL && dlist_size(list) > 0)
        return -1;

    //新元素分配内存
    new_element  = (DListElement *)malloc(sizeof(DListElement));

    //内存分配失败返回-1
    if(new_element == NULL)
        return -1;

    //
    new_element->data = data;

    if(dlist_size(list) == 0) {
        //如果为空链表则设置元素为链表的头和尾
        new_element->next = NULL;
        new_element->prev = NULL;
        list->head = new_element;
        list->tail = new_element;
    } else {
        //如果传入后继元素，则将新元素与后继元素链接
        new_element->next = element;
        new_element->prev = element->prev;

        //如果后继元素为链表头，则设置新元素为链表头
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

    //如果元素为链表头，则设置链表头为元素后继元素,否则修改前驱元素的后继元素
    if(element->prev == NULL)
        list->head = element->next;
    else
        element->prev->next = element->next;

    //如果元素为链表尾，则设置链表尾为元素的前驱元素，否则修改后继元素的前驱元素
    if(element->next == NULL)
        list->tail = element->prev;
    else
        element->next->prev = element->prev;

    //传出元素数据
    *data = element->data;
    //释放元素内存
    free(element);
    list->size--;

    return 0;
}

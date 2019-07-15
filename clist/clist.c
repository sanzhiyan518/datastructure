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

//销毁
void clist_destroy(CList * list) {
    if(clist_size(list) > 0) {
        //链表不为空释放链表内各元素所占内存
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

//插入
int clist_ins_next(CList * list, CListElement * element, void * data) {
    CListElement * new_element;

    //如果传入前驱为空且链表长度不为零
    if(element == NULL && clist_size(list) > 0)
        return -1;

    //新元素分配内存
    new_element  = (CListElement *)malloc(sizeof(CListElement));
    if(new_element == NULL)
        return -1;

    new_element->data = data;

    if(clist_size(list) == 0) {
        //链表长度为零，设置元素为链表头,且自身构成循环
        new_element->prev = new_element;
        new_element->next = new_element;
        list->head = new_element;
    } else {
        //与前驱元素链接
        new_element->next = element->next;
        new_element->prev = element;

        element->next->prev = new_element;
        element->next = new_element;
    }

    list->size ++;
    return 0;
}

//删除
int clist_rem_next(CList * list, CListElement * element, void ** data) {
    CListElement * old_element;

    //链表长度为0，返回-1
    if(clist_size(list) == 0)
        return -1;

    old_element = element->next;

    if(old_element == element) {
        //此时链表只有一个元素，设置链表头为空
        list->head = NULL;
    } else {
        //将删除元素断开链接
        element->next = old_element->next;
        old_element->next->prev = element;
        //如果删除元素为链表头，则修改链表头为后继元素
        if(clist_head(list) == old_element)
            list->head = old_element->next;
    }

    //传出数据
    *data = old_element->data;
    //
    list->size --;
    //释放元素内存
    free(old_element);

    return 0;
}

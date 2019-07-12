#ifndef ILIST_H_INCLUDED
#define ILIST_H_INCLUDED

#include <stdio.h>

typedef struct IListNode_ {
    struct IListNode_ * prev;
    struct IListNode_ * next;
} IList, IListNode;


//初始化一个链表，一般用于初始化链表头
void ilist_init(IList * list);

//在链表头追加元素
void ilist_add_head(IList * list, IListNode * cur);

//在链表尾前追加元素
void ilist_add_tail(IList * list, IListNode * cur);

//链表元素删除
void ilist_remove(IListNode * cur);

//获取链表元素所在数据指针
#define ilist_entry(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)(&((type *)0)->member)))


#endif // ILIST_H_INCLUDED

#ifndef ILIST_H_INCLUDED
#define ILIST_H_INCLUDED

#include <stdio.h>

typedef struct IListNode_ {
    struct IListNode_ * prev;
    struct IListNode_ * next;
} IList, IListNode;


//��ʼ��һ������һ�����ڳ�ʼ������ͷ
void ilist_init(IList * list);

//������ͷ׷��Ԫ��
void ilist_add_head(IList * list, IListNode * cur);

//������βǰ׷��Ԫ��
void ilist_add_tail(IList * list, IListNode * cur);

//����Ԫ��ɾ��
void ilist_remove(IListNode * cur);

//��ȡ����Ԫ����������ָ��
#define ilist_entry(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)(&((type *)0)->member)))


#endif // ILIST_H_INCLUDED

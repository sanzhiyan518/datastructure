#ifndef DLIST_H_
#define DLIST_H_
//
typedef void (*destroy)(void * data);
typedef int (*match)(const void *data1, const void * data2);

//双向链表元素
typedef struct DListElement_
{
    void * data;                     //数据成员
    struct DListElement_ * prev;     //前驱元素
    struct DListElement_ * next;     //后继元素
} DListElement;

//双向链表定义
typedef struct DList_
{
    long size;  //链表长度
    match  match;  //元素比较函数
    destroy destroy;  //元素销毁函数
    DListElement * head; //链表头
    DListElement * tail;  //链表尾
}DList;

//链表操作集合
//链表初始化
void dlist_init(DList * list, destroy destroy);
void dlist_init_asm(DList * list, destroy destroy);

//链表销毁
void dlist_destroy(DList * list);
void dlist_destroy_asm(DList * list);

//插入操作
int dlist_ins_next(DList * list, DListElement * element, void * data);
int dlist_ins_next_asm(DList * list, DListElement * element, void * data);

int dlist_ins_prev(DList * list, DListElement * element, void * data);
int dlist_ins_prev_asm(DList * list, DListElement * element, void * data);

//删除操作
int dlist_remove(DList * list, DListElement * element, void ** data);
int dlist_remove_asm(DList * list, DListElement * element, void ** data);

//链表元素个数
#define dlist_size(list) ((list)->size)
//链表头
#define dlist_head(list) ((list)->head)
//链表尾
#define dlist_tail(list) ((list)->tail)
//是否为链表头
#define dlist_is_head(list, element) ((element) == (list)->head ? 1 : 0)
//是否为链表尾
#define dlist_is_tail(list, element) ((element) == (list)->tail ? 1 : 0)
//链表元素的数据成员
#define dlist_data(element) ((element)->data)
//链表元素后继元素
#define dlist_next(element) ((element)->next)
//链表元素前驱元素
#define dlist_prev(element) ((element)->prev)

#endif // DLISTC_H_

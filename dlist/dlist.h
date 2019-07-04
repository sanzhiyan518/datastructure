#ifndef DLIST_H_
#define DLIST_H_
//
typedef int (* compare)(const void * key1, const void * key2);

//双向链表元素
typedef struct DListElement
{
    void * data; //卫星数据
    struct DListElement * prev; //前驱元素
    struct DListElement * next; //后继元素
} DListElement;

//双向链表定义
typedef struct DList
{
    int length;
    DListElement * head;
    DListElement * tail;
    //比较函数
    compare compare;
}DList;

//链表操作集合
//链表初始化
DList * dlist_init(compare compare);
DList * dlist_init_asm(compare compare);

//链表销毁
void dlist_destroy(DList * dlist);
void dlist_destroy_asm(DList * dlist);

//插入操作，构建新的链表元素，并将此链表元素插入到传入链表元素参数之后，可以为空
void dlist_insert(DList * dlist, DListElement * prev, void * data);
void dlist_insert_asm(DList * dlist, DListElement * prev, void * data);

//根据传入卫星数据，搜索链表元素
DListElement * dlist_search(DList * dlist, void * data);
DListElement * dlist_search_asm(DList * dlist, void * data);

//删除操作，删除与传入卫星数据相等的链表元素
void dlist_delete(DList * dlist, void * data);
void dlist_delete_asm(DList * dlist, void * data);
//打印
void dlist_print(DList * dlist);

#define dlist_size(dlist) ((dlist)->length)
#define dlist_head(dlist) ((dlist)->head)
#define dlist_tail(dlist) ((dlist)->tail)
#define dlist_is_head(element) ((element)->prev == NULL ? 1 : 0)
#define dlist_is_tail(element) ((element)->next == NULL ? 1 : 0)
#define dlist_data(element) ((element)->data)
#define dlist_next(element) ((element)->next)
#define dlist_prev(element) ((element)->prev)
#define dlist_append(dlist, data) (dlist_insert_asm(dlist, dlist_tail(dlist), data))

//扫描链表宏
#define for_each(element, dlist) \
    for((element)=dlist_head(dlist); (element) != NULL; (element)=dlist_next(element))

#endif // DLISTC_H_

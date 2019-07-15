#ifndef CLIST_H_
#define CLIST_H_

typedef void (*destroy)(void * data);
typedef int (*match)(const void *data1, const void * data2);

//双向循环链表元素
typedef struct CListElement_
{
    void * data;                     //数据成员
    struct CListElement_ * prev;     //前驱元素
    struct CListElement_ * next;     //后继元素
} CListElement;

//双向循环链表定义
typedef struct CList_
{
    int size;  //链表长度
    match  match;  //元素比较函数
    destroy destroy;  //元素销毁函数
    CListElement * head; //链表头
}CList;

//初始化
void clist_init(CList * list, destroy destroy);
void clist_init_asm(CList * list, destroy destroy);

//销毁
void clist_destroy(CList * list);
void clist_destroy_asm(CList * list);

//插入
int clist_ins_next(CList * list, CListElement * element, void * data);
int clist_ins_next_asm(CList * list, CListElement * element, void * data);

//删除
int clist_rem_next(CList * list, CListElement * element, void ** data);
int clist_rem_next_asm(CList * list, CListElement * element, void ** data);

//链表长度
#define clist_size(list) ((list)->size)

//链表头
#define clist_head(list) ((list)->head)

//元素数据成员
#define clist_data(element) ((element)->data)

//后继元素
#define clist_next(element) ((element)->next)

//前驱元素
#define clist_prev(element) ((element)->prev)

#endif // CLIST_H_

#ifndef SLIST_H_
#define SLIST_H_

typedef void (*destroy)(void * data);
typedef int (*match)(const void *data1, const void * data2);

//链表元素结构体
typedef struct ListElement_ {
    //卫星数据
    void * data;
    //后继链表元素
    struct ListElement_ * next;
} ListElement;

//链表结构体
typedef struct List_ {
    //链表长度
    int size;
    //链表元素比较函数
    match match;
    //链表元素销毁函数
    destroy destroy;
    //链表头
    ListElement * head;
    //链表尾
    ListElement * tail;
} List;

//链表操作集合
//链表初始化
void list_init(List * list, destroy destroy);
void list_init_asm(List * list, destroy destroy);

//链表销毁
void list_destroy(List * list);
void list_destroy_asm(List * list);

//插入操作
int list_ins_next(List * list, ListElement * prev, void * data);
int list_ins_next_asm(List * list, ListElement * prev, void * data);

//删除操作
int list_rem_next(List * list, ListElement * prev, void ** data);
int list_rem_next_asm(List * list, ListElement * prev, void ** data);

//链表元素个数
#define list_size(list) ((list)->size)
//链表头
#define list_head(list) ((list)->head)
//链表尾
#define list_tail(list) ((list)->tail)
//是否为链表头
#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)
//是否为链表尾
#define list_is_tail(list, element) ((element) == (list)->tail ? 1 : 0)
//链表元素的数据成员
#define list_data(element) ((element)->data)
//链表元素链接元素
#define list_next(element) ((element)->next)

#endif // SLIST_H_

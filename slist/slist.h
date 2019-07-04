#ifndef SLIST_H_
#define SLIST_H_

 //元素比较函数
typedef int (* compare)(void * a, void *b);

//链表元素结构体
typedef struct ListElement {
    //卫星数据
    void * data;
    //后继链表元素
    struct ListElement * next;
} ListElement;

//链表结构体
typedef struct List {
    //链表长度
    int length;
    //链表头
    ListElement * head;
    //链表尾
    ListElement * tail;
    //比较函数
    compare compare;
} List;

//链表操作集合
//链表初始化
List * list_init(compare compare);
List * list_init_asm(compare compare);

//链表销毁
void list_destroy(List * list);
void list_destroy_asm(List * list);

//插入操作，构建新的链表元素，并将此链表元素插入到传入链表元素参数之后，可以为空
void list_insert(List * list, ListElement * prev, void * data);
void list_insert_asm(List * list, ListElement * prev, void * data);

//根据传入卫星数据，搜索链表元素
ListElement * list_search(List * list, void * data);
ListElement * list_search_asm(List * list, void * data);

//删除操作，删除与传入卫星数据相等的链表元素
void list_delete(List * list, void * data);
void list_delete_asm(List * list, void * data);

//链表大小
#define list_length(l) ((l) ? (l)->length : 0)
//链表头
#define list_head(l) ((l) ? (l)->head : NULL)
//链表尾
#define list_tail(l) ((l) ? (l)->tail : NULL)
//是否为链表头
#define list_is_head(l, c) ((l) ? ((l)->head == c ? 1 : 0 ) : 0)
//是否为链表尾
#define list_is_tail(e) ((e)->next == NULL ? 1 : 0)
//链表元素的卫星数据
#define list_data(e) ((e) ? (e)->data : 0)
//链表元素的后继元素
#define list_next(e) ((e) ? (e)->next : 0)
//追加
#define list_append(l, data) list_insert((l), list_tail(l), data)
//扫描链表宏
#define for_each(element, list) \
    for((element)=list_head(list); (element) != NULL; (element)=list_next(element))

#endif // SLIST_H_

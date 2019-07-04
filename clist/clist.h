#ifndef CLIST_H_
#define CLIST_H_

//循环链表元素
typedef struct CListElement {
    //卫星数据
    void * data;
    //前驱
    struct CListElement * prev;
    //后继
    struct CListElement * next;
} CListElement;

typedef int (* compare)(const void * key1, const void * key2);

//链表
typedef struct CList {
    //长度
    int length;
    //头
    CListElement * head;
    //元素比较函数
    compare compare;
} CList;

void test();
//初始化
CList * clist_init(compare  compare);
CList * clist_init_asm(compare compare);

//销毁
void clist_destroy(CList * l);
void clist_destroy_asm(CList * l);

//插入元素
void clist_insert(CList * l, CListElement * prev, void * data);
void clist_insert_asm(CList * l, CListElement * prev, void * data);

//搜索元素
CListElement *  clist_search(CList * l, void * data);
CListElement * clist_search_asm(CList * l, void * data);

//删除元素
void clist_delete(CList * l, void * data);
void clist_delete_asm(CList * l, void * data);

void clist_print(CList *l);

#endif // CLIST_H_

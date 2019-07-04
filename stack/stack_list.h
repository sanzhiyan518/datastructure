#ifndef STACK_LIST_H_
#define STACK_LIST_H_

//栈的单链表实现
typedef struct Node {
    //后继元素
    struct Node * next;
    //卫星数据
    void * data;
} Node;

//栈也使用Node数据结构
typedef Node * StackList;

//创建栈
StackList stacklist_init();
StackList stacklist_init_asm();

//销毁栈
void stacklist_destroy(StackList s);
void stacklist_destroy_asm(StackList s);

//压入
int stacklist_push(StackList s, void * data);
int stacklist_push_asm(StackList s, void * data);

//弹出
int stacklist_pop(StackList s, void ** data);
int stacklist_pop_asm(StackList s, void ** data);

//是否空
int stacklist_empty(StackList s);
int stacklist_empty_asm(StackList s);

#endif // STACK_LIST_H_

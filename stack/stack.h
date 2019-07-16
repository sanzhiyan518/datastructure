#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>

typedef void (*destroy)(void * data);

//栈的单链表结点
typedef struct Node_ {
    //数据成员
    void * data;
    //后继元素
    struct Node_ * next;
} Node;

//单链表实现结构体
typedef struct ListStack_ {
    //元素销毁函数
    destroy destroy;
    //头结点
    Node * head;
} ListStack;

//栈的数组实现
typedef struct ArrayStack_ {
    //元素销毁函数
    destroy destroy;
    //栈深
    int deepth;
    //栈顶
    int top;
    //数据存储
    void ** data;
} ArrayStack;

//初始化栈
void liststack_init(ListStack * stack, destroy destroy);
void liststack_init_asm(ListStack * stack, destroy destroy);
void arraystack_init(ArrayStack * stack, destroy destroy);
void arraystack_init_asm(ArrayStack * stack, destroy destroy);

//线元素销毁函数
void liststack_destroy(ListStack * s);
void liststack_destroy_asm(ListStack * s);
void arraystack_destroy(ArrayStack * s);
void arraystack_destroy_asm(ArrayStack * s);

//进栈
int liststack_push(ListStack * s, void * data);
int liststack_push_asm(ListStack * s, void * data);
int arraystack_push(ArrayStack * s, void * data);
int arraystack_push_asm(ArrayStack * s, void * data);

//出栈
int liststack_pop(ListStack * s, void ** data);
int liststack_pop_asm(ListStack * s, void ** data);
int arraystack_pop(ArrayStack * s, void ** data);
int arraystack_pop_asm(ArrayStack * s, void ** data);

//返回栈顶元素数据成员
#define liststack_peek(stack) ((stack)->head->data);
#define arraystack_peek(stack) ((stack)->data[(stack)->top])

//判断栈是否为空
#define liststack_is_empty(stack) ((stack)->head == NULL ? 0 : -1)
#define arraystack_is_empty(stack) ((stack)->top == -1 ? 0 : -1)

#endif // STACK_H_

#ifndef STACK_H_
#define STACK_H_

//栈数据结构定义
typedef struct Stack {
    //栈深
    int deepth;
    //栈顶
    int top;
    //数据存储
    void ** data;
} Stack;

//栈初始化,传入栈的深度
Stack * __attribute__((fastcall)) stack_init(int deepth);
Stack * stack_init_asm(int deepth);

//栈销毁
void __attribute__((fastcall)) stack_destroy(Stack * s);
void stack_destroy_asm(Stack * s);

//压入
int stack_push(Stack * s, void * data);
int stack_push_asm(Stack * s, void * data);

//弹出
int stack_pop(Stack * s, void ** data);
int stack_pop_asm(Stack * s, void ** data);

//判断栈是否为空，返回零为空，其他值不为空
int stack_empty(Stack * s);
int stack_empty_asm(Stack * s);

#endif // STACK_H_

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack * __attribute__((fastcall)) stack_init(int deepth) {
    Stack * s = (Stack *)malloc(sizeof(*s));
    //�����ڴ���䣬������ȴ�С
    s->data = (void **)malloc((size_t)(deepth) * sizeof(void *));
    //����ջ��Ϊ-1
    s->top = -1;
    s->deepth = deepth;
    return s;
}

void __attribute__((fastcall)) stack_destroy(Stack * s) {
    if(s == NULL)
        return;

    free(s->data);
    free(s);
}
int stack_push(Stack * s, void * data) {
    if(s == NULL)
        return -1;

    //
    //����ջ���ӡ����
    if(s->top + 1 >= s->deepth) {
        printf("overflow");
        return -1;
    }
    s->data[++s->top] = data;
    return 0;
}

int stack_pop(Stack * s, void **data) {
    if( s== NULL)
        return -1;

    //ջ���մ�ӡ����
    if(s->top == -1 ) {
        printf("underflow");
        return -1;
    }

    *data = s->data[s->top--];
    return 0;
}

int stack_empty(Stack * s) {
    return (s == NULL) ? 0 : (s->top < 0 ? 0 : 1);
}

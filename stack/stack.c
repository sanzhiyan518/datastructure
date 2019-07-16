#include <stdlib.h>
#include "stack.h"

//初始化栈
void liststack_init(ListStack * stack, destroy destroy) {
    stack->destroy = destroy;
    stack->head = NULL;
}

void arraystack_init(ArrayStack * stack, destroy destroy) {
    stack->destroy = destroy;
    stack->top = -1;
    //预分配内存
    stack->data = (void **)malloc(stack->deepth * sizeof(void *));
}

//线元素销毁函数
void liststack_destroy(ListStack * s) {
    Node * node = s->head, * prev;
    destroy destroy = s->destroy;

    while(node != NULL) {
        prev = node;
        node = node->next;

        if(destroy)
            destroy(prev->data);
        free(prev);
    }

    s->destroy = NULL;
    s->head = NULL;
}

void arraystack_destroy(ArrayStack * s) {
    int i = 0;
    destroy destroy = s->destroy;
    if(destroy != NULL) {
        void ** datas = s->data;
        for(; i <= s->top; i++) {
            destroy(datas[i]);
        }
    }
    free(s->data);
    s->data = NULL;
    s->top = -1;
}

//进栈
int liststack_push(ListStack * s, void * data) {
    Node * node = (Node *)malloc(sizeof(Node));

    if(node == NULL)
        return -1;

    node->data = data;

    //链表为空
    if(s->head == NULL) {
        node->next = NULL;
        s->head = node;
    } else {
        node->next = s->head;
        s->head = node;
    }

    return 0;
}

int arraystack_push(ArrayStack * s, void * data) {
    if( s->top + 1 >= s->deepth)
        return -1;

    s->data[++s->top] = data;
    return 0;
}

//出栈
int liststack_pop(ListStack * s, void ** data) {
    Node * node = s->head;

    if(node == NULL)
        return -1;

    s->head = node->next;
    *data = node->data;
    free(node);

    return 0;
}

int arraystack_pop(ArrayStack * s, void ** data) {
    if(s->top == -1)
        return 0;

    *data = s->data[s->top--];
    return 0;
}

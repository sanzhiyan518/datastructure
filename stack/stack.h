#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>

typedef void (*destroy)(void * data);

//ջ�ĵ�������
typedef struct Node_ {
    //���ݳ�Ա
    void * data;
    //���Ԫ��
    struct Node_ * next;
} Node;

//������ʵ�ֽṹ��
typedef struct ListStack_ {
    //Ԫ�����ٺ���
    destroy destroy;
    //ͷ���
    Node * head;
} ListStack;

//ջ������ʵ��
typedef struct ArrayStack_ {
    //Ԫ�����ٺ���
    destroy destroy;
    //ջ��
    int deepth;
    //ջ��
    int top;
    //���ݴ洢
    void ** data;
} ArrayStack;

//��ʼ��ջ
void liststack_init(ListStack * stack, destroy destroy);
void liststack_init_asm(ListStack * stack, destroy destroy);
void arraystack_init(ArrayStack * stack, destroy destroy);
void arraystack_init_asm(ArrayStack * stack, destroy destroy);

//��Ԫ�����ٺ���
void liststack_destroy(ListStack * s);
void liststack_destroy_asm(ListStack * s);
void arraystack_destroy(ArrayStack * s);
void arraystack_destroy_asm(ArrayStack * s);

//��ջ
int liststack_push(ListStack * s, void * data);
int liststack_push_asm(ListStack * s, void * data);
int arraystack_push(ArrayStack * s, void * data);
int arraystack_push_asm(ArrayStack * s, void * data);

//��ջ
int liststack_pop(ListStack * s, void ** data);
int liststack_pop_asm(ListStack * s, void ** data);
int arraystack_pop(ArrayStack * s, void ** data);
int arraystack_pop_asm(ArrayStack * s, void ** data);

//����ջ��Ԫ�����ݳ�Ա
#define liststack_peek(stack) ((stack)->head->data);
#define arraystack_peek(stack) ((stack)->data[(stack)->top])

//�ж�ջ�Ƿ�Ϊ��
#define liststack_is_empty(stack) ((stack)->head == NULL ? 0 : -1)
#define arraystack_is_empty(stack) ((stack)->top == -1 ? 0 : -1)

#endif // STACK_H_

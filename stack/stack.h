#ifndef STACK_H_
#define STACK_H_

//ջ���ݽṹ����
typedef struct Stack {
    //ջ��
    int deepth;
    //ջ��
    int top;
    //���ݴ洢
    void ** data;
} Stack;

//ջ��ʼ��,����ջ�����
Stack * __attribute__((fastcall)) stack_init(int deepth);
Stack * stack_init_asm(int deepth);

//ջ����
void __attribute__((fastcall)) stack_destroy(Stack * s);
void stack_destroy_asm(Stack * s);

//ѹ��
int stack_push(Stack * s, void * data);
int stack_push_asm(Stack * s, void * data);

//����
int stack_pop(Stack * s, void ** data);
int stack_pop_asm(Stack * s, void ** data);

//�ж�ջ�Ƿ�Ϊ�գ�������Ϊ�գ�����ֵ��Ϊ��
int stack_empty(Stack * s);
int stack_empty_asm(Stack * s);

#endif // STACK_H_

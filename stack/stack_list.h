#ifndef STACK_LIST_H_
#define STACK_LIST_H_

//ջ�ĵ�����ʵ��
typedef struct Node {
    //���Ԫ��
    struct Node * next;
    //��������
    void * data;
} Node;

//ջҲʹ��Node���ݽṹ
typedef Node * StackList;

//����ջ
StackList stacklist_init();
StackList stacklist_init_asm();

//����ջ
void stacklist_destroy(StackList s);
void stacklist_destroy_asm(StackList s);

//ѹ��
int stacklist_push(StackList s, void * data);
int stacklist_push_asm(StackList s, void * data);

//����
int stacklist_pop(StackList s, void ** data);
int stacklist_pop_asm(StackList s, void ** data);

//�Ƿ��
int stacklist_empty(StackList s);
int stacklist_empty_asm(StackList s);

#endif // STACK_LIST_H_

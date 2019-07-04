#ifndef QUEUE_H_
#define QUEUE_H_

//����ʵ�ֶ��еĽṹ�嶨��
typedef struct Queue {
    int length;     //�����ܳ���
    int size;       //��ǰ���еĳ���
    int front;    //��ͷ
    int rear;    //��β
    void ** data;   //Ԫ������
} Queue;

//���д���
Queue * queue_init(int length);
Queue * queue_init_asm(int length);

//��������
void queue_destroy(Queue * q);
void queue_destroy_asm(Queue * q);

//��Ӳ���
int queue_enter(Queue * q, void * data);
int queue_enter_asm(Queue * q, void * data);

//���Ӳ���
int queue_delete(Queue * q, void ** data);
int queue_delete_asm(Queue * q, void ** data);

//�����Ƿ���
int queue_full(Queue * q);
int queue_full_asm(Queue * q);

//�����Ƿ�Ϊ��
int queue_empty(Queue * q);
int queue_empty_asm(Queue * q);

//������ʵ�ֶ���
typedef struct Node {
    struct Node * next;
    void * data;
} Node;

typedef struct QueueList {
    Node * front;       //��ͷ
    Node * rear;        //��β
} QueueList;

//���й���
QueueList * queuelist_init();
QueueList * queuelist_init_asm();

//��������
void queuelist_destroy(QueueList * q);
void queuelist_destroy_asm(QueueList * q);

//�����Ƿ�Ϊ��
int queuelist_empty(QueueList * q);
int queuelist_empty_asm(QueueList * q);

//�������
int queuelist_enter(QueueList * q, void * data);
int queuelist_enter_asm(QueueList * q, void * data);

//���г���
int queuelist_delete(QueueList * q, void ** data);
int queuelist_delete_asm(QueueList * q, void ** data);

#endif // QUEUE_H_

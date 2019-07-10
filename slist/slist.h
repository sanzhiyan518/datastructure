#ifndef SLIST_H_
#define SLIST_H_

typedef void (*destroy)(void * data);
typedef int (*match)(const void *data1, const void * data2);

//����Ԫ�ؽṹ��
typedef struct ListElement_ {
    //��������
    void * data;
    //�������Ԫ��
    struct ListElement_ * next;
} ListElement;

//����ṹ��
typedef struct List_ {
    //������
    int size;
    //����Ԫ�رȽϺ���
    match match;
    //����Ԫ�����ٺ���
    destroy destroy;
    //����ͷ
    ListElement * head;
    //����β
    ListElement * tail;
} List;

//�����������
//�����ʼ��
void list_init(List * list, destroy destroy);
void list_init_asm(List * list, destroy destroy);

//��������
void list_destroy(List * list);
void list_destroy_asm(List * list);

//�������
int list_ins_next(List * list, ListElement * prev, void * data);
int list_ins_next_asm(List * list, ListElement * prev, void * data);

//ɾ������
int list_rem_next(List * list, ListElement * prev, void ** data);
int list_rem_next_asm(List * list, ListElement * prev, void ** data);

//����Ԫ�ظ���
#define list_size(list) ((list)->size)
//����ͷ
#define list_head(list) ((list)->head)
//����β
#define list_tail(list) ((list)->tail)
//�Ƿ�Ϊ����ͷ
#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)
//�Ƿ�Ϊ����β
#define list_is_tail(list, element) ((element) == (list)->tail ? 1 : 0)
//����Ԫ�ص����ݳ�Ա
#define list_data(element) ((element)->data)
//����Ԫ������Ԫ��
#define list_next(element) ((element)->next)

#endif // SLIST_H_

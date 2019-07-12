#ifndef DLIST_H_
#define DLIST_H_
//
typedef void (*destroy)(void * data);
typedef int (*match)(const void *data1, const void * data2);

//˫������Ԫ��
typedef struct DListElement_
{
    void * data;                     //���ݳ�Ա
    struct DListElement_ * prev;     //ǰ��Ԫ��
    struct DListElement_ * next;     //���Ԫ��
} DListElement;

//˫��������
typedef struct DList_
{
    long size;  //������
    match  match;  //Ԫ�رȽϺ���
    destroy destroy;  //Ԫ�����ٺ���
    DListElement * head; //����ͷ
    DListElement * tail;  //����β
}DList;

//�����������
//�����ʼ��
void dlist_init(DList * list, destroy destroy);
void dlist_init_asm(DList * list, destroy destroy);

//��������
void dlist_destroy(DList * list);
void dlist_destroy_asm(DList * list);

//�������
int dlist_ins_next(DList * list, DListElement * element, void * data);
int dlist_ins_next_asm(DList * list, DListElement * element, void * data);

int dlist_ins_prev(DList * list, DListElement * element, void * data);
int dlist_ins_prev_asm(DList * list, DListElement * element, void * data);

//ɾ������
int dlist_remove(DList * list, DListElement * element, void ** data);
int dlist_remove_asm(DList * list, DListElement * element, void ** data);

//����Ԫ�ظ���
#define dlist_size(list) ((list)->size)
//����ͷ
#define dlist_head(list) ((list)->head)
//����β
#define dlist_tail(list) ((list)->tail)
//�Ƿ�Ϊ����ͷ
#define dlist_is_head(list, element) ((element) == (list)->head ? 1 : 0)
//�Ƿ�Ϊ����β
#define dlist_is_tail(list, element) ((element) == (list)->tail ? 1 : 0)
//����Ԫ�ص����ݳ�Ա
#define dlist_data(element) ((element)->data)
//����Ԫ�غ��Ԫ��
#define dlist_next(element) ((element)->next)
//����Ԫ��ǰ��Ԫ��
#define dlist_prev(element) ((element)->prev)

#endif // DLISTC_H_

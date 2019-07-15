#ifndef CLIST_H_
#define CLIST_H_

typedef void (*destroy)(void * data);
typedef int (*match)(const void *data1, const void * data2);

//˫��ѭ������Ԫ��
typedef struct CListElement_
{
    void * data;                     //���ݳ�Ա
    struct CListElement_ * prev;     //ǰ��Ԫ��
    struct CListElement_ * next;     //���Ԫ��
} CListElement;

//˫��ѭ��������
typedef struct CList_
{
    int size;  //������
    match  match;  //Ԫ�رȽϺ���
    destroy destroy;  //Ԫ�����ٺ���
    CListElement * head; //����ͷ
}CList;

//��ʼ��
void clist_init(CList * list, destroy destroy);
void clist_init_asm(CList * list, destroy destroy);

//����
void clist_destroy(CList * list);
void clist_destroy_asm(CList * list);

//����
int clist_ins_next(CList * list, CListElement * element, void * data);
int clist_ins_next_asm(CList * list, CListElement * element, void * data);

//ɾ��
int clist_rem_next(CList * list, CListElement * element, void ** data);
int clist_rem_next_asm(CList * list, CListElement * element, void ** data);

//������
#define clist_size(list) ((list)->size)

//����ͷ
#define clist_head(list) ((list)->head)

//Ԫ�����ݳ�Ա
#define clist_data(element) ((element)->data)

//���Ԫ��
#define clist_next(element) ((element)->next)

//ǰ��Ԫ��
#define clist_prev(element) ((element)->prev)

#endif // CLIST_H_

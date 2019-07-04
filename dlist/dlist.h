#ifndef DLIST_H_
#define DLIST_H_
//
typedef int (* compare)(const void * key1, const void * key2);

//˫������Ԫ��
typedef struct DListElement
{
    void * data; //��������
    struct DListElement * prev; //ǰ��Ԫ��
    struct DListElement * next; //���Ԫ��
} DListElement;

//˫��������
typedef struct DList
{
    int length;
    DListElement * head;
    DListElement * tail;
    //�ȽϺ���
    compare compare;
}DList;

//�����������
//�����ʼ��
DList * dlist_init(compare compare);
DList * dlist_init_asm(compare compare);

//��������
void dlist_destroy(DList * dlist);
void dlist_destroy_asm(DList * dlist);

//��������������µ�����Ԫ�أ�����������Ԫ�ز��뵽��������Ԫ�ز���֮�󣬿���Ϊ��
void dlist_insert(DList * dlist, DListElement * prev, void * data);
void dlist_insert_asm(DList * dlist, DListElement * prev, void * data);

//���ݴ����������ݣ���������Ԫ��
DListElement * dlist_search(DList * dlist, void * data);
DListElement * dlist_search_asm(DList * dlist, void * data);

//ɾ��������ɾ���봫������������ȵ�����Ԫ��
void dlist_delete(DList * dlist, void * data);
void dlist_delete_asm(DList * dlist, void * data);
//��ӡ
void dlist_print(DList * dlist);

#define dlist_size(dlist) ((dlist)->length)
#define dlist_head(dlist) ((dlist)->head)
#define dlist_tail(dlist) ((dlist)->tail)
#define dlist_is_head(element) ((element)->prev == NULL ? 1 : 0)
#define dlist_is_tail(element) ((element)->next == NULL ? 1 : 0)
#define dlist_data(element) ((element)->data)
#define dlist_next(element) ((element)->next)
#define dlist_prev(element) ((element)->prev)
#define dlist_append(dlist, data) (dlist_insert_asm(dlist, dlist_tail(dlist), data))

//ɨ�������
#define for_each(element, dlist) \
    for((element)=dlist_head(dlist); (element) != NULL; (element)=dlist_next(element))

#endif // DLISTC_H_

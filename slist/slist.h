#ifndef SLIST_H_
#define SLIST_H_

 //Ԫ�رȽϺ���
typedef int (* compare)(void * a, void *b);

//����Ԫ�ؽṹ��
typedef struct ListElement {
    //��������
    void * data;
    //�������Ԫ��
    struct ListElement * next;
} ListElement;

//����ṹ��
typedef struct List {
    //������
    int length;
    //����ͷ
    ListElement * head;
    //����β
    ListElement * tail;
    //�ȽϺ���
    compare compare;
} List;

//�����������
//�����ʼ��
List * list_init(compare compare);
List * list_init_asm(compare compare);

//��������
void list_destroy(List * list);
void list_destroy_asm(List * list);

//��������������µ�����Ԫ�أ�����������Ԫ�ز��뵽��������Ԫ�ز���֮�󣬿���Ϊ��
void list_insert(List * list, ListElement * prev, void * data);
void list_insert_asm(List * list, ListElement * prev, void * data);

//���ݴ����������ݣ���������Ԫ��
ListElement * list_search(List * list, void * data);
ListElement * list_search_asm(List * list, void * data);

//ɾ��������ɾ���봫������������ȵ�����Ԫ��
void list_delete(List * list, void * data);
void list_delete_asm(List * list, void * data);

//�����С
#define list_length(l) ((l) ? (l)->length : 0)
//����ͷ
#define list_head(l) ((l) ? (l)->head : NULL)
//����β
#define list_tail(l) ((l) ? (l)->tail : NULL)
//�Ƿ�Ϊ����ͷ
#define list_is_head(l, c) ((l) ? ((l)->head == c ? 1 : 0 ) : 0)
//�Ƿ�Ϊ����β
#define list_is_tail(e) ((e)->next == NULL ? 1 : 0)
//����Ԫ�ص���������
#define list_data(e) ((e) ? (e)->data : 0)
//����Ԫ�صĺ��Ԫ��
#define list_next(e) ((e) ? (e)->next : 0)
//׷��
#define list_append(l, data) list_insert((l), list_tail(l), data)
//ɨ�������
#define for_each(element, list) \
    for((element)=list_head(list); (element) != NULL; (element)=list_next(element))

#endif // SLIST_H_

#ifndef CLIST_H_
#define CLIST_H_

//ѭ������Ԫ��
typedef struct CListElement {
    //��������
    void * data;
    //ǰ��
    struct CListElement * prev;
    //���
    struct CListElement * next;
} CListElement;

typedef int (* compare)(const void * key1, const void * key2);

//����
typedef struct CList {
    //����
    int length;
    //ͷ
    CListElement * head;
    //Ԫ�رȽϺ���
    compare compare;
} CList;

void test();
//��ʼ��
CList * clist_init(compare  compare);
CList * clist_init_asm(compare compare);

//����
void clist_destroy(CList * l);
void clist_destroy_asm(CList * l);

//����Ԫ��
void clist_insert(CList * l, CListElement * prev, void * data);
void clist_insert_asm(CList * l, CListElement * prev, void * data);

//����Ԫ��
CListElement *  clist_search(CList * l, void * data);
CListElement * clist_search_asm(CList * l, void * data);

//ɾ��Ԫ��
void clist_delete(CList * l, void * data);
void clist_delete_asm(CList * l, void * data);

void clist_print(CList *l);

#endif // CLIST_H_

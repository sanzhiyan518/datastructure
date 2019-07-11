# 双链表

<img src="https://github.com/sanzhiyan518/datastructure/blob/master/imgs/dlist.png" />

## 双链表特征

* 双链表元素之间由两个指针链接；

* 双链表元素由3部分组成：除了数据成员和next的指针外，还包含一个指向其前驱元素的指针，称为prev指针；

* 双向链表中，每个元素的next指针都指向其后继的元素，prev指针都指向其前驱元素；

* 链表头的prev指针设置为NULL；

* 链表尾的next指针设置NULL；

## 结构定义

``` c
typedef void (*destroy)(void * data);
typedef int (*match)(const void *data1, const void * data2);

//双向链表元素
typedef struct DListElement_
{
    void * data;                     //数据成员
    struct DListElement_ * prev;     //前驱元素
    struct DListElement_ * next;     //后继元素
} DListElement;

//双向链表定义
typedef struct DList_
{
    int size;  //链表长度
    match  match;  //元素比较函数
    destroy destroy;  //元素销毁函数
    DListElement * head; //链表头
    DListElement * tail;  //链表尾
}DList;

``` 

## 接口定义

### dlist_init
``` c
void dlist_init(DList * list, destroy destroy);
```
* **返回值** 无
* **描述** 初始化由参数list指定的双向链表。list内存由调用的函数来分配，destroy函数将用来释放链表元素所占内存，可指定自定义的数据成员释放函数或为空。

### dlist_destroy
``` c
void dlist_destroy(DList * list);
```
* **返回值** 无
* **描述** 销毁参数list指定的双向链表，如果destroy成员不为空，则在移除链表中每个元素时将调用该函数一次。

### dlist_ins_next
``` c
int dlist_ins_next(DList * list, DListElement * element, void * data);
```
* **返回值** 如果插入元素成功返回0，否则返回-1。
* **描述** 在list链表中element元素后面插入一个新元素，如果element为null且链表长度为0，则新元素为链表的头和尾。

### dlist_ins_prev
``` c
int dlist_ins_prev(DList * list, DListElement * element, void * data);
```
* **返回值** 如果插入元素成功返回0，否则返回-1。
* **描述** 在list链表中element元素前面插入一个新元素，如果element为null且链表长度为0，则新元素为链表的头和尾。


### list_remove
``` c
int dlist_remove(DList * list, DListElement * element, void ** data);
```
* **返回值** 如果移除元素成功返回0，否则返回-1。
* **描述** 移除list链表中element元素，data指向己移除元素中存储的数据。由调用函数负责管理data所引用的存储空间。

### dlist_size
```c
#define dlist_size(list) ((list)->size)
```
* **描述** 返回链表中元素的个数。

### dlist_head
```c
#define dlist_head(list) ((list)->head)
```
* **描述** 返回链表中头元素。

### dlist_tail
```c
#define dlist_tail(list) ((list)->tail
```
* **描述** 返回链表中尾元素。

### dlist_is_head
```c
#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)
```
* **描述** 如果element为链表的头元素返回1，否则返回0。

### dlist_is_tail
```c
#define dlist_is_tail(list, element) ((element) == (list)->tail ? 1 : 0)
```
* **描述** 如果element为链表的尾元素返回1，否则返回0。

### dlist_data
```c
#define dlist_data(element) ((element)->data)
```
* **描述** 返回element元素中保存的数据。

### dlist_next
```c
#define dlist_next(element) ((element)->next)
```
* **描述** 返回element元素的后继元素。

### dlist_prev
```c
#define dlist_prev(element) ((element)->prev)
```
* **描述** 返回element元素的前驱元素。

# 循环链表

<img src="https://github.com/sanzhiyan518/datastructure/blob/master/imgs/clist.png" />

## 循环链表特征

* 链表元素之间由两个指针链接；

* 链表元素由3部分组成：除了数据成员和next的指针外，还包含一个指向其前驱元素的指针，称为prev指针；

* 链表中，每个元素的next指针都指向其后继的元素，prev指针都指向其前驱元素；

* 没有链表尾元素，最后一个元素的next指针指向头元素，头元素的prev指针指向最后一个元素

* 链表中每个元素即可以看做头元素也可以看做尾元素

## 结构定义

``` c
typedef void (*destroy)(void * data);
typedef int (*match)(const void *data1, const void * data2);

//双向循环链表元素
typedef struct CListElement_
{
    void * data;                     //数据成员
    struct CListElement_ * prev;     //前驱元素
    struct CListElement_ * next;     //后继元素
} CListElement;

//双向循环链表定义
typedef struct CList_
{
    int size;  //链表长度
    match  match;  //元素比较函数
    destroy destroy;  //元素销毁函数
    CListElement * head; //链表头
}CList;

``` 

## 接口定义

### clist_init
``` c
void clist_init(CList * list, destroy destroy);
```
* **返回值** 无
* **描述** 初始化由参数list指定的双向循环链表。list内存由调用的函数来分配，destroy函数将用来释放链表元素所占内存，可指定自定义的数据成员释放函数或为空。

### clist_destroy
``` c
void clist_destroy(CList * list);
```
* **返回值** 无
* **描述** 销毁参数list指定的双向循环链表，如果destroy成员不为空，则在移除链表中每个元素时将调用该函数一次。

### clist_ins_next
``` c
int clist_ins_next(CList * list, CListElement * element, void * data);
```
* **返回值** 如果插入元素成功返回0，否则返回-1。
* **描述** 在list链表中element元素后面插入一个新元素，如果element为null且链表长度为0，则新元素为链表的头和尾。

### cist_rem_next
``` c
int clist_rem_next(CList * list, CListElement * element, void ** data);
```
* **返回值** 如果移除元素成功返回0，否则返回-1。
* **描述** 移除list链表中element后继元素，data指向己移除元素中存储的数据。由调用函数负责管理data所引用的存储空间。

### clist_size
```c
#define clist_size(list) ((list)->size)
```
* **描述** 返回链表中元素的个数。

### clist_head
```c
#define clist_head(list) ((list)->head)
```
* **描述** 返回链表中头元素。


### clist_data
```c
#define clist_data(element) ((element)->data)
```
* **描述** 返回element元素中保存的数据。

### clist_next
```c
#define clist_next(element) ((element)->next)
```
* **描述** 返回element元素的后继元素。

### clist_prev
```c
#define clist_prev(element) ((element)->prev)
```
* **描述** 返回element元素的前驱元素。

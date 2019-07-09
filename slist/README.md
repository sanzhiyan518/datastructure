# 单链表

<img src="https://github.com/sanzhiyan518/datastructure/blob/master/imgs/sline.png" />

## 单链表特征

* 链表元素之间通过一个指针彼此链接起来；

* 每个链表元素包含两个部分：数据成员和一个称为next的指针。next指针指向其后的元素；

* 最后一个链表元素的next指针设置为NULL；

* 链表开头处的元素称为“头”；

* 链表末尾的元素称为“尾”。

## 优点

* 维护代价小，仅修改next成员就可改变链接关系；

* 内存占用空间小；

## 缺点

* 访问一个元素，只能从链表头开始连接遍历直到找到所需要的元素为止；

* 只能一个方向遍历，没有维护元素的前一个元素的链接，找前一个元素只能从头遍历；
## 结构定义

```  c

//链表元素结构体
typedef struct ListElement {
    void * data; //数据成员
    struct ListElement * next; //后继链表元素
} ListElement;

//链表结构体
typedef struct List {
    //链表长度
    int size;
    //链表元素比较函数
    int (*match)(const void * key1, const void * key2);
    //链表元素销毁函数
    void (*destroy)(void * data);
    //链表头
    ListElement * head;
    //链表尾
    ListElement * tail;
} List;

``` 

## 接口定义

### list_init
``` c
void list_init(List * list, void (*destroy)(void * data);
```
* **返回值** 无
* **描述** 初始化由参数list指定的链表。list内存由调用的函数来分配，destroy函数将用来释放链表元素所占内存，可指定自定义的数据成员释放函数或为空。

### list_destroy
``` c
void list_destroy(List * list);
```
* **返回值** 无
* **描述** 销毁参数list指定的链表，如果destroy成员不为空，则在移除链表中每个元素时将调用该函数一次。

### list_ins_next
``` c
int list_ins_next(List *list, ListElement *element, const void *data);
```
* **返回值** 如果插入元素成功返回0，否则返回-1。
* **描述** 在list链表中element元素后面插入一个新元素，如果element为null，则新元素插入链表头部。

### list_rem_next
``` c
int list_rem_next(List *list, ListElement *element, void **data);
```
* **返回值** 如果移除元素成功返回0，否则返回-1。
* **描述** 移除list链表中element后的那个元素。如果element为null,则移除链表头元素。调用返回后，data指向己移除元素中存储的数据。由调用函数负责管理data所引用的存储空间。

### list_size
```c
#define list_size(list) ((list)->size)
```
* **描述** 返回链表中元素的个数。

### list_head
```c
#define list_head(list) ((list)->head)
```
* **描述** 返回链表中头元素。

### list_tail
```c
#define list_tail(list) ((list)->tail
```
* **描述** 返回链表中尾元素。

### list_is_head
```c
#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)
```
* **描述** 如果element为链表的头元素返回1，否则返回0。

### list_is_tail
```c
#define list_is_tail(list, element) ((element) == (list)->tail ? 1 : 0)
```
* **描述** 如果element为链表的尾元素返回1，否则返回0。

### list_data
```c
#define list_data(element) ((element)->data)
```
* **描述** 返回element元素中保存的数据。

### list_next
```c
#define list_next(element) ((element)->next)
```
* **描述** 返回element元素链接的元素。

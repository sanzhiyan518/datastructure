# 介入式链表

<img src="https://github.com/sanzhiyan518/datastructure/blob/master/imgs/ilist.png" />

在linux内核源代码中采用的双向链表不同于经典的双向链表，在经典链表实现中数据成员都“嵌入”到链表的结点中，实际上数据成员内存与结点内存是分离的。而在linux内核链表实现中，链表结点直接包在数据中。

## 双链表特征

* 链表元素定义在数据结构体中，同在一个内存块中；

* 数据结构通过内嵌的链表元素链接在一起；

* 得到链表元素后通过指针偏移可迅速得到数据内存，避免通过链表元素数据成员指针间接访问数据。

## 结构定义

``` c
typedef struct IList_ {
    struct IList * prev;
    struct IList * next;
} IList;
``` 

## 接口定义

### ilist_init
``` c
void ilist_init(IList * list);
```
* **描述** 初始化一个链表，一般用于初始化链表头

### ilist_add_head
``` c
void ilist_add_head(IList * list, IListNode * cur);
```
* **描述** 在链表头追加元素

### ilist_add_tail
``` c
void ilist_add_tail(IList * list, IListNode * cur);
```
* **描述** 在链表尾前追加元素

### ilist_remove
``` c
void ilist_remove(IListNode * cur);
```
* **描述** 链表元素删除

### ilist_entry
``` c
#define ilist_entry(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)(&((type *)0)->member)))
```
* **描述** 获取链表元素所在数据指针
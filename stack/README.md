# 栈

<img src="https://github.com/sanzhiyan518/datastructure/blob/master/imgs/stack.png" />

## 栈特征

* 按照后进先出（LIFO）的方式存储和删除元素，被删除的元素是最近插入的元素；

* 添加与删除元素是在同一端进行的，称为栈顶，相应地，另一端被称为栈底；

* 有两种比较流行的实现方法，一种方法链表，而另一种方法使用数组；

* 具有两种基本操作Push(进栈）和Pop（出栈）。

## 链表实现结构定义

``` c
typedef void (*destroy)(void * data);
//栈的单链表结点
typedef struct Node_ {
    //后继元素
    struct Node_ * next;
    //数据成员
    void * data;
} Node;

//栈结构体
typedef struct ListStack_ {
    //元素销毁函数
    destroy destroy;
    //头结点
    Node * head;
} ListStack;

``` 

## 数组实现结构定义
``` c
//栈的数组实现
typedef struct ArrayStack_ {
    //元素销毁函数
    destroy destroy;
    //栈深
    int deepth;
    //栈顶
    int top;
    //数据存储
    void ** data;
} ArrayStack;
```

## 接口定义

栈提供如下接口，两种实现方法都提供如下接口

### stack_init
``` c
void stack_init(Stack * stack, destroy destroy);
```
* **返回值** 无
* **描述** 初始化由参数stack指定的栈。stack内存由调用的函数来分配，destroy函数将用来释放链表元素所占内存，可指定自定义的数据成员释放函数或为空。

### stack_destroy
``` c
void stack_destroy(Stack * stack);
```
* **返回值** 无
* **描述** 销毁由参数stack指定的栈，如果destroy成员不为空，则在移除链表中每个元素时将调用该函数一次。

### stack_push
``` c
int stack_push(Stack * stack, void * data);
```
* **返回值** 如果压入元素成功返回0，否则返回-1。
* **描述** 栈顶压入元素

### stack_pop
``` c
int stack_pop(Stack * stack, void ** data);
```
* **返回值** 如果元素出栈成功返回0，否则返回-1。
* **描述** 栈顶弹出元素，data指向己弹出元素中存储的数据。由调用函数负责管理data所引用的存储空间。

### stack_peek
```c
#define stack_peek(stack) ...;
```
* **描述** 返回栈顶元素的数据成员

### stack_is_empty
```c
#define stack_is_empty(stack) ...
```
* **描述** 判断栈是否为空

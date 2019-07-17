# 队列

<img src="https://github.com/sanzhiyan518/datastructure/blob/master/imgs/queue.png" />

## 栈特征

* 按照先进先出（FIFO）的方式存储和删除元素；

* 添加与删除元素分别在两端进行，在队尾添加，在队头删除；

* 有两种比较流行的实现方法，一种方法链表，而另一种方法使用数组；

* 具有两种基本操作Enqueue（入队）和Dequeue（出队）。

## 链表实现结构定义

``` c
typedef void (*destroy)(void * data);
//单链表实现队列结构体定义
typedef struct Node_ {
    struct Node_ * next;
    void * data;
} Node_;

typedef struct ListQueue_ {
    destroy destroy  //元素销毁函数
    Node * front;       //队头
    Node * rear;        //队尾
} ListQueue;

``` 

## 数组实现结构定义
``` c
//数组实现队列的结构体定义
typedef struct ArrayQueue {
    destroy destroy       //元素销毁函数
    int capacity;         //队列总长度
    int size;             //当前队列的长度
    int front;            //队头
    int rear;             //队尾
    void ** data;         //元素数组
} ArrayQueue;
```

## 接口定义

队列提供如下接口，两种实现方法都提供如下接口

### queue_init
``` c
void queue_init(Queue * q, destroy destroy);
```
* **返回值** 无
* **描述** 初始化由参数q指定的队列。q内存由调用的函数来分配，destroy函数将用来释放链表元素所占内存，可指定自定义的数据成员释放函数或为空。

### queue_destroy
``` c
void queue_destroy(Quque * q);
```
* **返回值** 无
* **描述** 销毁由参数q指定的队列，如果destroy成员不为空，则在移除每个元素时将调用该函数一次。

### queue_enqueue
``` c
int queue_enqueue(Quque * q, void * data);
```
* **返回值** 如果元素入队成功返回0，否则返回-1。
* **描述** 入队操作

### queue_dequeue
``` c
int queue_dequeue(Quque * q, void ** data);
```
* **返回值** 如果元素出队成功返回0，否则返回-1。
* **描述** 出队操作，data指向己出队元素中存储的数据。由调用函数负责管理data所引用的存储空间。

### queue_is_empty
```c
#define queue_is_empty(queue) ...
```
* **描述** 判断队列是否为空

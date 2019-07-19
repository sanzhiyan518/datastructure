# 链式散列表

<img src="https://github.com/sanzhiyan518/datastructure/blob/master/imgs/chainhashtable.png" />

## 链式散列表特征

* 包含一个哈希桶的数组，每个哈希桶是一个链表；

* 对于每个槽位上的哈希桶用来存储散列值为此槽位上的元素；

## 链式散列表结构体定义

```c

//散列函数
typedef int (*hash_fun)(const void *data);
//键值比较函数
typedef int (*match)(const void * key1, const void * key2);
//元素销毁函数
typedef void (*destroy)(void * data);
//单链表结构体定义
typedef struct Node_ {
    struct Node_ * next;
    void * data;
} Node;


typedef struct HanshTable_ {
    int buckets;                //哈希桶数
    hash_fun hash_fun;      //哈希函数
    match match;
    destroy destroy;             //元素销毁函数
    Node * table;               //哈希桶数组
} HashTable;

``` 
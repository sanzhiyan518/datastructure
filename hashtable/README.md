# 散列表

从根本上来说，一个哈希散列表包含一个数组，通过特殊的索引值来访问数组中的元素。哈希表的主要思想是通过一个哈希函数，在所有可能的键和槽位之间建立一张映射表。哈希函数每次接受一个键将返回与键相对应的哈希编码或哈希值。键的数据类型可能多种多样，但哈希值的类型只能是整形 。
当两个键映射到一个相同的槽位上时，它们就产生了冲突。一个好的哈希函数能最大限度地减少冲突，但冲突不可能完全削除，我们依然要想办法处理这些冲突。一般有两种方式来解决冲突：

## 链式散列表，数据存储在桶中，每个桶是一个链表

## 开地址散列表，数据存储在表中，通过多种探查方法来避免冲突问题

## 接口定义

### hashtable_init
``` c
void hashtable_init(HashTable * hashtable, int buckets, hash_fun hash_fun, match match, destroy  destroy);
```
* **返回值** 无
* **描述** 初始化由参数hashtable指定的散列表，结构体成员设置为传入的各个参数。

### hashtable_destroy
``` c
void hashtable_destroy(HashTable * hashtable);
```
* **返回值** 无
* **描述** 参数hashtable指定的散列表结构体成员置零，对于每个哈希桶释放其占用的内存块，如果传入的元素销毁函数，每个元素的数据成员要进行调用。

### hashtable_insert
``` c
int hashtable_insert(HashTable * hashtable, const void * data);
```
* **返回值** 无
* **描述** 插入数据

### hashtable_remove
``` c
int hashtable_remove(HashTable * hashtable,  void ** data);
```
* **返回值** 无
* **描述** 删除数据

### hashtable_lookup
``` c
int hashtable_lookup(HashTable * hashtable, void ** data);
```
* **返回值** 无
* **描述** 查找数据

# 散列函数

散列函数的目的是尽可能的产生均匀散列 ，包含各经典实现方法。

## 整形散列函数
```c
/* Thomas Wang's 32 bit Mix Function */
unsigned int dictIntHashFunction(unsigned int key)
{
    key += ~(key << 15);
    key ^=  (key >> 10);
    key +=  (key << 3);
    key ^=  (key >> 6);
    key += ~(key << 11);
    key ^=  (key >> 16);
    return key;
}

uint32_t hash( uint32_t a) 
{ 
   a = (a+0x7ed55d16) + (a<<12); 
   a = (a^0xc761c23c) ^ (a>>19); 
   a = (a+0x165667b1) + (a<<5); 
   a = (a+0xd3a2646c) ^ (a<<9); 
   a = (a+0xfd7046c5) + (a<<3); // <<和 +的组合是可逆的 
   a = (a^0xb55a4f09) ^ (a>>16);  
   return a; 
}

uint64_t hash64shift(uint64_t key) 
{ 
  key = (~key) + (key << 21); // key = (key << 21) - key - 1; 
  key = key ^ (key >> 24); 
  key = (key + (key << 3)) + (key << 8); // key * 265 
  key = key ^ (key >> 14); 
  key = (key + (key << 2)) + (key << 4); // key * 21 
  key = key ^ (key >> 28); 
  key = key + (key << 31); 
  return key; 
}

uint32_t hash64_32shift(uint64_t key) 
{ 
  key = (~key) + (key << 18); // key = (key << 18) - key - 1; 
  key = key ^ (key >> 31); 
  key = key * 21; // key = (key + (key << 2)) + (key << 4); 
  key = key ^ (key >> 11); 
  key = key + (key << 6); 
  key = key ^ (key >> 22); 
  return (int) key; 
}

uint32_t mix(uint32_t a, uint32_t b, uint32_t c) 
{ 
  a=a-b;  a=a-c;  a=a^(c >> 13); 
  b=b-c;  b=b-a;  b=b^(a << 8); 
  c=c-a;  c=c-b;  c=c^(b >> 13); 
  a=a-b;  a=a-c;  a=a^(c >> 12); 
  b=b-c;  b=b-a;  b=b^(a << 16); 
  c=c-a;  c=c-b;  c=c^(b >> 5); 
  a=a-b;  a=a-c;  a=a^(c >> 3); 
  b=b-c;  b=b-a;  b=b^(a << 10); 
  c=c-a;  c=c-b;  c=c^(b >> 15); 
  return c; 
}

```

## 字符串散列函数

```c
unsigned int SDBMHash(char *str)
{
    unsigned int hash = 0;
    while (*str)
    {
        // equivalent to: hash = 65599*hash + (*str++);
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }
 
    return (hash & 0x7FFFFFFF);
}
 
// RS Hash Function
unsigned int RSHash(char *str)
{
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
 
    while (*str)
    {
        hash = hash * a + (*str++);
        a *= b;
    }
 
    return (hash & 0x7FFFFFFF);
}
 
// JS Hash Function
unsigned int JSHash(char *str)
{
    unsigned int hash = 1315423911;
 
    while (*str)
    {
        hash ^= ((hash << 5) + (*str++) + (hash >> 2));
    }
 
    return (hash & 0x7FFFFFFF);
}
 
// P. J. Weinberger Hash Function
unsigned int PJWHash(char *str)
{
    unsigned int BitsInUnignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    unsigned int ThreeQuarters    = (unsigned int)((BitsInUnignedInt  * 3) / 4);
    unsigned int OneEighth        = (unsigned int)(BitsInUnignedInt / 8);
    unsigned int HighBits         = (unsigned int)(0xFFFFFFFF) << (BitsInUnignedInt - OneEighth);
    unsigned int hash             = 0;
    unsigned int test             = 0;
 
    while (*str)
    {
        hash = (hash << OneEighth) + (*str++);
        if ((test = hash & HighBits) != 0)
        {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }
 
    return (hash & 0x7FFFFFFF);
}
 
// ELF Hash Function
unsigned int ELFHash(char *str)
{
    unsigned int hash = 0;
    unsigned int x    = 0;
 
    while (*str)
    {
        hash = (hash << 4) + (*str++);
        if ((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
            hash &= ~x;
        }
    }
 
    return (hash & 0x7FFFFFFF);
}
 
// BKDR Hash Function
unsigned int BKDRHash(char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;
 
    while (*str)
    {
        hash = hash * seed + (*str++);
    }
 
    return (hash & 0x7FFFFFFF);
}
 
// DJB Hash Function
unsigned int DJBHash(char *str)
{
    unsigned int hash = 5381;
 
    while (*str)
    {
        hash += (hash << 5) + (*str++);
    }
 
    return (hash & 0x7FFFFFFF);
}
 
// AP Hash Function
unsigned int APHash(char *str)
{
    unsigned int hash = 0;
    int i;
 
    for (i=0; *str; i++)
    {
        if ((i & 1) == 0)
        {
            hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
        }
        else
        {
            hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
        }
    }
 
    return (hash & 0x7FFFFFFF);
}

```

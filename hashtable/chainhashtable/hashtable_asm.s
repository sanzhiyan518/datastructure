.global hashtable_init_asm, hashtable_destroy_asm, hashtable_insert_asm, hashtable_remove_asm, hashtable_lookup_asm

#初始化
hashtable_init_asm:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp                     #开栈保存参数及局部变量

    movq %rdi, (%rsp)                  #保存哈希表参数
    movq %rsi, (%rdi)                  #设置哈希桶数组个数
    movq %rdx, 8(%rdi)                 #设置散列函数成员
    movq %rcx, 16(%rdi)                #设置比较函数成员
    movq %r8, 24(%rdi)                 #设置元素销毁函数成员

    movq %rsi, %rdi                    #计算哈希桶数据内存块大小，并存栈，以备后内存块置零用
    imulq $8, %rdi
    movq %rdi, 8(%rsp)
    call  malloc                       #分配哈希桶数组内存
    movq (%rsp), %rdi                  #设置哈希桶成员
    movq %rax, 32(%rdi)
    movq %rax, %rdi                    #哈希桶数组内存块置零
    movq $0x0,%rsi
    movq 8(%rsp),%rdx
    call memset
    leave
    ret

#销毁
hashtable_destroy_asm:
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp                     #开栈

    movq 32(%rdi), %rax                #哈希桶数组地址入栈rsp，避免二次内存寻址
    movq %rax, (%rsp)
    movq 24(%rdi), %rcx                #元素销毁函数入栈rsp+8
    movq %rcx, 8(%rsp)
    movq %rax, 16(%rsp)                #哈希桶遍历变量入栈rsp+16,起始值为数组地址
    movq (%rdi), %rcx                  #获取哈希桶数组尾端地址入栈rsp+24
    leaq (%rax,%rcx, 8), %rax
    movq  %rax, 24(%rsp)

    movq $0, %rsi                      #哈希表结构体清零
    movq $40,%rdx
    call memset

    #开始遍历哈希桶数组
    jmp  1f

2:
    movq (%rax), %rcx                 #判断是否为空桶
    jrcxz  3f

    movq %rcx, 32(%rsp)               #哈希链表遍历元素入栈rsp+32
    jmp 4f                            #开始循环遍历哈希桶中的链表元素

6:
    movq %rax, 40(%rsp)               #链表遍历元素的前驱入栈rsp+40
    movq (%rax), %rcx                 #修改遍历后为后继元素
    movq %rcx, 32(%rsp)
    movq 8(%rsp), %rcx                #取出元素销毁函数，判断是否为空
    jrcxz 5f
    movq 8(%rax),%rdi                 #调用元素销毁函数
    call *%rcx
5:
    movq 40(%rsp), %rdi               #释放遍历元素的内存
    call free

4:
    movq 32(%rsp),%rax                #判断链表是否遍历结束
    cmpq $0, %rax
    jne  6b

3:
    addq $8, 16(%rsp)                 #遍历桶的指针前进

1:
    movq 16(%rsp), %rax               #判断哈希桶数据是否遍历结束
    cmpq %rax, 24(%rsp)
    jne 2b

    movq (%rsp),%rdi                  #释放哈希桶数组内存块
    call free
    leave
    ret

#内部函数获取数据所槽位桶地址
hashtable_position:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    movq 32(%rdi), %rax              #哈希桶数组地址入栈rsp，避免二次内存寻址
    movq %rax, (%rsp)
    movq (%rdi), %rax                #桶个数入栈rsp+8
    movq %rax, 8(%rsp)
    movq 8(%rdi), %rcx               #调用散列函数
    movq %rsi, %rdi
    callq *%rcx
    xorq %rdx, %rdx                  #计算槽位
    idivq 8(%rsp)
    movq (%rsp), %rbx                #获取桶地址
    leaq (%rbx,%rdx,8), %rax
    leave
    ret

#插入操作
hashtable_insert_asm:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp
    movq %rsi,(%rsp)                #数据成员入栈rsp
    call hashtable_position         #获取所在槽位，入栈rsp+8
    movq %rax, 8(%rsp)

    movq $16, %rdi                  #链表元素内存分配
    call malloc

    cmpq $0, %rax                 #内存分配失败返回-1
    jne 1f
    movq $-1, %rax
    leave
    ret

1:
    movq (%rsp), %rcx               #设置链表元素数据成员
    movq %rcx, 8(%rax)

    movq 8(%rsp), %rbx            #判断槽位据桶是否为空桶
    movq (%rbx), %rcx
    jrcxz  2f
    #不为空桶，将元素链入链表头
    movq (%rcx), %rdx
    movq  %rdx, (%rax)
    movq  %rax, (%rcx)
    jmp  3f
2:
    movq %rax, (%rbx)              #空桶新元素为链表头
    movq $0, (%rax)

3:
    movq $0x0,%rax
    leave
    ret

hashtable_remove_asm:
    pushq %rbp
    movq %rsp, %rbp
    subq  $48, %rsp
    movq %rsi, (%rsp)             #数据成员地址入栈rsp
    movq (%rsi), %rsi             #数据成员入栈rsp+40
    movq %rsi, 40(%rsp)

    movq 16(%rdi),%rax            #元素比较函数入栈rsp+8
    movq %rax,8(%rsp)
    call hashtable_position       #获取槽位所在桶地址入栈rsp+16
    movq %rax, 16(%rsp)

    movq (%rax), %rcx             #桶链表遍历元素入栈rsp+24, 初始值桶链表头
    movq %rcx, 24(%rsp)
    movq $0, 32(%rsp)             #遍历前驱入栈rsp+32，初始值为空

    jrcxz  1f                     #空桶返回-1

    jmp 2f                        #遍历桶链表

6:
    movq 8(%rcx), %rsi            #调用元素比较函数
    movq 40(%rsp), %rdi
    call *8(%rsp)

    cmp $0, %rax                 #判断是否相同
    jne  3f                      #不同继续

    movq 24(%rsp),%rdi           #取出遍历元素及后继
    movq (%rdi), %rcx
    cmpq $0, 32(%rsp)            #判断遍历元素是否为链表头
    jne  4f
    movq 16(%rsp), %rbx          #删除元素为链表头则链表头设置为后继
    movq %rcx, (%rbx)
    jmp 5f
4:
    movq 32(%rsp),%rbx     	#修改元素前驱的后继
    movq %rcx,(%rbx)
5:
    movq (%rsp),%rcx            #传出数据成员,释放元素内存
    movq 8(%rdi),%rax
    movq %rax,(%rcx)
    call free
    movq $0, %rax               #返回0
    leave
    ret

3:
    movq 24(%rsp), %rax         #修改遍历元素为后继,前驱显为遍历元素
    movq %rax, 32(%rsp)
    movq (%rax), %rax
    movq %rax, 24(%rsp)

2:
    movq 24(%rsp), %rcx         #判断链表是否遍历结束
    cmpq $0, %rcx
    jne 6b

1:
    movq $-1,%rax
    leave
    ret

hashtable_lookup_asm:
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp
    movq %rsi, (%rsp)             #数据成员地址入栈rsp
    movq (%rsi), %rsi             #数据成员入栈rsp+40
    movq %rsi, 40(%rsp)
    movq 16(%rdi), %rax           #元素比较函数入栈rsp+8
    movq %rax, 8(%rsp)
    call hashtable_position       #获取槽位所在桶地址入栈rsp+16
    movq %rax, 16(%rsp)

    movq (%rax), %rcx             #桶链表遍历元素入栈rsp+24, 初始值桶链表头
    movq %rcx, 24(%rsp)

    jrcxz  1f                     #空桶返回-1

    jmp 2f                        #遍历桶链表

4:
    movq 8(%rcx), %rsi            #调用元素比较函数
    movq 40(%rsp), %rdi
    call *8(%rsp)
    cmp $0, %rax                  #判断是否相同
    jne  3f                       #不同继续
    movq 24(%rsp), %rax           #相同传出数据成员,返回0
    movq 8(%rax),%rax
    movq (%rsp),%rcx
    movq %rax,(%rcx)
    movq $0,%rax
    leave
    ret

3:
    movq 24(%rsp), %rax          #修改遍历元素为后继
    movq (%rax),%rax
    movq %rax, 24(%rsp)

2:
    movq 24(%rsp),%rcx         #判断链表是否遍历结束
    cmpq $0, %rcx
    jne 4b

1:
    movq $-1,%rax
    leave
    ret

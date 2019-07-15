.global clist_init_asm, clist_destroy_asm, clist_ins_next_asm, clist_rem_next_asm

#链表初始化
clist_init_asm:
    #链表参数在rdi中
    movq $0, (%rdi)
    movq $0, 8(%rdi)
    #元素销毁函数在rsi中
    movq %rsi, 16(%rdi)
    movq $0, 24(%rdi)
    ret

#链表元素销毁
clist_destroy_asm:
    #判断链表长度是否为零，为零直接调将链表内存清零
    cmpq $0, (%rdi)
    je 1f

    #链表长度不为零
    #开栈保存参数，以防调用函数后寄存器发生变化
    subq $32, %rsp
    #链表参数使用rsp
    movq %rdi, (%rsp)
    #元素数据销毁函数使用8(%rsp)
    movq 16(%rdi),  %rax
    movq %rax, 8(%rsp)
    #遍历元素使用16(%rsp)
    movq 24(%rdi), %rax
    movq %rax, 16(%rsp)
    #遍历元素的前驱使用24(%rsp)，用于修改遍历元素的临时变量

2:
    #取出遍历元素
    movq 16(%rsp), %rcx
    #将遍历元素修改为其后继,遍历元素存到临时变量
    movq %rcx, 24(%rsp)
    movq 16(%rcx), %rax
    movq %rax, 16(%rsp)

    #判断元素释放函数是否为空
    movq 8(%rsp), %rax
    cmpq $0, %rax
    je 3f
    #调用元素数据释放函数
    movq  (%rcx), %rdi
    call *%rax

3:
    #释放元素内存,此时元素在24(%rsp)中，需要从内存再取一次
    movq 24(%rsp), %rax
    movq %rax, %rdi
    call free

    #判断前驱元素是否循环回链表头
    movq (%rsp), %rax
    movq 24(%rax), %rax
    cmpq %rax, 16(%rsp)
    jne 2b

4:
    #恢复栈
    movq (%rsp), %rdi
    addq $32, %rsp

1:
    #链表内存清零
    movq $0, (%rdi)
    movq $0, 8(%rdi)
    movq $0, 16(%rdi)
    movq $0,  24(%rdi)
    ret

#插入
clist_ins_next_asm:
    #判断传入前驱元素是否为空
    cmpq $0, %rsi
    jne 1f
    #判断链表长度是否为零
    cmpq $0, (%rdi)
    je 1f
    movq $-1, %rax
    ret

1:
    #参数入栈防止函数调用后，寄存器发生变化
    subq $24, %rsp
    movq %rdi, (%rsp)
    movq %rsi, 8(%rsp)
    movq %rdx, 16(%rsp)

    #新元素分配内存
    movq $24, %rdi
    call malloc

    #参数出栈到寄存器恢复
    movq 16(%rsp), %rdx
    movq 8(%rsp), %rsi
    movq (%rsp), %rdi
    addq $24, %rsp

    #内存分配失败返回-1
    cmpq $0, %rax
    jne 2f
    movq $-1, %rax
    ret

2:
    #元素数据成员设置
    movq %rdx, (%rax)
    #比较链表长度
    cmpq $0, (%rdi)
    jne 3f

    #链表长度为零，则设置元素为链表头，且元素自链
    movq %rax, 8(%rax)
    movq %rax, 16(%rax)
    movq %rax, 24(%rdi)
    jmp 4f

3:
    #与前驱元素链接
    #前驱元素的后继使用rcx
    movq 16(%rsi), %rcx
    movq %rcx, 16(%rax)
    movq %rsi, 8(%rax)

    movq %rax, 16(%rsi)
    movq %rax, 8(%rcx)

4:
    incq (%rdi)
    movq $0, %rax
    ret

#删除
clist_rem_next_asm:
    #链表长度为零返回-1
    cmpq $0, (%rdi)
    jne 1f
    movq $-1, %rax
    ret

1:
    #传入元素的后继为删除元素存储在rax
    movq 16(%rsi), %rax
    #判断是否自链，自链表则只有一个元素，将设置链表为空
    cmpq %rax, %rsi
    jne 2f
    movq $0, 24(%rdi)
    jmp 3f

2:
    #将删除元素与前、后元素断链
    #删除的后继元素存储在rcx
    movq 16(%rax), %rcx
    movq %rcx, 16(%rsi)
    movq %rsi, 8(%rcx)
    #比较元素是否链表头，是则设置链表头为后继
    cmpq %rax, 24(%rdi)
    jne 3f
    movq %rcx, 24(%rdi)

3:
    #删除的数据成员传出
    movq (%rax), %rcx
    movq %rcx, (%rdx)
    #链表长度减1
    decq (%rdi)
    #释放删除元素所占内存
    movq %rax, %rdi
    call free

    #返回0
    movq $0, %rax
    ret

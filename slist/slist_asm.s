.global list_init_asm, list_destroy_asm, list_ins_next_asm, list_rem_next_asm

LIST_SIZE:
    .int 20

LIST_ELEMENT_SIZE:
    .int 8

#链表构建
list_init_asm:
    #链表结构体直接赋给ebx
    movl 4(%esp), %ebx
    #设置结构体成员
    #长度
    movl $0, (%ebx)
    #比较函数
    movl $0, 4(%ebx)
    #元素销毁函数
    movl 8(%esp), %eax
    movl %eax, 8(%ebx)
    #头、尾
    movl $0, 12(%ebx)
    movl $0, 16(%ebx)
    ret

#链表销毁
list_destroy_asm:
    #开栈
    pushl %ebp
    movl %esp, %ebp
    subl $8, %esp

    #取出链表参数
    movl 8(%ebp), %ebx
    #遍历链表的元素存放在esp(ebp-8),起始值为链表头
    movl 12(%ebx), %eax
    movl %eax, (%esp)
    #元素释放函数存储在esp+4(ebp-4)
    movl 8(%ebx), %eax
    movl %eax, 4(%esp)

    #循环遍历链表
    jmp 1f

2:
    #取出遍历元素
    movl  (%esp), %eax
    #将元素压栈供释放函数调用
    pushl %eax
    #修改元素指向下一个元素
    movl 4(%eax), %ebx
    movl %ebx, 4(%esp)
    #此时eax存放着当前遍历的元素
    #判断元素释放函数是否为空
    cmpl $0, 8(%esp)
    je 3f
    #释放元素数据成员
    pushl (%eax)
    call * -4(%ebp)
    addl $4, %esp

3:
    #释放元素
    call free
    addl $4, %esp

1:
    #判断遍历链表是否完成
    cmpl $0, (%esp)
    jne 2b

    #链表内存清零
    pushl LIST_SIZE
    pushl $0
    pushl 8(%ebp)
    call memset
    leave
    ret

#插入操作
list_ins_next_asm:
    #新链表元素分配内存，分配完成后在eax寄存器
    pushl LIST_ELEMENT_SIZE
    call malloc
    addl $4, %esp

    #内存分配失败返回-1
    cmpl $0, %eax
    jne 1f
    movl -1, %eax
    ret

1:
    #链表元素初始化
    #数据成员
    movl 12(%esp), %ecx
    movl %ecx, (%eax)
    #链接元素为空
    movl $0, 4(%eax)

    #使用ebx寄存器存储链表参数
    movl 4(%esp), %ebx
    #使用ecx寄存器存储前向链表参数
    movl 8(%esp), %ecx

    #判断是否传入前向链表元素
    cmpl $0,  %ecx
    jne 2f
    #未传入前向链表元素，则将新链表元素做为链表头
    #判断链表是否空，空则新元素也是链表尾
    cmpl $0, (%ebx)
    jnz 3f
    #新元素为链表尾
    movl %eax, 16(%ebx)
3:
    #新元素为链表头
    movl 12(%ebx), %edx
    movl %edx, 4(%eax)
    movl %eax, 12(%ebx)
    jmp 4f

2:
    #传入了前向链表元素
    #前向链表元素是否为尾，是则新元素为链表尾
    cmpl 16(%ebx), %ecx
    jne 5f
    #新元素为链表尾
    movl %eax, 16(%ebx)
5:
    #新元素与前向元素链接
    movl 4(%ecx), %edx
    movl %edx, 4(%eax)
    movl %eax, 4(%ecx)

4:
    #链表元素个数增加
    incl (%ebx)
    #返回零
    xorl %eax, %eax
    ret

#删除操作
list_rem_next_asm:
    #返回值设置-1
    movl $-1, %eax
    #使用ebx存储链表
    movl 4(%esp), %ebx
    #判断链表是否含有元素，没有返回-1
    cmpl $0, (%ebx)
    jne 1f
    ret

1:
    #前向元素使用ecx
    movl 8(%esp), %ecx

    #判断前向元素是否为空
    cmpl $0, %ecx
    je 2f
    #前向元素不为空
    #取出前向链接元素做为删除元素，使用edx存储
    movl 4(%ecx), %edx
    #判断删除元素是否为空，为空返回
    cmpl $0, %edx
    jne 5f
    ret
5:
    #判断删除元素是否为链表尾，是则链表尾修改为前向元素
    cmpl %edx, 16(%ebx)
    jne 3f
    #修改链表尾
    movl %ecx, 16(%ebx)
3:
    #修改元素间链接关系
    movl 4(%edx), %eax
    movl %eax, 4(%ecx)
    jmp 4f

2:
    #未传入前向元素，则删除链表头元素
    movl 12(%ebx), %edx
    #判断链表是否只有一个元素，是则链表尾修改为空
    cmpl %edx, 16(%ebx)
    jne 5f
    #修改链表尾
    movl $0, 16(%ebx)
5:
    #修改链表头
    movl 4(%edx), %eax
    movl %eax, 12(%ebx)

4:
    #edx存储删除元素，释放删除元素内存
    #将删除元素数据成员传出
    movl 12(%esp), %eax
    movl (%edx), %ecx
    movl %ecx, (%eax)
    #链表元素个数减1
    decl (%ebx)
    #释放删除元素内存
    pushl %edx
    call free
    popl %edx
    xorl %eax, %eax
    ret

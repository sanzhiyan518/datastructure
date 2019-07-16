.global liststack_init_asm, liststack_destroy_asm, liststack_push_asm, liststack_pop_asm
.global arraystack_init_asm, arraystack_destroy_asm, arraystack_push_asm, arraystack_pop_asm

#栈初始化, rdi为栈参数，rsi为元素销毁函数
liststack_init_asm:
    movq %rsi, (%rdi)
    movq $0, 8(%rdi)
    ret

arraystack_init_asm:
    #为栈结构体参数成员:销毁函数和栈顶赋值
    movq %rsi, (%rdi)
    movl $-1, 12(%rdi)
    #栈参数入栈
    pushq %rdi
    #计算数组内存块大小
    movl 8(%rdi), %edi
    imull $8, %edi
    #分配数组内存
    call malloc
    #栈参数出栈
    popq %rdi
    #为数组成员赋值
    movq %rax, 16(%rdi)
    ret

#栈元素销毁,rdi为栈参数
liststack_destroy_asm:
    #开栈保存变量
    subq $24, %rsp
    #遍历元素使用rsp,初始值为栈的链表头
    movq 8(%rdi), %rax
    movq %rax, (%rsp)
    #元素销毁函数使用rsp+8
    movq (%rdi), %rax
    movq %rax, 8(%rsp)
    #遍历的前驱使用rsp+16,用于销毁元素及其数据成员

    #先将栈的成员置零，这样不用再存储传入的栈参数
    movq $0, (%rdi)
    movq $0, 8(%rdi)

    #开始循环
    jmp 1f

2:
    #循环取出遍历元素
    movq (%rsp), %rax
    #遍历元素修改为后继元素
    movq 8(%rax), %rcx
    movq %rcx, (%rsp)
    #遍历元素存储在前驱变量中，后而销毁用
    movq %rax, 16(%rsp)

    #取出元素销毁函数
    movq 8(%rsp), %rcx
    #比较元素销毁函数是否为空
    cmpq $0, %rcx
    je 3f
    #调用元素销毁函数
    movq (%rax), %rdi
    call *%rcx
3:
    #释放元素内存块
    movq 16(%rsp), %rdi
    call free

1:
    #遍历是否己结束
    cmpq $0, (%rsp)
    jne 2b

    addq $24, %rsp
    ret

arraystack_destroy_asm:
    #开栈保存参数及局部变量
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp
    #遍历元素的整形变量使用(%rsp)，初始值为栈顶
    xorq %rax, %rax
    movl 12(%rdi), %eax
    movq %rax, (%rsp)
    #栈数组成员使用rsp+8
    movq 16(%rdi), %rax
    movq %rax, 8(%rsp)
    #栈参数使用rsp+16
    movq %rdi, 16(%rsp)
    #元素销毁函数使用rsp+24
    movq (%rdi), %rcx
    movq %rcx, 24(%rsp)
    #元素销毁函数为空则直接栈内存块置零即可
    jrcxz 1f

    #循环调用元素销毁函数
    jmp 3f

2:
    #取出销毁元素
    movq 8(%rsp), %rbx          #栈的数组成员
    movq (%rsp), %rcx            #当前索引
    movq (%rbx, %rcx, 8), %rdi
    movq 24(%rsp), %rax
    call *%rax
    decq (%rsp)

3:
    #判断是否己结束
    cmpl $0, (%rsp)
    jge 2b

1:
    movq 16(%rsp), %rdi
    movl $-1, 12(%rdi)
    #释放数组内存
    movq 16(%rdi), %rdi
    call free

    leave
    ret

#进栈
liststack_push_asm:
    pushq %rdi                  #参数入栈
    pushq %rsi

    movq $16, %rdi             #链表元素分配内存
    call malloc
    popq %rsi                     #参数出栈
    popq %rdi

    cmpq $0, %rax               #判断元素内存分配是否成功
    jne 1f
    movq $-1, %rax               #失败返回-1
    ret

1:
    movq %rsi, (%rax)           #设置元素数据成员

    cmpq $0, 8(%rdi)            #比较栈的链表头是否为空
    jne 2f
    movq $0, 8(%rax)             #链表为空，设置元素为链表头
    movq %rax,  8(%rdi)
    jmp 3f

2:
    movq 8(%rdi), %rcx          #元素的后继设置为链表头，重新设置链表头为新元素
    movq %rcx, 8(%rax)
    movq %rax, 8(%rdi)

3:
    movq $0, %rax
    ret

arraystack_push_asm:
    xorq %rcx, %rcx
    movl 12(%rdi), %ecx       #取出栈顶，判断栈顶加1是否己经达到栈深
    incl %ecx
    cmpl 8(%rdi), %ecx
    jl 1f
    movq $-1, %rax
    ret

1:
    movq 16(%rdi), %rbx               #设置栈顶数据成员
    movq %rsi, (%rbx, %rcx, 8)
    movl %ecx, 12(%rdi)
    movq $0, %rax
    ret

#出栈
liststack_pop_asm:
    movq 8(%rdi), %rax              #取出链表头
    cmpq $0, %rax                     #判断链表是否为空
    jne 1f
    movq $-1, %rax
    ret

1:
    movq 8(%rax), %rcx             #设置链表头为后继元素
    movq %rcx, 8(%rdi)
    movq (%rax), %rcx               #传出数据成员
    movq %rcx, (%rsi)
    movq %rax, %rdi                 #释放元素内存
    call free
    movq $0, %rax
    ret

arraystack_pop_asm:
    cmpl $-1, 12(%rdi)             #比较是否为空栈
    jne 1f
    movq $-1, %rax
    ret

1:
    movq 16(%rdi), %rbx
    xorq %rcx, %rcx
    movl 12(%rdi), %ecx
    movq (%rbx, %rcx, 8), %rax   #传出数据成员
    movq %rax, (%rsi)
    decl 12(%rdi)                       #栈顶减1
    movq $0, %rax
    ret

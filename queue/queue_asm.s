.global arrayqueue_init_asm,  listqueue_init_asm, arrayqueue_destroy_asm, listqueue_destroy_asm
.global arrayqueue_enqueue_asm, listqueue_enqueue_asm, arrayqueue_dequeue_asm, listqueue_dequeue_asm

#队列初始化
arrayqueue_init_asm:
    pushq %rbp
    movq %rsp, %rbp
    movq %rsi, (%rdi)        #设置元素销毁函数
    movq $0, 12(%rdi)       #设置队列大小
    movq $0, 16(%rdi)       #设置队列头
    movq $-1, 20(%rdi)      #设置队列尾
    subq $16, %rsp
    movq %rdi, (%rsp)       #队列参数压栈，防止后面调用函数发生变化
    movl 8(%rdi), %edx      #计算元素数组大小，并压栈
    imull $8, %edx
    movl %edx, 8(%rsp)
    movl %edx, %edi
    call malloc                   #元素数组分配内存
    movl 8(%rsp), %edx          #恢复数组大小
    movq (%rsp), %rdi            #恢复栈参数

    movq %rax, 24(%rdi)    #设置元素数组成员
    movq %rax, %rdi          #元素数组内存清零
    movl $0, %esi
    call memset

    leave
    ret

listqueue_init_asm:
    movq %rsi, (%rdi)        #设置元素销毁函数
    movq $0, 8(%rdi)         #设置队列头与尾
    movq $0, 16(%rdi)
    ret

arrayqueue_destroy_asm:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp                  #开栈保存参数及局部变量

    xorq %rax, %rax                 #遍历数据变量在rsp初始值为队列容量-1
    movl 8(%rdi), %eax
    decq %rax
    movq %rax, (%rsp)

    movq 24(%rdi), %rax           #元素数组在rsp+8,以例后面使用时不再二次内存访问获取
    movq %rax, 8(%rsp)

    movq %rdi, 16(%rsp)           #队列参数在rsp+16

    movq (%rdi), %rcx               #元素销毁函数在rsp+24
    movq %rcx, 24(%rsp)           #队列参数在rsp

    jrcxz 1f                                 #元素销毁函数为空直接清空队列结构及释放数组

    #遍历数组调用元素释放函数
    jmp 2f

3:
    movq 8(%rsp), %rbx             #数据数组中元素
    movq (%rbx, %rcx, 8), %rdi
    cmpq $0, %rdi                   #
    je 4f
    movq 24(%rsp), %rax            #调用元素销毁函数
    call * %rax

4:
    decq (%rsp)                          #递减变量

2:
    movq (%rsp), %rcx               #判断遍历是否结束
    cmpq $0, %rcx
    jge 3b

1:
    movq 16(%rsp), %rdi           #恢复队列参数，设置各个成员
    movl $0, 12(%rdi)               #设置队列大小
    movl $0, 16(%rdi)               #设置队列头
    movl $-1, 20(%rdi)              #设置队列尾
    movq 24(%rdi), %rdi           #释放数组内存块
    call free

    leave
    ret

listqueue_destroy_asm:
    pushq %rbp
    movq %rsp, %rbp
    pushq (%rdi)                      #开栈压入元素销毁函数rsp+16
    pushq 8(%rdi)                    #压入链表头做遍历元素rsp+8
    pushq $0                           #遍历元素的前驱rsp

    movq $0, 8(%rdi)                #队列头、尾清零
    movq $0, 16(%rdi)

    jmp 1f

4:
    movq %rax, (%rsp)           #修改前驱元素为遍历元素
    movq 8(%eax), %rcx          #修改遍历元素为后继
    movq %rcx, 8(%rsp)

    movq 16(%rsp), %rcx        #调用元素销毁函数
    cmpq $0, %rcx
    je 2f
    movq (%rax), %rdi
    call *%rcx

2:
    movq (%rsp), %rdi            #释放元素内存
    call free

1:
    movq 8(%rsp), %rax
    cmpq $0, %rax                 #遍历是否结束
    jne 4b

    leave
    ret

#入队
arrayqueue_enqueue_asm:
    movl 12(%rdi), %ecx       #判断队列是否己满，是则返回-1
    cmpl 8(%rdi), %ecx
    jb 1f
    movq $-1, %rax
    ret

1:
    xorq %rcx, %rcx
    movl 20(%rdi), %ecx       #队尾加1
    incl  %ecx
    cmpl 8(%rdi), %ecx         #队尾己达队列容量上限，则返回起始
    jne 2f
    movl $0, %ecx
2:
    movl %ecx, 20(%rdi)       #回写队尾
    movq 24(%rdi), %rbx      #数据成员写入数组
    movq %rsi, (%rbx, %rcx, 8)
    incl 12(%rdi)                   #队列大小加1
    ret

listqueue_enqueue_asm:
    pushq %rdi                  #保存参数
    pushq %rsi
    movq $16, %rdi            #链表元素分配内存
    call malloc
    popq %rsi                     #出栈
    popq %rdi

    cmpq $0, %rax              #元素内存分配失败返回-1
    jne 3f
    movq $-1, %rax
    ret

3:
    movq %rsi, (%rax)        #设置元素成员
    movq $0, 8(%rax)

    cmpq $0, 16(%rdi)       #判断队列是否为空栈
    jne 1f
    movq %rax, 8(%rdi)      #空栈设置队头为新元素
    jmp 2f

1:
    movq 16(%rdi), %rcx     #设置队尾的后继是新元素
    movq %rax, 8(%rcx)

2:
    movq %rax, 16(%rdi)    #设置队尾为新元素
    movq $0, %rax
    ret

#出队操作
arrayqueue_dequeue_asm:
    cmpq $0, 12(%rdi)        #空队返回-1
    jne 1f
    movq $-1, %rax

1:
    xorq %rcx, %rcx
    movl 16(%rdi), %ecx           #传出队头元素
    movq 24(%rdi), %rbx
    movq (%rbx, %rcx, 8), %rax
    movq %rax, (%rsi)
    movq $0, (%rbx, %rcx, 8)

    incl %ecx                       #队头加1，达到容量上限返回到起始
    cmpl 8(%rdi), %ecx
    jne 2f
    movl $0, %ecx
2:
    movl %ecx, 16(%rdi)
    decl 12(%rdi)                   #队列大小减1
    movq $0, %rax
    ret

listqueue_dequeue_asm:
    movq 8(%rdi), %rax          #取出队列头元素
    cmpq $0, %rax                 #判断是否为空队列，是则返回-1
    jne 1f
    movq $-1, %rax
    ret

1:
    movq (%rax), %rcx            #传出数据成员
    movq %rcx, (%rsi)

    movq 8(%rax), %rcx          #修改队列头为元素的后继
    movq %rcx, 8(%rdi)

    cmpq $0, %rcx                #判断后继元素是否为空，是则表明为空队列，设置队头尾为空
    jne 2f
    movq $0, 16(%rdi)

2:
    movq %rax, %rdi             #释放元素内存
    call free
    movq $0, %rax
    ret

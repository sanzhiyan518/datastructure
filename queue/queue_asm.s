.global _queue_init_asm, _queue_destroy_asm, _queue_full_asm, _queue_empty_asm, _queue_enter_asm, _queue_delete_asm
_void_size:
    .int 4
_queue_size:
    .int 20

#队列初始化
_queue_init_asm:
    pushl %ebp
    movl %esp, %ebp
    subl $8, %esp
    pushl _queue_size
    call _malloc
    #队列使用寄存器%esp+4
    movl %eax, 4(%esp)
    #数组内存分配
    movl _void_size, %eax
    movl 8(%ebp), %edx
    mull %edx
    movl %eax, (%esp)
    call _malloc

    #队列初始化
    movl %eax, %edx
    movl 4(%esp), %eax
    movl 8(%ebp), %ecx
    movl %ecx, (%eax)
    movl $0, 4(%eax)
    movl $0, 8(%eax)
    movl $-1, 12(%eax)
    movl %edx, 16(%eax)

    leave
    ret


#队列销毁
_queue_destroy_asm:
    cmpl $0, 4(%esp)
    je 1f

    movl 4(%esp), %eax
    movl 16(%eax), %eax
    pushl %eax
    call _free
    movl 8(%esp), %eax
    movl %eax, (%esp)
    call _free
    addl $4, %esp

1:
    ret

#判断队列是否为空
_queue_empty_asm:
    movl $-1, %eax
    cmpl $0, 4(%esp)
    je 1f

    movl 4(%esp), %edx
    cmpl $0, 4(%edx)
    jne 1f
    movl $0, %eax

1:
    ret

#判断队列是否己满
_queue_full_asm:
    movl $-1, %eax
    cmpl $0, 4(%esp)
    je 1f

    movl 4(%esp), %edx
    #比较队列长度与容积
    cmpl (%edx), %ecx
    cmpl %ecx, 4(%edx)
    jne 1f
    movl $0, %eax

1:
    ret

#入队操作
_queue_enter_asm:
    movl $-1, %eax
    cmpl $0, 4(%esp)
    je 1f

    #队列使用ebx寄存器
    movl 4(%esp), %ebx
    #判断队列是否己满
    movl (%ebx), %ecx
    cmpl %ecx, 4(%ebx)
    je 1f

    #未满队尾向前
    movl 12(%ebx), %ecx
    incl %ecx
    #如果队尾已经到达最大容积，则归零
    cmpl %ecx, (%ebx)
    jne 2f
    movl $0, %ecx
2:
    #重新设置队尾
    movl %ecx, 12(%ebx)
    #队长度增1
    incl 4(%ebx)
    #入队
    movl 16(%ebx), %ebx
    movl 8(%esp), %edx
    movl %edx, (%ebx, %ecx, 4)
    movl $0, %eax

1:
    ret

#出队操作
_queue_delete_asm:
    movl $-1, %eax
    cmpl $0, 4(%esp)
    je 1f

    #判断队列是否为空
    #队列使用ebx寄存器
    movl 4(%esp), %ebx
    cmpl $0, 4(%ebx)
    je 1f

    #取出队头元素
    movl 8(%ebx), %ecx
    movl 16(%ebx), %eax
    movl (%eax, %ecx, 4), %edx
    #设置传出参数
    movl 8(%esp), %eax
    movl %edx, (%eax)
    #队头向前到达最大容积归零
    incl %ecx
    cmpl %ecx, (%ebx)
    jne 2f
    movl $0, %ecx
2:
    movl %ecx, 8(%ebx)
    #长度减1
    decl 4(%ebx)
    movl $0, %eax

1:
    ret

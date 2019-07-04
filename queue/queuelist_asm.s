.global _queuelist_init_asm, _queuelist_destroy_asm, _queuelist_empty, _queuelist_enter_asm, _queuelist_delete_asm

_node_size:
    .int 8

_queuelist_size:
    .int 8

#构建队列结构
_queuelist_init_asm:
    pushl _queuelist_size
    call _malloc
    movl $0, (%eax)
    movl $0, 4(%eax)
    addl $4, %esp
    ret

#队列销毁
_queuelist_destroy_asm:
    cmpl $0, 4(%esp)
    je 1f

    pushl %ebp
    movl %esp, %ebp

    #
    subl $8, %esp
    #循环队列变量用esp + 4
    movl 8(%ebp), %eax
    movl (%eax), %eax
    movl %eax, 4(%esp)
    jmp 2f

3:
    movl 4(%esp), %eax
    movl (%eax), %edx
    movl %edx, 4(%esp)
    movl %eax, (%esp)
    call _free

2:
    cmpl $0, 4(%esp)
    jne 3b

    movl 8(%ebp), %eax
    movl %eax, (%esp)
    call _free

    leave
1:
    ret

#判断队列是否为空
_queuelist_empty_asm:
    movl $-1, %eax
    cmpl $0, 4(%esp)
    je 1f

    movl 4(%esp), %edx
    cmpl $0, (%edx)
    jne 1f
    movl $0, %eax

1:
    ret

#入队操作
_queuelist_enter_asm:
    movl $-1, %eax
    cmpl $0, 4(%esp)
    je 1f

    pushl %ebp
    movl %esp, %ebp

    #为元素分配内存
    pushl _node_size
    call _malloc
    movl 12(%ebp), %edx
    movl %edx, 4(%eax)
    movl $0, (%eax)

    #队列使用ebx
    movl 8(%ebp), %ebx
    #原队尾不为空，设置本元素后继为原队尾
    cmpl $0, 4(%ebx)
    je 2f
    movl 4(%ebx), %edx
    movl %eax, (%edx)

2:
    #设置新元素为队头
    movl %eax, 4(%ebx)

    #判断队头是否为空，为空设置队头为新元素
    cmpl $0, (%ebx)
    jne 3f
    movl %eax, (%ebx)

3:
    movl $0, %eax

    leave
1:
    ret

#出队操作
_queuelist_delete_asm:
    movl $-1, %eax
    cmpl $0, 4(%esp)
    je 1f

    pushl %ebp
    movl %esp, %ebp
    #队列使用ebx寄存器
    movl 8(%ebp), %ebx
    #判断队列是否为空
    cmpl $0, (%ebx)
    je 2f

    #不为空传出数据重新设置队头
    movl 12(%ebp), %esi
    movl (%ebx), %eax
    movl 4(%eax), %edx
    movl %edx, (%esi)
    movl (%eax), %edx
    movl %edx, (%ebx)
    pushl %eax
    call _free
    movl $0, %eax

2:
    leave
1:
    ret

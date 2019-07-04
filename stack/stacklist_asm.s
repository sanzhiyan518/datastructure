.section .text
.global _stacklist_init_asm, _stacklist_destroy_asm, _stacklist_push_asm, _stacklist_pop_asm, _stacklist_empty_asm

_node_size:
    .int 8

#create stack
_stacklist_init_asm:
    pushl _node_size
    call _malloc
    movl $0, (%eax)
    addl $4, %esp
    ret

#destroy stack
_stacklist_destroy_asm:
    #判断栈是否为空
    cmpl $0, 4(%esp)
    je 1f

    #开栈
    pushl %ebp
    movl %esp, %ebp
    subl $8, %esp
    #循环变量使用esp+4
    movl 8(%ebp), %ebx
    movl (%ebx), %eax
    movl %eax, 4(%esp)
    jmp 2f

3:
    #释放单链表元素内存
    #循环变量继续
    movl 4(%esp), %eax
    movl (%eax), %edx
    movl %edx, 4(%esp)
    movl %eax, (%esp)
    call _free

2:
    #判断是否结束
    cmpl $0, 4(%esp)
    jne 3b

    #释放栈内存
    movl 8(%ebp), %eax
    movl %eax, (%esp)
    call _free

    leave
1:
    ret

#push operation
_stacklist_push_asm:
    cmpl $0, 4(%esp)
    jne 1f
    movl $-1, %eax
    jmp 2f

1:
    #为元素分配内存链入栈结构
    pushl _node_size
    call _malloc
    #
    movl 8(%esp), %ebx
    movl 12(%esp), %edx
    movl %edx, 4(%eax)
    movl (%ebx), %edx
    movl %edx, (%eax)
    movl %eax, (%ebx)
    movl $0, %eax
    addl $4, %esp

2:
    ret

#pop operation
_stacklist_pop_asm:
    cmpl $0, 4(%esp)
    jne 1f
    movl $-1, %eax
    jmp 2f

1:
    #断开栈顶元素
    movl 4(%esp), %ebx
    movl (%ebx), %eax
    cmpl $0, %eax
    jne 3f

    movl $-1, %eax
    jmp 2f

3:
    movl (%eax), %edx
    movl %edx, (%ebx)

    #传出元素卫星
    movl 8(%esp), %edx
    movl 4(%eax), %ecx
    movl %ecx, (%edx)
    #释放元素内存
    pushl %eax
    call _free
    movl $0, %eax
    addl $4, %esp

2:
    ret

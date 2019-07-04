.text
.global _stack_init_asm, _stack_destroy_asm, _stack_push_asm, _stack_pop_asm, _stack_empty_asm

_stack_size:
    .int 12

_void_size:
    .int 4

#栈初始化
_stack_init_asm:
    subl $4, %esp

    #为栈分配内存
    pushl _stack_size;
    call _malloc
    #栈使用esp+4保存
    movl %eax, 4(%esp)
    #设置栈深
    movl 12(%esp), %edx
    movl %edx, (%eax)
    #设置栈顶
    movl $-1, %ecx
    movl %ecx, 4(%eax)

    #计算元素指针数组大小
    movl _void_size, %eax
    mull %edx
    #为数组分配内存
    movl %eax, (%esp)
    call _malloc
    movl %eax, %edx
    movl 4(%esp), %eax
    movl %edx, 8(%eax)
    addl $8, %esp
    ret

#栈销毁
_stack_destroy_asm:
    #判断栈是否为空
    cmpl $0, 4(%esp)
    je 1f

    #数组内存释放
    movl 4(%esp), %eax
    pushl 8(%eax)
    call _free;
    #栈内存释放
    pushl 8(%esp)
    call _free

    #恢复栈
    addl $8, %esp
1:
    ret

#压入操作
_stack_push_asm:
    cmpl $0, 4(%esp)
    jne 2f
    movl $-1, %eax
    jmp 1f

2:
    #栈直接使用ebx寄存器
    movl 4(%esp), %ebx
    #取出栈顶
    movl 4(%ebx), %ecx
    #自增
    incl %ecx
    #与栈深比较大于等于栈深退出
    cmpl (%ebx), %ecx
    jl 3f
    movl -1, %eax
    jmp 1f

3:
    #数据数组直接使用eax寄存器
    movl 8(%ebx), %eax
    #压入数据
    movl %ecx, 4(%ebx)
    movl 8(%esp), %edx
    movl %edx, (%eax, %ecx, 4)
    movl $0, %eax

1:
    ret

#弹出操作
_stack_pop_asm:
    cmpl $0, 4(%esp)
    jne 1f
    movl $-1, %eax
    jmp 2f

1:
    #栈使用ebx寄存器
    movl 4(%esp), %ebx
    #获取栈顶使用ecx寄存器
    movl 4(%ebx), %ecx
    #比较栈顶是否超过栈底
    cmpl $-1, %ecx
    jne 3f
    movl $-1, %eax
    jmp 2f

3:
    #弹出数据
    movl 8(%ebx), %eax
    movl (%eax, %ecx, 4), %edx
    #重新设置栈顶
    decl %ecx
    movl %ecx, 4(%ebx)
    #传入参数
    movl 8(%esp), %eax
    movl %edx, (%eax)
    movl $0, %eax


2:
    ret

.global _list_init_asm, _list_destroy_asm, _list_insert_asm, _list_search_asm, _list_delete_asm

list_size:
    .int 16
list_element_size:
    .int 8

#链表构建
_list_init_asm:
    sub $4, %esp
    #分配链表结构体内存
    movl list_size, %eax
    movl %eax, (%esp)
    call _malloc

    #设置结构体成员
    #长度
    movl $0, (%eax)
    #头、尾
    movl $0, 4(%eax)
    movl $0, 8(%eax)
    movl 8(%esp), %ebx
    movl %ebx, 12(%eax)

    add $4, %esp
    ret

#链表销毁
_list_destroy_asm:
    #保存寄存器
    sub $4, %esp

    #遍历链表的元素使用%ebx
    movl 8(%esp), %ebx
    #movl %ebp, %ebx
    movl 4(%ebx), %ebx

    jmp 1f

2:
    #临时变量
    movl %ebx, %ecx
    #修改元素指向下一个元素
    movl 4(%ebx), %ebx
    #释放内存
    movl %ecx, (%esp)
    call _free

1:
    cmpl $0, %ebx
    jnz 2b

    #释放链表占用内存
    movl 8(%esp), %eax
    movl %eax, (%esp)
    call _free

    addl $4, %esp
    ret

#插入操作，构建新的链表元素，并将此链表元素插入到传入链表元素参数之后，可以为空
_list_insert_asm:
    subl $4, %esp
    #判断传入链表是否为空
    cmpl $0, 8(%esp)
    jz 1f

    #为新的链表元素分配内存
    movl $8, (%esp)
    call _malloc
    movl 16(%esp), %ecx
    movl %ecx, (%eax)

    #链表指针使用ebx寄存器
    movl 8(%esp), %ebx
    #传入链表元素使用%ecx寄存器
    movl 12(%esp), %ecx

    #判断是否传入链表元素
    cmpl $0, %ecx
    jnz 2f
    #未传入链表元素，则将新链表元素做为链表头
    #判断链表是否空，空则新元素也是链表尾
    cmpl $0, (%ebx)
    jnz 3f
    movl %eax, 8(%ebx)
3:
    movl 4(%ebx), %edx
    movl %edx, 4(%eax)
    movl %eax, 4(%ebx)
    jmp 5f

2:
    #传入了链表元素
    #传入链表元素是否为尾
    cmpl 8(%ebx), %ecx
    jne 4f
    movl %eax, 8(%ebx)
4:
    movl 4(%ecx), %edx
    movl %edx, 4(%eax)
    movl %eax, 4(%ecx)

5:
    incl (%ebx)
1:
    addl $4, %esp
    ret

#根据传入卫星数据，搜索链表元素
_list_search_asm:
    #判断链表是否为空
    subl $16, %esp

    movl 20(%esp), %eax
    cmpl $0, %eax
    jz 1f

    #元素比较函数使用esp+8
    movl 12(%eax), %edx
    movl %edx, 8(%esp)
    #链表搜索元素使用esp+12
    movl 4(%eax), %edx
    movl %edx, 12(%esp)
    #传入卫星数据直接压栈
    movl 24(%esp), %eax
    movl %eax, (%esp)
    jmp 2f

3:
    #比较元素
    movl 12(%esp), %eax
    movl (%eax), %eax
    movl %eax, 4(%esp)
    movl 8(%esp), %edx
    call *%edx
    cmpl $0, %eax
    #不相等继续
    je 4f
    #相等设置返回值退出
    movl 12(%esp), %eax
    jmp 1f
4:
    movl 12(%esp), %eax
    movl 4(%eax), %eax
    movl %eax, 12(%esp)

2:
    cmpl $0, 12(%esp)
    jne 3b

1:
    addl $16, %esp
    ret

_list_delete_asm:
    pushl %ebp
    movl %esp, %ebp
    subl $24, %esp

    #判断链表是否为空
    movl 8(%ebp), %eax
    cmpl $0, %eax
    je 1f

    #元素比较函数使用%esp+8
    movl 12(%eax), %edx
    movl %edx, 8(%esp)
    #遍历元素使用esp + 12
    movl 4(%eax), %edx
    movl %edx, 12(%esp)
    #前驱元素使用esp + 16
    xorl %edx, %edx
    movl %edx, 16(%esp)
    #将待删除元素压栈
    movl 12(%ebp), %eax
    movl %eax, (%esp)
    jmp 2f

3:
    #取出遍历元素卫星数据调用比较函数
    movl 12(%esp), %eax
    movl (%eax), %eax
    movl %eax, 4(%esp)
    movl 8(%esp), %edx
    call *%edx
    #不相同下一个元素
    cmpl $1, %eax
    jne 4f
    #相同开始删除元素,得到此元素的后继元素
    movl 12(%esp), %eax
    movl 4(%eax), %edx

    #链表
    movl 8(%ebp), %ebx
    #前驱元素
    movl 16(%esp), %ecx

    #根据前驱元素是否为空处理
    cmpl $0, %ecx
    jne 5f

    #没有前驱元素表明此元素为头修改链表头
    movl %edx, 4(%ebx)
    jmp 6f

5:
    #有前驱元素,修改前驱的下一个元素
    movl %edx, 4(%ecx)

6:
    #检查元素是否尾，为尾修改尾
    cmpl 8(%ebx), %eax
    jne 7f
    #修改链表尾为前驱元素
    movl %ecx, 8(%ebx)

7:
    #释放元素
    movl %eax, (%esp)
    call _free
    #链表数据减1
    decl (%ebx)
    jmp 1f

4:
    #不相同
    movl 12(%esp), %eax
    #修改前驱元素
    movl %eax, 16(%esp)
    #下一个元素
    movl 4(%eax), %eax
    movl %eax, 12(%esp)

2:
    cmpl $0, 12(%esp)
    jne 3b

1:
    addl $24, %esp
    leave
    ret

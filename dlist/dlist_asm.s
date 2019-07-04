.global _dlist_init_asm, _dlist_destroy_asm, _dlist_insert_asm, _dlist_search_asm, _dlist_delete_asm

dlist_size:
    .int 16
dlist_element_size:
    .int 12

#链表构建
_dlist_init_asm:
    subl $4, %esp

    #分配内存
    movl dlist_size, %eax
    movl %eax, (%esp)
    call _malloc
    #eax为返回值
    movl $0, (%eax)
    movl $0, 4(%eax)
    movl $0, 8(%eax)
    movl 8(%esp), %edx
    movl %edx, 12(%eax)

    addl $4, %esp

    ret

#链表销毁
_dlist_destroy_asm:
    push %ebp
    movl %esp, %ebp
    subl $16, %esp

    #遍历元素使用esp + 4
    movl 8(%ebp), %eax
    cmpl $0, %eax
    je 1f

    movl 4(%eax), %eax
    movl %eax, 4(%esp)
    jmp 2f

3:
    #临时变量用edx
    movl 4(%esp), %edx
    #循环改为后继元素
    movl 8(%edx), %eax
    movl %eax, 4(%esp)
    #释放元素所占内存
    movl %edx, (%esp)
    call _free

2:
    cmpl $0, 4(%esp)
    jne 3b

    mov 8(%ebp), %eax
    movl %eax, (%esp)
    call _free

1:
    leave
    ret

#链表插入元素
_dlist_insert_asm:
    #
    subl $4, %esp
    #判断传入链表是否为空
    cmpl $0, 8(%esp)
    je 1f

    #新建元素分配内存
    movl dlist_element_size, %eax
    movl %eax, (%esp)
    call _malloc
    #新建元素使用eax寄存器,设置初始值
    movl 16(%esp), %edx
    movl %edx, (%eax)
    movl $0, 4(%eax)
    movl $0, 8(%eax)

    #前驱元素使用ecx寄存器
    movl 12(%esp), %ecx
    #链表使用ebx寄存器
    movl 8(%esp), %ebx

    #根据是否传入前驱元素进行处理
    cmpl $0, %ecx
    je 2f

    #前驱元素不为空
    #判断前驱元素是否为尾，为尾则修改链尾为新元素
    cmpl %ecx, 8(%ebx)
    je 3f

    #不为尾，修改元素间链接关系
    #原前驱的后继的前驱改为新元素
    movl 8(%ecx), %edx
    movl %eax, 4(%edx)
    jmp 4f

3:
    #前驱为尾修改链表尾为新元素
    movl %eax, 8(%ebx)

4:
    #加入链
    #前驱的后继改为新元素的后继
    movl 8(%ecx), %edx
    movl %edx, 8(%eax)
    #新元素的前驱修改
    movl %ecx, 4(%eax)
    #前驱的后继改为新元素
    movl %eax, 8(%ecx)
    jmp 5f

2:
    #传入前驱元素为空
    #判断链表长度是否为空，为空则设置新元素为尾
    cmpl $0, (%ebx)
    jne 6f
    #链表为空
    movl %eax, 8(%ebx)
6:
    #新元素为链表头
    #新元素的后继为旧头
    movl 4(%ebx), %edx
    movl %edx, 8(%eax)

    #判断旧头是否为空
    cmpl $0, %edx
    je 7f
    #不为空则旧头前驱为新元素
    movl %eax, 4(%edx)
7:
    #改链表头为新元素
    movl %eax, 4(%ebx)

5:
    #增加链表长度
    incl (%ebx)

1:
    addl $4, %esp
    ret

_dlist_search_asm:
    push %ebp
    movl %esp, %ebp
    subl $16, %esp

    #判断链表是否为空
    cmpl $0, 8(%ebp)
    jne 2f
    #为空返回
    xorl %eax, %eax
    jmp 1f

2:
    #遍历元素使用esp + 8
    movl 8(%ebp), %eax
    movl 4(%eax), %edx
    movl %edx, 8(%esp)
    #比较函数使用esp + 12
    movl 12(%eax), %edx
    movl %edx, 12(%esp)
    #比较卫星数据提前压栈
    movl 12(%ebp), %eax
    movl %eax, (%esp)

    jmp 3f

4:
    #取出卫星数据，压栈调用比较函数
    movl 8(%esp), %eax
    movl (%eax), %eax
    movl %eax, 4(%esp)
    #
    movl 12(%esp), %eax
    call *%eax
    #
    cmpl $1, %eax
    jne 5f

    #相等，设置返回值退出
    movl 8(%esp), %eax
    #不相等继续
    jmp 1f
5:
    #继续搜索
    movl 8(%esp), %eax
    movl 8(%eax), %eax
    movl %eax, 8(%esp)

3:
    cmpl $0, 8(%esp)
    jne 4b

    #未发现设置空
    xorl %eax, %eax

1:
    leave
    ret

#删除操作，删除与传入卫星数据相等的链表元素
_dlist_delete_asm:
    push %ebp
    movl %esp, %ebp
    subl $8, %esp
    #调用搜索函数
    movl 8(%ebp), %eax
    movl %eax, (%esp)
    movl 12(%ebp), %eax
    movl %eax, 4(%esp)
    call _dlist_search_asm
    #搜索到的链表元素直接使用eax寄存器
    #比较是否搜到
    cmpl $0, %eax
    #未搜到退出
    je 1f

    #前驱元素使用ecx寄存器
    movl 4(%eax), %ecx
    #后继元素使用edx寄存器
    movl 8(%eax), %edx
    #链表使用ebx寄存器
    movl (%esp), %ebx

    #判断前驱是否空
    cmpl $0, %ecx
    je 2f
    #非空设置前驱的后继为后继元素
    movl %edx, 8(%ecx)
    jmp 3f
2:
    #空则设置链表头
    movl %edx, 4(%ebx)

3:
    #判断元素是否为链表尾
    cmpl %eax, 8(%ebx)
    je 4f

    #不是链表尾，则设置后继的前驱为前驱
    movl %ecx, 4(%edx)
    jmp 5f
4:
    #链表尾，则设置链表尾为前驱
    movl %ecx, 8(%ebx)

5:
    #链表元素数减1
    decl (%ebx)
    #释放元素
    movl %eax, (%esp)
    call _free

1:
    leave
    ret

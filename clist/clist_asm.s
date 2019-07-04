
.section .data
_t:
    .byte 0x25,0x64,0x2E,0x00
_msg:
    .ascii "%d.\n";

clist_size:
    .int 12

clist_element_size:
    .int 12

pointer_size:
    .int 4

offset_head:
offset_prev:
    .int 4

offset_compare:
offset_next:
    .int 8

.section .text
.global _test, _clist_init_asm, _clist_destroy_asm, _clist_insert_asm, _clist_search_asm, _clist_delete_asm
ok:
    pushl %ebp
    movl %esp, %ebp
    leave
    ret

_test:
    pushl %ebp
    movl %esp, %ebp
    subl $8, %esp
    movl $_t, %eax
    movl %eax, (%esp)
    movl $2, 4(%esp)
    call _printf
    call ok
    leave
    movl $_tt, %eax
    pushl %eax
    ret

#构建链表
_clist_init_asm:
    #
    pushl $12
    call _malloc

    #链表内存在eax寄存器中，设置初始值
    movl $0, (%eax)
    movl $0, 4(%eax)
    movl 8(%esp), %edx
    movl %edx, 8(%eax)

    addl $4, %esp
    ret

#销毁链表
_clist_destroy_asm:
    #
    pushl %ebp
    movl %esp, %ebp
    subl $16, %esp

    movl 8(%ebp), %eax

    #传入链表是否空
    cmpl $0, %eax
    #为空直接返回
    je 1f
    #链表长度为空
    cmpl $0, (%eax)
    je 3f

    #循环变量使用esp + 4

    movl 4(%eax), %eax
    movl %eax, 4(%esp)
    #链表头使用esp + 8
    movl %eax, 8(%esp)

2:
    #取出后继元素
    movl 4(%esp), %eax
    movl 8(%eax), %edx
    #设置回变量
    movl %edx, 4(%esp)
    movl %eax, (%esp)
    #释放元素内存
    call _free

    #比较是否循环回到头
    movl 4(%esp), %eax
    cmpl %eax, 8(%esp)
    jne 2b

3:
    #释放链表内存
    movl 8(%ebp), %eax
    movl %eax, (%esp)
    call _free

1:
    addl $16, (%esp)
    leave
    ret

#插入元素
_clist_insert_asm:
    pushl %ebp
    movl %esp, %ebp

    #判断链表是否为空
    cmpl $0, 8(%ebp)
    je 1f

    subl $16, %esp
    #分配元素内存
    movl clist_element_size, %eax
    movl %eax, (%esp)
    call _malloc
    #新元素内存使用eax,设置初始值
    movl 16(%ebp), %edx
    movl %edx, (%eax)
    movl %eax, 4(%eax)
    movl %eax, 8(%eax)

    #判断前驱是否为空
    cmpl $0, 12(%ebp)
    jne 4f

    #链表使用%ebx
    movl 8(%ebp), %ebx
    #前驱为空分情况处理
    #先得到链表头
    movl 4(%ebx), %edi
    #使用新元素设置头
    movl %eax, 4(%ebx)
    #比较原头是否为空
    cmpl $0, %edi
    #原头为空直接长度增1结束
    je 3f
    #设置前驱元素为原头的前驱
    movl 4(%edi), %ecx
    jmp 2f

4:
    #前驱使用%ecx
    movl 12(%ebp), %ecx

2:
    #修改后继的前驱
    movl 8(%ecx), %edi
    movl %eax, 4(%edi)
    #修改新元素的后继与前驱
    movl %edi, 8(%eax)
    movl %ecx, 4(%eax)
    #修改前驱的后继
    movl %eax, 8(%ecx)

3:
    #长度增1
    incl (%ebx)
1:
    addl $16, %esp
    leave
    ret

#搜索元素
_clist_search_asm:
    pushl %ebp
    movl %esp, %ebp

    movl 8(%ebp), %eax
    #比较是否为空链表
    cmpl $0, %eax
    je 1f

    subl $24, %esp
    #循环元素使用esp+8
    movl 4(%eax), %edx
    movl %edx, 8(%esp)
    #链表头使用esp + 12
    movl %edx, 12(%esp)
    #比较函数使用esp + 16
    movl 8(%eax), %edx
    movl %edx, 16(%esp)
    #比较卫星数据压栈
    movl 12(%ebp), %eax
    movl %eax, (%esp)

2:
    #取出循环元素中值调用比较函数
    movl 8(%esp), %eax
    movl (%eax), %eax
    movl %eax, 4(%esp)
    movl 16(%esp), %eax
    call *%eax

    #相等返回零
    cmpl $0, %eax
    jne 3f
    movl 8(%esp), %eax
    jmp 4f

3:
    #不相等循环下一个
    movl 8(%esp), %eax
    movl 8(%eax), %eax
    #判断是否结束
    cmpl %eax, 12(%esp)
    #结束设置返回值为空，返回
    jne 5f
    xorl $0, %eax
    jmp 4f

5:
    movl %eax, 8(%esp)
    jmp 2b

4:
    addl $24, %esp

1:
    leave
    ret

#删除元素
_clist_delete_asm:
    pushl %ebp
    movl %esp, %ebp

    subl $8, %esp

    #调用元素搜索函数
    movl 8(%ebp), %eax
    movl %eax, (%esp)
    movl 12(%ebp), %eax
    movl %eax, 4(%esp)
    call _clist_search_asm
    #搜索失败返回
    cmpl $0, %eax
    je 1f

    #前驱使用ecx
    movl 4(%eax), %ecx
    #链表使用ebx
    movl 8(%ebp), %ebx
    #后继使用edx
    movl 8(%eax), %edx

    #判断是否只有一个元素
    cmpl %ecx, %eax
    jne 2f
    #只有一个设置链表头为空
    movl $0, 4(%ebx)
    jmp 3f
2:
    #修改后继的前驱为前驱
    movl %ecx, 4(%edx)
    #修改前驱的后继为后继
    movl %edx, 8(%ecx)
    #判断元素是否为头修改头
    cmpl %eax, 4(%ebx)
    jne 3f
    movl %edx, 4(%ebx)

3:
    #释放内存
    movl %eax, (%esp)
    call _free
    #长度减1
    decl (%ebx)

1:
    addl $8, %esp
    leave
    ret

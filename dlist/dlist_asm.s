.global dlist_init_asm, dlist_destroy_asm, dlist_ins_next_asm, dlist_ins_prev_asm, dlist_remove_asm

#链表初始化
dlist_init_asm:
    #链表参数rdi传入
    #设置长度
    movq $0, (%rdi)
    #设置比较函数
    movq $0, 8(%rdi)
    #设置数据成员销毁函数,函数指针由rsi传入
    movq %rsi, 16(%rdi)
    #设置链表头、尾
    movq $0, 24(%rdi)
    movq $0, 32(%rdi)
    ret


#链表销毁
dlist_destroy_asm:
    #开栈
    push %rbp
    movq %rsp, %rbp
    subq $24, %rsp

    #链表参数由rdi传入,将其存入rsp+16,以备后用
    movq %rdi, 16(%rsp)
    #取出链表头为遍历元素使用rsp
    movq 24(%rdi), %rax
    movq %rax, (%rsp)
    #元素销毁函数使用rsp+8
    movq 16(%rdi), %rax
    movq %rax, 8(%rsp)

    #循环遍历链表
    jmp 1f

2:
   #取出遍历元素
   movq (%rsp), %rdx
   #判断元素销毁函数是否为空
   cmpq $0, 8(%rsp)
   je 3f
   #不为空,调用元素销毁函数
   movq 8(%rsp), %rax
   movq (%rdx), %rdi
   call *%rax
3:
    #释放元素内存
    movq (%rsp), %rdi
    call free
    #将遍历元素修改为后继元素
    movq (%rsp), %rax
    movq 16(%rax), %rax
    movq %rax, (%rsp)

 1:
    #判断遍历链表结束
    cmpq $0, (%rsp)
    jne 2b

    #链表清零
    #链表参数为第1个参数
    movq 16(%rsp), %rdi
    #0为第2个参数
    movl $0, %esi
    #链表结构体为第3个参数
    movl $40, %edx
    call memset
    leave
    ret

#链表元素后插入新元素
dlist_ins_next_asm:
    #链表参数存于rdi
    #前驱元素存于rsi
    #数据成员存于rdx

    #判断前驱元素是否空
    cmpq $0, %rsi
    jne 1f
    #判断链表长度是否为零，前驱为空且链表长度不空则返回-1
    cmpq $0, (%rdi)
    je 1f
    movq $-1, %rax
    ret

1:
    #将参数入栈，调用其它函数后可能传入参数的寄存器会发生变化
    pushq %rdx
    pushq %rsi
    pushq %rdi

    #为新元素分配内存,返回在rax
    movq $24, %rdi
    call malloc

    #参数出线
    popq %rdi
    popq %rsi
    popq %rdx

    #判断内存分配是否成功
    cmpq $0, %rax
    jne 2f
    movq $-1, %rax
    ret

2:
    #设置数据成员
    movq %rdx, (%rax)

    cmpq $0, %rsi
    jne 3f
    #如果前驱元素为空（链表长度为零），新元素为链表的头、尾
    movq $0, 8(%rax)
    movq $0, 16(%rax)
    movq %rax, 24(%rdi)
    movq %rax, 32(%rdi)
    jmp 4f

3:
    #己传入前驱元素，则与前驱链接
    movq 16(%rsi), %rcx
    movq %rcx, 16(%rax)
    movq %rsi, 8(%rax)

    #判断前驱元素是否为链表尾，是则新元素设置为链表尾
    cmpq  $0,16(%rsi)
    jne 5f
    #设置为链表尾
    movq %rax, 32(%rdi)
    jmp 6f
5:
    #修改前驱的后继元素的前驱为新元素
    movq 16(%rsi), %rcx
    movq %rax, 8(%rcx)
6:
    #前驱的后继为新元素
    movq %rax, 16(%rsi)

4:
    #链表长度增加
    incq (%rdi)
    movq $0, %rax
    ret

#链表元素前插入新元素
dlist_ins_prev_asm:
    #链表参数存于rdi
    #后继元素存于rsi
    #数据成员存于rdx

    #判断后继元素是否空
    cmpq $0, %rsi
    jne 1f
    #判断链表长度是否为零，后继为空且链表长度不空则返回-1
    cmpq $0, (%rdi)
    je 1f
    movq $-1, %rax
    ret

1:
    #将参数入栈，调用其它函数后可能传入参数的寄存器会发生变化
    pushq %rdx
    pushq %rsi
    pushq %rdi

    #为新元素分配内存,返回在rax
    movq $24, %rdi
    call malloc

    #参数出线
    popq %rdi
    popq %rsi
    popq %rdx

    #判断内存分配是否成功
    cmpq $0, %rax
    jne 2f
    movq $-1, %rax
    ret

2:
    #设置数据成员
    movq %rdx, (%rax)

    cmpq $0, %rsi
    jne 3f
    #如果后继元素为空（链表长度为零），新元素为链表的头、尾
    movq $0, 8(%rax)
    movq $0, 16(%rax)
    movq %rax, 24(%rdi)
    movq %rax, 32(%rdi)
    jmp 4f

3:
    #己传入后继元素，则与后继链接
    #后断元素的前驱为新元素的前驱
    movq 8(%rsi), %rcx
    movq %rcx, 8(%rax)
    #新元素的后继为传入后继元素
    movq %rsi, 16(%rax)

    #判断后继元素是否为链表头，是则新元素设置为链表头
    cmpq  $0, 8(%rsi)
    jne 5f
    #设置为链表头
    movq %rax, 24(%rdi)
    jmp 6f
5:
    #修改后继元素的前驱的后继为新元素
    movq 8(%rsi), %rcx
    movq %rax, 16(%rcx)
6:
    #后继元素的前驱为新元素
    movq %rax, 8(%rsi)

4:
    #链表长度增加
    incq (%rdi)
    movq $0, %rax
    ret

#删除元素
dlist_remove_asm:
    #链表参数在rdi
    #删除元素在rsi
    #数据传出指针在rdx

    movq $-1, %rax
    #判断删除元素是否为空
    cmpq $0, %rsi
    jne 1f
    ret
1:
    #判断链表长度是否为零
    cmpq $0, (%rdi)
    jne 2f
    ret

2:
    #取出元素的前驱与后继
    movq 8(%rsi), %rax
    movq 16(%rsi), %rcx

    #判断元素是否为链表头（前驱为空）
    cmpq $0,  %rax
    jne 3f
    #修改链表头为元素的后继
    movq %rcx, 24(%rdi)
    jmp 4f
3:
    #元素不为链表头，则修改元素的前驱的后继为元素的后继元素
    movq %rcx, 16(%rax)

4:
    #判断元素是否为链表尾（后继为空）
    cmpq $0, %rcx
    jne 5f
    #修改链表尾为元素的前驱
    movq %rax, 32(%rdi)
    jmp 6f
5:
    #元素不为链表尾，则修改元素后继的前驱为元素的前驱元素
    movq %rax, 8(%rcx)

6:
    #链表长度减1
    decl (%rdi)
    #传出数据成员
    movq (%rsi), %rcx
    movq %rcx, (%rdx)
    #释放元素内存
    movq %rsi, %rdi
    call free
    movq $0, %rax
    ret

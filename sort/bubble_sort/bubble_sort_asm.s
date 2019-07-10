.global _bubble_sort_asm

_bubble_sort_asm:
    #保存寄存器
    pusha

    #直接使用ebx访问元素首地址
    movl 36(%esp), %ebx
    #循环变量i直接使用ecx
    #取出元素长度
    movl 40(%esp), %ecx
    #减1
    decl %ecx
    #末端
    leal (%ebx, %ecx, 4), %ecx

    jmp 1f

6:
    #交换标志exchangeFlag直接使用eax,置0
    xorl %eax, %eax

    #循环变量j直接使用edx，置0，循环至i
    movl %ebx, %edx

3:
    cmpl %ecx, %edx
    #大于时跳出此次循环
    jg 4f

    #取出相邻元素，判断是否交换
    movl (%edx), %esi
    cmpl 4(%edx), %esi
    jle 5f
    #交换
    xchgl %esi, 4(%edx)
    movl %esi, (%edx)
    movl $1, %eax

5:
    #j自增
    addl $4, %edx
    jmp 3b

4:
    #判断交换标志是否置1,没有则退出调用
    cmpl $0, %eax
    je 2f
    #i自减
    subl $4, %ecx

1:
    #循环i变量至0，判断
    cmpl %ebx, %ecx
    #若小于0退出调用
    jge 6b

2:
    #恢复寄存器
    popa
    ret

.global _selection_sort_asm

_selection_sort_asm:
    #保存栈位置信息及开栈
    pushl %ebp
    movl %esp, %ebp
    subl $12, %esp

    #局部变量i使用ebp-4
    xorl %eax, %eax
    movl %eax, -4(%ebp)
    #定义局部变量len位于直接使用edi寄存器
    movl 12(%ebp), %edi
    decl %edi
    #取出数组基址使用ebx寄存器
    movl 8(%ebp), %ebx

1:
    #比较i变量是否小于变量len1
    cmpl %edi, -4(%ebp)
    #大于等于结束
    jae 2f

    #使用i值初始化最小值索引变量minIndex直接使用esi寄存器
    movl -4(%ebp), %esi

    #使用i+1初始化局部变量j直接使用ecx寄存器
    movl %esi, %ecx
    incl %ecx

3:
    #比较变量j值是否小于len
    cmpl %edi, %ecx
    #大于等于跳至下一步选择排序
    ja 4f

    #取出索引j值,使用基址加变址索引寻址方式
    #设置索引寄存器值
    movl (%ebx, %ecx, 4), %edx

    #比较索引j值与最小索引minIndex值
    cmpl (%ebx, %esi, 4), %edx
    #大于等于跳至下次循环
    jge 5f
    #使用j替换minIndex
    movl %ecx, %esi

5:
    #局部变量j自增
    incl %ecx
    jmp 3b

4:
    #判断i与minIndex是否相等
    cmpl -4(%ebp), %esi
    #相等则略过
    jz 6f
    #交换i值与minIndex索引值
    #minIndex值
    movl (%ebx, %esi, 4), %edx
    #形成i索引值
    movl -4(%ebp), %eax
    xchgl %edx, (%ebx, %eax, 4)
    movl %edx, (%ebx, %esi, 4)

6:
    #局部变量i自增
    incl -4(%ebp)
    #跳至下一次选择排序
    jmp 1b

2:
    #恢复栈
    movl %ebp, %esp
    popl %ebp
    ret

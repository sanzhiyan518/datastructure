.global _list_init_asm, _list_destroy_asm, _list_insert_asm, _list_search_asm, _list_delete_asm

list_size:
    .int 16
list_element_size:
    .int 8

#������
_list_init_asm:
    sub $4, %esp
    #��������ṹ���ڴ�
    movl list_size, %eax
    movl %eax, (%esp)
    call _malloc

    #���ýṹ���Ա
    #����
    movl $0, (%eax)
    #ͷ��β
    movl $0, 4(%eax)
    movl $0, 8(%eax)
    movl 8(%esp), %ebx
    movl %ebx, 12(%eax)

    add $4, %esp
    ret

#��������
_list_destroy_asm:
    #����Ĵ���
    sub $4, %esp

    #���������Ԫ��ʹ��%ebx
    movl 8(%esp), %ebx
    #movl %ebp, %ebx
    movl 4(%ebx), %ebx

    jmp 1f

2:
    #��ʱ����
    movl %ebx, %ecx
    #�޸�Ԫ��ָ����һ��Ԫ��
    movl 4(%ebx), %ebx
    #�ͷ��ڴ�
    movl %ecx, (%esp)
    call _free

1:
    cmpl $0, %ebx
    jnz 2b

    #�ͷ�����ռ���ڴ�
    movl 8(%esp), %eax
    movl %eax, (%esp)
    call _free

    addl $4, %esp
    ret

#��������������µ�����Ԫ�أ�����������Ԫ�ز��뵽��������Ԫ�ز���֮�󣬿���Ϊ��
_list_insert_asm:
    subl $4, %esp
    #�жϴ��������Ƿ�Ϊ��
    cmpl $0, 8(%esp)
    jz 1f

    #Ϊ�µ�����Ԫ�ط����ڴ�
    movl $8, (%esp)
    call _malloc
    movl 16(%esp), %ecx
    movl %ecx, (%eax)

    #����ָ��ʹ��ebx�Ĵ���
    movl 8(%esp), %ebx
    #��������Ԫ��ʹ��%ecx�Ĵ���
    movl 12(%esp), %ecx

    #�ж��Ƿ�������Ԫ��
    cmpl $0, %ecx
    jnz 2f
    #δ��������Ԫ�أ���������Ԫ����Ϊ����ͷ
    #�ж������Ƿ�գ�������Ԫ��Ҳ������β
    cmpl $0, (%ebx)
    jnz 3f
    movl %eax, 8(%ebx)
3:
    movl 4(%ebx), %edx
    movl %edx, 4(%eax)
    movl %eax, 4(%ebx)
    jmp 5f

2:
    #����������Ԫ��
    #��������Ԫ���Ƿ�Ϊβ
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

#���ݴ����������ݣ���������Ԫ��
_list_search_asm:
    #�ж������Ƿ�Ϊ��
    subl $16, %esp

    movl 20(%esp), %eax
    cmpl $0, %eax
    jz 1f

    #Ԫ�رȽϺ���ʹ��esp+8
    movl 12(%eax), %edx
    movl %edx, 8(%esp)
    #��������Ԫ��ʹ��esp+12
    movl 4(%eax), %edx
    movl %edx, 12(%esp)
    #������������ֱ��ѹջ
    movl 24(%esp), %eax
    movl %eax, (%esp)
    jmp 2f

3:
    #�Ƚ�Ԫ��
    movl 12(%esp), %eax
    movl (%eax), %eax
    movl %eax, 4(%esp)
    movl 8(%esp), %edx
    call *%edx
    cmpl $0, %eax
    #����ȼ���
    je 4f
    #������÷���ֵ�˳�
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

    #�ж������Ƿ�Ϊ��
    movl 8(%ebp), %eax
    cmpl $0, %eax
    je 1f

    #Ԫ�رȽϺ���ʹ��%esp+8
    movl 12(%eax), %edx
    movl %edx, 8(%esp)
    #����Ԫ��ʹ��esp + 12
    movl 4(%eax), %edx
    movl %edx, 12(%esp)
    #ǰ��Ԫ��ʹ��esp + 16
    xorl %edx, %edx
    movl %edx, 16(%esp)
    #����ɾ��Ԫ��ѹջ
    movl 12(%ebp), %eax
    movl %eax, (%esp)
    jmp 2f

3:
    #ȡ������Ԫ���������ݵ��ñȽϺ���
    movl 12(%esp), %eax
    movl (%eax), %eax
    movl %eax, 4(%esp)
    movl 8(%esp), %edx
    call *%edx
    #����ͬ��һ��Ԫ��
    cmpl $1, %eax
    jne 4f
    #��ͬ��ʼɾ��Ԫ��,�õ���Ԫ�صĺ��Ԫ��
    movl 12(%esp), %eax
    movl 4(%eax), %edx

    #����
    movl 8(%ebp), %ebx
    #ǰ��Ԫ��
    movl 16(%esp), %ecx

    #����ǰ��Ԫ���Ƿ�Ϊ�մ���
    cmpl $0, %ecx
    jne 5f

    #û��ǰ��Ԫ�ر�����Ԫ��Ϊͷ�޸�����ͷ
    movl %edx, 4(%ebx)
    jmp 6f

5:
    #��ǰ��Ԫ��,�޸�ǰ������һ��Ԫ��
    movl %edx, 4(%ecx)

6:
    #���Ԫ���Ƿ�β��Ϊβ�޸�β
    cmpl 8(%ebx), %eax
    jne 7f
    #�޸�����βΪǰ��Ԫ��
    movl %ecx, 8(%ebx)

7:
    #�ͷ�Ԫ��
    movl %eax, (%esp)
    call _free
    #�������ݼ�1
    decl (%ebx)
    jmp 1f

4:
    #����ͬ
    movl 12(%esp), %eax
    #�޸�ǰ��Ԫ��
    movl %eax, 16(%esp)
    #��һ��Ԫ��
    movl 4(%eax), %eax
    movl %eax, 12(%esp)

2:
    cmpl $0, 12(%esp)
    jne 3b

1:
    addl $24, %esp
    leave
    ret

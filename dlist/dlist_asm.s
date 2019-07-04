.global _dlist_init_asm, _dlist_destroy_asm, _dlist_insert_asm, _dlist_search_asm, _dlist_delete_asm

dlist_size:
    .int 16
dlist_element_size:
    .int 12

#������
_dlist_init_asm:
    subl $4, %esp

    #�����ڴ�
    movl dlist_size, %eax
    movl %eax, (%esp)
    call _malloc
    #eaxΪ����ֵ
    movl $0, (%eax)
    movl $0, 4(%eax)
    movl $0, 8(%eax)
    movl 8(%esp), %edx
    movl %edx, 12(%eax)

    addl $4, %esp

    ret

#��������
_dlist_destroy_asm:
    push %ebp
    movl %esp, %ebp
    subl $16, %esp

    #����Ԫ��ʹ��esp + 4
    movl 8(%ebp), %eax
    cmpl $0, %eax
    je 1f

    movl 4(%eax), %eax
    movl %eax, 4(%esp)
    jmp 2f

3:
    #��ʱ������edx
    movl 4(%esp), %edx
    #ѭ����Ϊ���Ԫ��
    movl 8(%edx), %eax
    movl %eax, 4(%esp)
    #�ͷ�Ԫ����ռ�ڴ�
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

#�������Ԫ��
_dlist_insert_asm:
    #
    subl $4, %esp
    #�жϴ��������Ƿ�Ϊ��
    cmpl $0, 8(%esp)
    je 1f

    #�½�Ԫ�ط����ڴ�
    movl dlist_element_size, %eax
    movl %eax, (%esp)
    call _malloc
    #�½�Ԫ��ʹ��eax�Ĵ���,���ó�ʼֵ
    movl 16(%esp), %edx
    movl %edx, (%eax)
    movl $0, 4(%eax)
    movl $0, 8(%eax)

    #ǰ��Ԫ��ʹ��ecx�Ĵ���
    movl 12(%esp), %ecx
    #����ʹ��ebx�Ĵ���
    movl 8(%esp), %ebx

    #�����Ƿ���ǰ��Ԫ�ؽ��д���
    cmpl $0, %ecx
    je 2f

    #ǰ��Ԫ�ز�Ϊ��
    #�ж�ǰ��Ԫ���Ƿ�Ϊβ��Ϊβ���޸���βΪ��Ԫ��
    cmpl %ecx, 8(%ebx)
    je 3f

    #��Ϊβ���޸�Ԫ�ؼ����ӹ�ϵ
    #ԭǰ���ĺ�̵�ǰ����Ϊ��Ԫ��
    movl 8(%ecx), %edx
    movl %eax, 4(%edx)
    jmp 4f

3:
    #ǰ��Ϊβ�޸�����βΪ��Ԫ��
    movl %eax, 8(%ebx)

4:
    #������
    #ǰ���ĺ�̸�Ϊ��Ԫ�صĺ��
    movl 8(%ecx), %edx
    movl %edx, 8(%eax)
    #��Ԫ�ص�ǰ���޸�
    movl %ecx, 4(%eax)
    #ǰ���ĺ�̸�Ϊ��Ԫ��
    movl %eax, 8(%ecx)
    jmp 5f

2:
    #����ǰ��Ԫ��Ϊ��
    #�ж��������Ƿ�Ϊ�գ�Ϊ����������Ԫ��Ϊβ
    cmpl $0, (%ebx)
    jne 6f
    #����Ϊ��
    movl %eax, 8(%ebx)
6:
    #��Ԫ��Ϊ����ͷ
    #��Ԫ�صĺ��Ϊ��ͷ
    movl 4(%ebx), %edx
    movl %edx, 8(%eax)

    #�жϾ�ͷ�Ƿ�Ϊ��
    cmpl $0, %edx
    je 7f
    #��Ϊ�����ͷǰ��Ϊ��Ԫ��
    movl %eax, 4(%edx)
7:
    #������ͷΪ��Ԫ��
    movl %eax, 4(%ebx)

5:
    #����������
    incl (%ebx)

1:
    addl $4, %esp
    ret

_dlist_search_asm:
    push %ebp
    movl %esp, %ebp
    subl $16, %esp

    #�ж������Ƿ�Ϊ��
    cmpl $0, 8(%ebp)
    jne 2f
    #Ϊ�շ���
    xorl %eax, %eax
    jmp 1f

2:
    #����Ԫ��ʹ��esp + 8
    movl 8(%ebp), %eax
    movl 4(%eax), %edx
    movl %edx, 8(%esp)
    #�ȽϺ���ʹ��esp + 12
    movl 12(%eax), %edx
    movl %edx, 12(%esp)
    #�Ƚ�����������ǰѹջ
    movl 12(%ebp), %eax
    movl %eax, (%esp)

    jmp 3f

4:
    #ȡ���������ݣ�ѹջ���ñȽϺ���
    movl 8(%esp), %eax
    movl (%eax), %eax
    movl %eax, 4(%esp)
    #
    movl 12(%esp), %eax
    call *%eax
    #
    cmpl $1, %eax
    jne 5f

    #��ȣ����÷���ֵ�˳�
    movl 8(%esp), %eax
    #����ȼ���
    jmp 1f
5:
    #��������
    movl 8(%esp), %eax
    movl 8(%eax), %eax
    movl %eax, 8(%esp)

3:
    cmpl $0, 8(%esp)
    jne 4b

    #δ�������ÿ�
    xorl %eax, %eax

1:
    leave
    ret

#ɾ��������ɾ���봫������������ȵ�����Ԫ��
_dlist_delete_asm:
    push %ebp
    movl %esp, %ebp
    subl $8, %esp
    #������������
    movl 8(%ebp), %eax
    movl %eax, (%esp)
    movl 12(%ebp), %eax
    movl %eax, 4(%esp)
    call _dlist_search_asm
    #������������Ԫ��ֱ��ʹ��eax�Ĵ���
    #�Ƚ��Ƿ��ѵ�
    cmpl $0, %eax
    #δ�ѵ��˳�
    je 1f

    #ǰ��Ԫ��ʹ��ecx�Ĵ���
    movl 4(%eax), %ecx
    #���Ԫ��ʹ��edx�Ĵ���
    movl 8(%eax), %edx
    #����ʹ��ebx�Ĵ���
    movl (%esp), %ebx

    #�ж�ǰ���Ƿ��
    cmpl $0, %ecx
    je 2f
    #�ǿ�����ǰ���ĺ��Ϊ���Ԫ��
    movl %edx, 8(%ecx)
    jmp 3f
2:
    #������������ͷ
    movl %edx, 4(%ebx)

3:
    #�ж�Ԫ���Ƿ�Ϊ����β
    cmpl %eax, 8(%ebx)
    je 4f

    #��������β�������ú�̵�ǰ��Ϊǰ��
    movl %ecx, 4(%edx)
    jmp 5f
4:
    #����β������������βΪǰ��
    movl %ecx, 8(%ebx)

5:
    #����Ԫ������1
    decl (%ebx)
    #�ͷ�Ԫ��
    movl %eax, (%esp)
    call _free

1:
    leave
    ret

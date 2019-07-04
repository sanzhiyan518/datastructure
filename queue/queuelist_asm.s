.global _queuelist_init_asm, _queuelist_destroy_asm, _queuelist_empty, _queuelist_enter_asm, _queuelist_delete_asm

_node_size:
    .int 8

_queuelist_size:
    .int 8

#�������нṹ
_queuelist_init_asm:
    pushl _queuelist_size
    call _malloc
    movl $0, (%eax)
    movl $0, 4(%eax)
    addl $4, %esp
    ret

#��������
_queuelist_destroy_asm:
    cmpl $0, 4(%esp)
    je 1f

    pushl %ebp
    movl %esp, %ebp

    #
    subl $8, %esp
    #ѭ�����б�����esp + 4
    movl 8(%ebp), %eax
    movl (%eax), %eax
    movl %eax, 4(%esp)
    jmp 2f

3:
    movl 4(%esp), %eax
    movl (%eax), %edx
    movl %edx, 4(%esp)
    movl %eax, (%esp)
    call _free

2:
    cmpl $0, 4(%esp)
    jne 3b

    movl 8(%ebp), %eax
    movl %eax, (%esp)
    call _free

    leave
1:
    ret

#�ж϶����Ƿ�Ϊ��
_queuelist_empty_asm:
    movl $-1, %eax
    cmpl $0, 4(%esp)
    je 1f

    movl 4(%esp), %edx
    cmpl $0, (%edx)
    jne 1f
    movl $0, %eax

1:
    ret

#��Ӳ���
_queuelist_enter_asm:
    movl $-1, %eax
    cmpl $0, 4(%esp)
    je 1f

    pushl %ebp
    movl %esp, %ebp

    #ΪԪ�ط����ڴ�
    pushl _node_size
    call _malloc
    movl 12(%ebp), %edx
    movl %edx, 4(%eax)
    movl $0, (%eax)

    #����ʹ��ebx
    movl 8(%ebp), %ebx
    #ԭ��β��Ϊ�գ����ñ�Ԫ�غ��Ϊԭ��β
    cmpl $0, 4(%ebx)
    je 2f
    movl 4(%ebx), %edx
    movl %eax, (%edx)

2:
    #������Ԫ��Ϊ��ͷ
    movl %eax, 4(%ebx)

    #�ж϶�ͷ�Ƿ�Ϊ�գ�Ϊ�����ö�ͷΪ��Ԫ��
    cmpl $0, (%ebx)
    jne 3f
    movl %eax, (%ebx)

3:
    movl $0, %eax

    leave
1:
    ret

#���Ӳ���
_queuelist_delete_asm:
    movl $-1, %eax
    cmpl $0, 4(%esp)
    je 1f

    pushl %ebp
    movl %esp, %ebp
    #����ʹ��ebx�Ĵ���
    movl 8(%ebp), %ebx
    #�ж϶����Ƿ�Ϊ��
    cmpl $0, (%ebx)
    je 2f

    #��Ϊ�մ��������������ö�ͷ
    movl 12(%ebp), %esi
    movl (%ebx), %eax
    movl 4(%eax), %edx
    movl %edx, (%esi)
    movl (%eax), %edx
    movl %edx, (%ebx)
    pushl %eax
    call _free
    movl $0, %eax

2:
    leave
1:
    ret

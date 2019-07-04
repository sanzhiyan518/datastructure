.global _queue_init_asm, _queue_destroy_asm, _queue_full_asm, _queue_empty_asm, _queue_enter_asm, _queue_delete_asm
_void_size:
    .int 4
_queue_size:
    .int 20

#���г�ʼ��
_queue_init_asm:
    pushl %ebp
    movl %esp, %ebp
    subl $8, %esp
    pushl _queue_size
    call _malloc
    #����ʹ�üĴ���%esp+4
    movl %eax, 4(%esp)
    #�����ڴ����
    movl _void_size, %eax
    movl 8(%ebp), %edx
    mull %edx
    movl %eax, (%esp)
    call _malloc

    #���г�ʼ��
    movl %eax, %edx
    movl 4(%esp), %eax
    movl 8(%ebp), %ecx
    movl %ecx, (%eax)
    movl $0, 4(%eax)
    movl $0, 8(%eax)
    movl $-1, 12(%eax)
    movl %edx, 16(%eax)

    leave
    ret


#��������
_queue_destroy_asm:
    cmpl $0, 4(%esp)
    je 1f

    movl 4(%esp), %eax
    movl 16(%eax), %eax
    pushl %eax
    call _free
    movl 8(%esp), %eax
    movl %eax, (%esp)
    call _free
    addl $4, %esp

1:
    ret

#�ж϶����Ƿ�Ϊ��
_queue_empty_asm:
    movl $-1, %eax
    cmpl $0, 4(%esp)
    je 1f

    movl 4(%esp), %edx
    cmpl $0, 4(%edx)
    jne 1f
    movl $0, %eax

1:
    ret

#�ж϶����Ƿ���
_queue_full_asm:
    movl $-1, %eax
    cmpl $0, 4(%esp)
    je 1f

    movl 4(%esp), %edx
    #�Ƚ϶��г������ݻ�
    cmpl (%edx), %ecx
    cmpl %ecx, 4(%edx)
    jne 1f
    movl $0, %eax

1:
    ret

#��Ӳ���
_queue_enter_asm:
    movl $-1, %eax
    cmpl $0, 4(%esp)
    je 1f

    #����ʹ��ebx�Ĵ���
    movl 4(%esp), %ebx
    #�ж϶����Ƿ���
    movl (%ebx), %ecx
    cmpl %ecx, 4(%ebx)
    je 1f

    #δ����β��ǰ
    movl 12(%ebx), %ecx
    incl %ecx
    #�����β�Ѿ���������ݻ��������
    cmpl %ecx, (%ebx)
    jne 2f
    movl $0, %ecx
2:
    #�������ö�β
    movl %ecx, 12(%ebx)
    #�ӳ�����1
    incl 4(%ebx)
    #���
    movl 16(%ebx), %ebx
    movl 8(%esp), %edx
    movl %edx, (%ebx, %ecx, 4)
    movl $0, %eax

1:
    ret

#���Ӳ���
_queue_delete_asm:
    movl $-1, %eax
    cmpl $0, 4(%esp)
    je 1f

    #�ж϶����Ƿ�Ϊ��
    #����ʹ��ebx�Ĵ���
    movl 4(%esp), %ebx
    cmpl $0, 4(%ebx)
    je 1f

    #ȡ����ͷԪ��
    movl 8(%ebx), %ecx
    movl 16(%ebx), %eax
    movl (%eax, %ecx, 4), %edx
    #���ô�������
    movl 8(%esp), %eax
    movl %edx, (%eax)
    #��ͷ��ǰ��������ݻ�����
    incl %ecx
    cmpl %ecx, (%ebx)
    jne 2f
    movl $0, %ecx
2:
    movl %ecx, 8(%ebx)
    #���ȼ�1
    decl 4(%ebx)
    movl $0, %eax

1:
    ret

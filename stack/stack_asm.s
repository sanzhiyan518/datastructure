.text
.global _stack_init_asm, _stack_destroy_asm, _stack_push_asm, _stack_pop_asm, _stack_empty_asm

_stack_size:
    .int 12

_void_size:
    .int 4

#ջ��ʼ��
_stack_init_asm:
    subl $4, %esp

    #Ϊջ�����ڴ�
    pushl _stack_size;
    call _malloc
    #ջʹ��esp+4����
    movl %eax, 4(%esp)
    #����ջ��
    movl 12(%esp), %edx
    movl %edx, (%eax)
    #����ջ��
    movl $-1, %ecx
    movl %ecx, 4(%eax)

    #����Ԫ��ָ�������С
    movl _void_size, %eax
    mull %edx
    #Ϊ��������ڴ�
    movl %eax, (%esp)
    call _malloc
    movl %eax, %edx
    movl 4(%esp), %eax
    movl %edx, 8(%eax)
    addl $8, %esp
    ret

#ջ����
_stack_destroy_asm:
    #�ж�ջ�Ƿ�Ϊ��
    cmpl $0, 4(%esp)
    je 1f

    #�����ڴ��ͷ�
    movl 4(%esp), %eax
    pushl 8(%eax)
    call _free;
    #ջ�ڴ��ͷ�
    pushl 8(%esp)
    call _free

    #�ָ�ջ
    addl $8, %esp
1:
    ret

#ѹ�����
_stack_push_asm:
    cmpl $0, 4(%esp)
    jne 2f
    movl $-1, %eax
    jmp 1f

2:
    #ջֱ��ʹ��ebx�Ĵ���
    movl 4(%esp), %ebx
    #ȡ��ջ��
    movl 4(%ebx), %ecx
    #����
    incl %ecx
    #��ջ��Ƚϴ��ڵ���ջ���˳�
    cmpl (%ebx), %ecx
    jl 3f
    movl -1, %eax
    jmp 1f

3:
    #��������ֱ��ʹ��eax�Ĵ���
    movl 8(%ebx), %eax
    #ѹ������
    movl %ecx, 4(%ebx)
    movl 8(%esp), %edx
    movl %edx, (%eax, %ecx, 4)
    movl $0, %eax

1:
    ret

#��������
_stack_pop_asm:
    cmpl $0, 4(%esp)
    jne 1f
    movl $-1, %eax
    jmp 2f

1:
    #ջʹ��ebx�Ĵ���
    movl 4(%esp), %ebx
    #��ȡջ��ʹ��ecx�Ĵ���
    movl 4(%ebx), %ecx
    #�Ƚ�ջ���Ƿ񳬹�ջ��
    cmpl $-1, %ecx
    jne 3f
    movl $-1, %eax
    jmp 2f

3:
    #��������
    movl 8(%ebx), %eax
    movl (%eax, %ecx, 4), %edx
    #��������ջ��
    decl %ecx
    movl %ecx, 4(%ebx)
    #�������
    movl 8(%esp), %eax
    movl %edx, (%eax)
    movl $0, %eax


2:
    ret

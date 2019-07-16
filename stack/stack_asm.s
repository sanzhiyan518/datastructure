.global liststack_init_asm, liststack_destroy_asm, liststack_push_asm, liststack_pop_asm
.global arraystack_init_asm, arraystack_destroy_asm, arraystack_push_asm, arraystack_pop_asm

#ջ��ʼ��, rdiΪջ������rsiΪԪ�����ٺ���
liststack_init_asm:
    movq %rsi, (%rdi)
    movq $0, 8(%rdi)
    ret

arraystack_init_asm:
    #Ϊջ�ṹ�������Ա:���ٺ�����ջ����ֵ
    movq %rsi, (%rdi)
    movl $-1, 12(%rdi)
    #ջ������ջ
    pushq %rdi
    #���������ڴ���С
    movl 8(%rdi), %edi
    imull $8, %edi
    #���������ڴ�
    call malloc
    #ջ������ջ
    popq %rdi
    #Ϊ�����Ա��ֵ
    movq %rax, 16(%rdi)
    ret

#ջԪ������,rdiΪջ����
liststack_destroy_asm:
    #��ջ�������
    subq $24, %rsp
    #����Ԫ��ʹ��rsp,��ʼֵΪջ������ͷ
    movq 8(%rdi), %rax
    movq %rax, (%rsp)
    #Ԫ�����ٺ���ʹ��rsp+8
    movq (%rdi), %rax
    movq %rax, 8(%rsp)
    #������ǰ��ʹ��rsp+16,��������Ԫ�ؼ������ݳ�Ա

    #�Ƚ�ջ�ĳ�Ա���㣬���������ٴ洢�����ջ����
    movq $0, (%rdi)
    movq $0, 8(%rdi)

    #��ʼѭ��
    jmp 1f

2:
    #ѭ��ȡ������Ԫ��
    movq (%rsp), %rax
    #����Ԫ���޸�Ϊ���Ԫ��
    movq 8(%rax), %rcx
    movq %rcx, (%rsp)
    #����Ԫ�ش洢��ǰ�������У����������
    movq %rax, 16(%rsp)

    #ȡ��Ԫ�����ٺ���
    movq 8(%rsp), %rcx
    #�Ƚ�Ԫ�����ٺ����Ƿ�Ϊ��
    cmpq $0, %rcx
    je 3f
    #����Ԫ�����ٺ���
    movq (%rax), %rdi
    call *%rcx
3:
    #�ͷ�Ԫ���ڴ��
    movq 16(%rsp), %rdi
    call free

1:
    #�����Ƿ񼺽���
    cmpq $0, (%rsp)
    jne 2b

    addq $24, %rsp
    ret

arraystack_destroy_asm:
    #��ջ����������ֲ�����
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp
    #����Ԫ�ص����α���ʹ��(%rsp)����ʼֵΪջ��
    xorq %rax, %rax
    movl 12(%rdi), %eax
    movq %rax, (%rsp)
    #ջ�����Աʹ��rsp+8
    movq 16(%rdi), %rax
    movq %rax, 8(%rsp)
    #ջ����ʹ��rsp+16
    movq %rdi, 16(%rsp)
    #Ԫ�����ٺ���ʹ��rsp+24
    movq (%rdi), %rcx
    movq %rcx, 24(%rsp)
    #Ԫ�����ٺ���Ϊ����ֱ��ջ�ڴ�����㼴��
    jrcxz 1f

    #ѭ������Ԫ�����ٺ���
    jmp 3f

2:
    #ȡ������Ԫ��
    movq 8(%rsp), %rbx          #ջ�������Ա
    movq (%rsp), %rcx            #��ǰ����
    movq (%rbx, %rcx, 8), %rdi
    movq 24(%rsp), %rax
    call *%rax
    decq (%rsp)

3:
    #�ж��Ƿ񼺽���
    cmpl $0, (%rsp)
    jge 2b

1:
    movq 16(%rsp), %rdi
    movl $-1, 12(%rdi)
    #�ͷ������ڴ�
    movq 16(%rdi), %rdi
    call free

    leave
    ret

#��ջ
liststack_push_asm:
    pushq %rdi                  #������ջ
    pushq %rsi

    movq $16, %rdi             #����Ԫ�ط����ڴ�
    call malloc
    popq %rsi                     #������ջ
    popq %rdi

    cmpq $0, %rax               #�ж�Ԫ���ڴ�����Ƿ�ɹ�
    jne 1f
    movq $-1, %rax               #ʧ�ܷ���-1
    ret

1:
    movq %rsi, (%rax)           #����Ԫ�����ݳ�Ա

    cmpq $0, 8(%rdi)            #�Ƚ�ջ������ͷ�Ƿ�Ϊ��
    jne 2f
    movq $0, 8(%rax)             #����Ϊ�գ�����Ԫ��Ϊ����ͷ
    movq %rax,  8(%rdi)
    jmp 3f

2:
    movq 8(%rdi), %rcx          #Ԫ�صĺ������Ϊ����ͷ��������������ͷΪ��Ԫ��
    movq %rcx, 8(%rax)
    movq %rax, 8(%rdi)

3:
    movq $0, %rax
    ret

arraystack_push_asm:
    xorq %rcx, %rcx
    movl 12(%rdi), %ecx       #ȡ��ջ�����ж�ջ����1�Ƿ񼺾��ﵽջ��
    incl %ecx
    cmpl 8(%rdi), %ecx
    jl 1f
    movq $-1, %rax
    ret

1:
    movq 16(%rdi), %rbx               #����ջ�����ݳ�Ա
    movq %rsi, (%rbx, %rcx, 8)
    movl %ecx, 12(%rdi)
    movq $0, %rax
    ret

#��ջ
liststack_pop_asm:
    movq 8(%rdi), %rax              #ȡ������ͷ
    cmpq $0, %rax                     #�ж������Ƿ�Ϊ��
    jne 1f
    movq $-1, %rax
    ret

1:
    movq 8(%rax), %rcx             #��������ͷΪ���Ԫ��
    movq %rcx, 8(%rdi)
    movq (%rax), %rcx               #�������ݳ�Ա
    movq %rcx, (%rsi)
    movq %rax, %rdi                 #�ͷ�Ԫ���ڴ�
    call free
    movq $0, %rax
    ret

arraystack_pop_asm:
    cmpl $-1, 12(%rdi)             #�Ƚ��Ƿ�Ϊ��ջ
    jne 1f
    movq $-1, %rax
    ret

1:
    movq 16(%rdi), %rbx
    xorq %rcx, %rcx
    movl 12(%rdi), %ecx
    movq (%rbx, %rcx, 8), %rax   #�������ݳ�Ա
    movq %rax, (%rsi)
    decl 12(%rdi)                       #ջ����1
    movq $0, %rax
    ret

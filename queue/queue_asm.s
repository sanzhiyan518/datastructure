.global arrayqueue_init_asm,  listqueue_init_asm, arrayqueue_destroy_asm, listqueue_destroy_asm
.global arrayqueue_enqueue_asm, listqueue_enqueue_asm, arrayqueue_dequeue_asm, listqueue_dequeue_asm

#���г�ʼ��
arrayqueue_init_asm:
    pushq %rbp
    movq %rsp, %rbp
    movq %rsi, (%rdi)        #����Ԫ�����ٺ���
    movq $0, 12(%rdi)       #���ö��д�С
    movq $0, 16(%rdi)       #���ö���ͷ
    movq $-1, 20(%rdi)      #���ö���β
    subq $16, %rsp
    movq %rdi, (%rsp)       #���в���ѹջ����ֹ������ú��������仯
    movl 8(%rdi), %edx      #����Ԫ�������С����ѹջ
    imull $8, %edx
    movl %edx, 8(%rsp)
    movl %edx, %edi
    call malloc                   #Ԫ����������ڴ�
    movl 8(%rsp), %edx          #�ָ������С
    movq (%rsp), %rdi            #�ָ�ջ����

    movq %rax, 24(%rdi)    #����Ԫ�������Ա
    movq %rax, %rdi          #Ԫ�������ڴ�����
    movl $0, %esi
    call memset

    leave
    ret

listqueue_init_asm:
    movq %rsi, (%rdi)        #����Ԫ�����ٺ���
    movq $0, 8(%rdi)         #���ö���ͷ��β
    movq $0, 16(%rdi)
    ret

arrayqueue_destroy_asm:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp                  #��ջ����������ֲ�����

    xorq %rax, %rax                 #�������ݱ�����rsp��ʼֵΪ��������-1
    movl 8(%rdi), %eax
    decq %rax
    movq %rax, (%rsp)

    movq 24(%rdi), %rax           #Ԫ��������rsp+8,��������ʹ��ʱ���ٶ����ڴ���ʻ�ȡ
    movq %rax, 8(%rsp)

    movq %rdi, 16(%rsp)           #���в�����rsp+16

    movq (%rdi), %rcx               #Ԫ�����ٺ�����rsp+24
    movq %rcx, 24(%rsp)           #���в�����rsp

    jrcxz 1f                                 #Ԫ�����ٺ���Ϊ��ֱ����ն��нṹ���ͷ�����

    #�����������Ԫ���ͷź���
    jmp 2f

3:
    movq 8(%rsp), %rbx             #����������Ԫ��
    movq (%rbx, %rcx, 8), %rdi
    cmpq $0, %rdi                   #
    je 4f
    movq 24(%rsp), %rax            #����Ԫ�����ٺ���
    call * %rax

4:
    decq (%rsp)                          #�ݼ�����

2:
    movq (%rsp), %rcx               #�жϱ����Ƿ����
    cmpq $0, %rcx
    jge 3b

1:
    movq 16(%rsp), %rdi           #�ָ����в��������ø�����Ա
    movl $0, 12(%rdi)               #���ö��д�С
    movl $0, 16(%rdi)               #���ö���ͷ
    movl $-1, 20(%rdi)              #���ö���β
    movq 24(%rdi), %rdi           #�ͷ������ڴ��
    call free

    leave
    ret

listqueue_destroy_asm:
    pushq %rbp
    movq %rsp, %rbp
    pushq (%rdi)                      #��ջѹ��Ԫ�����ٺ���rsp+16
    pushq 8(%rdi)                    #ѹ������ͷ������Ԫ��rsp+8
    pushq $0                           #����Ԫ�ص�ǰ��rsp

    movq $0, 8(%rdi)                #����ͷ��β����
    movq $0, 16(%rdi)

    jmp 1f

4:
    movq %rax, (%rsp)           #�޸�ǰ��Ԫ��Ϊ����Ԫ��
    movq 8(%eax), %rcx          #�޸ı���Ԫ��Ϊ���
    movq %rcx, 8(%rsp)

    movq 16(%rsp), %rcx        #����Ԫ�����ٺ���
    cmpq $0, %rcx
    je 2f
    movq (%rax), %rdi
    call *%rcx

2:
    movq (%rsp), %rdi            #�ͷ�Ԫ���ڴ�
    call free

1:
    movq 8(%rsp), %rax
    cmpq $0, %rax                 #�����Ƿ����
    jne 4b

    leave
    ret

#���
arrayqueue_enqueue_asm:
    movl 12(%rdi), %ecx       #�ж϶����Ƿ��������򷵻�-1
    cmpl 8(%rdi), %ecx
    jb 1f
    movq $-1, %rax
    ret

1:
    xorq %rcx, %rcx
    movl 20(%rdi), %ecx       #��β��1
    incl  %ecx
    cmpl 8(%rdi), %ecx         #��β��������������ޣ��򷵻���ʼ
    jne 2f
    movl $0, %ecx
2:
    movl %ecx, 20(%rdi)       #��д��β
    movq 24(%rdi), %rbx      #���ݳ�Աд������
    movq %rsi, (%rbx, %rcx, 8)
    incl 12(%rdi)                   #���д�С��1
    ret

listqueue_enqueue_asm:
    pushq %rdi                  #�������
    pushq %rsi
    movq $16, %rdi            #����Ԫ�ط����ڴ�
    call malloc
    popq %rsi                     #��ջ
    popq %rdi

    cmpq $0, %rax              #Ԫ���ڴ����ʧ�ܷ���-1
    jne 3f
    movq $-1, %rax
    ret

3:
    movq %rsi, (%rax)        #����Ԫ�س�Ա
    movq $0, 8(%rax)

    cmpq $0, 16(%rdi)       #�ж϶����Ƿ�Ϊ��ջ
    jne 1f
    movq %rax, 8(%rdi)      #��ջ���ö�ͷΪ��Ԫ��
    jmp 2f

1:
    movq 16(%rdi), %rcx     #���ö�β�ĺ������Ԫ��
    movq %rax, 8(%rcx)

2:
    movq %rax, 16(%rdi)    #���ö�βΪ��Ԫ��
    movq $0, %rax
    ret

#���Ӳ���
arrayqueue_dequeue_asm:
    cmpq $0, 12(%rdi)        #�նӷ���-1
    jne 1f
    movq $-1, %rax

1:
    xorq %rcx, %rcx
    movl 16(%rdi), %ecx           #������ͷԪ��
    movq 24(%rdi), %rbx
    movq (%rbx, %rcx, 8), %rax
    movq %rax, (%rsi)
    movq $0, (%rbx, %rcx, 8)

    incl %ecx                       #��ͷ��1���ﵽ�������޷��ص���ʼ
    cmpl 8(%rdi), %ecx
    jne 2f
    movl $0, %ecx
2:
    movl %ecx, 16(%rdi)
    decl 12(%rdi)                   #���д�С��1
    movq $0, %rax
    ret

listqueue_dequeue_asm:
    movq 8(%rdi), %rax          #ȡ������ͷԪ��
    cmpq $0, %rax                 #�ж��Ƿ�Ϊ�ն��У����򷵻�-1
    jne 1f
    movq $-1, %rax
    ret

1:
    movq (%rax), %rcx            #�������ݳ�Ա
    movq %rcx, (%rsi)

    movq 8(%rax), %rcx          #�޸Ķ���ͷΪԪ�صĺ��
    movq %rcx, 8(%rdi)

    cmpq $0, %rcx                #�жϺ��Ԫ���Ƿ�Ϊ�գ��������Ϊ�ն��У����ö�ͷβΪ��
    jne 2f
    movq $0, 16(%rdi)

2:
    movq %rax, %rdi             #�ͷ�Ԫ���ڴ�
    call free
    movq $0, %rax
    ret

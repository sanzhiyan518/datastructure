.global clist_init_asm, clist_destroy_asm, clist_ins_next_asm, clist_rem_next_asm

#�����ʼ��
clist_init_asm:
    #���������rdi��
    movq $0, (%rdi)
    movq $0, 8(%rdi)
    #Ԫ�����ٺ�����rsi��
    movq %rsi, 16(%rdi)
    movq $0, 24(%rdi)
    ret

#����Ԫ������
clist_destroy_asm:
    #�ж��������Ƿ�Ϊ�㣬Ϊ��ֱ�ӵ��������ڴ�����
    cmpq $0, (%rdi)
    je 1f

    #�����Ȳ�Ϊ��
    #��ջ����������Է����ú�����Ĵ��������仯
    subq $32, %rsp
    #�������ʹ��rsp
    movq %rdi, (%rsp)
    #Ԫ���������ٺ���ʹ��8(%rsp)
    movq 16(%rdi),  %rax
    movq %rax, 8(%rsp)
    #����Ԫ��ʹ��16(%rsp)
    movq 24(%rdi), %rax
    movq %rax, 16(%rsp)
    #����Ԫ�ص�ǰ��ʹ��24(%rsp)�������޸ı���Ԫ�ص���ʱ����

2:
    #ȡ������Ԫ��
    movq 16(%rsp), %rcx
    #������Ԫ���޸�Ϊ����,����Ԫ�ش浽��ʱ����
    movq %rcx, 24(%rsp)
    movq 16(%rcx), %rax
    movq %rax, 16(%rsp)

    #�ж�Ԫ���ͷź����Ƿ�Ϊ��
    movq 8(%rsp), %rax
    cmpq $0, %rax
    je 3f
    #����Ԫ�������ͷź���
    movq  (%rcx), %rdi
    call *%rax

3:
    #�ͷ�Ԫ���ڴ�,��ʱԪ����24(%rsp)�У���Ҫ���ڴ���ȡһ��
    movq 24(%rsp), %rax
    movq %rax, %rdi
    call free

    #�ж�ǰ��Ԫ���Ƿ�ѭ��������ͷ
    movq (%rsp), %rax
    movq 24(%rax), %rax
    cmpq %rax, 16(%rsp)
    jne 2b

4:
    #�ָ�ջ
    movq (%rsp), %rdi
    addq $32, %rsp

1:
    #�����ڴ�����
    movq $0, (%rdi)
    movq $0, 8(%rdi)
    movq $0, 16(%rdi)
    movq $0,  24(%rdi)
    ret

#����
clist_ins_next_asm:
    #�жϴ���ǰ��Ԫ���Ƿ�Ϊ��
    cmpq $0, %rsi
    jne 1f
    #�ж��������Ƿ�Ϊ��
    cmpq $0, (%rdi)
    je 1f
    movq $-1, %rax
    ret

1:
    #������ջ��ֹ�������ú󣬼Ĵ��������仯
    subq $24, %rsp
    movq %rdi, (%rsp)
    movq %rsi, 8(%rsp)
    movq %rdx, 16(%rsp)

    #��Ԫ�ط����ڴ�
    movq $24, %rdi
    call malloc

    #������ջ���Ĵ����ָ�
    movq 16(%rsp), %rdx
    movq 8(%rsp), %rsi
    movq (%rsp), %rdi
    addq $24, %rsp

    #�ڴ����ʧ�ܷ���-1
    cmpq $0, %rax
    jne 2f
    movq $-1, %rax
    ret

2:
    #Ԫ�����ݳ�Ա����
    movq %rdx, (%rax)
    #�Ƚ�������
    cmpq $0, (%rdi)
    jne 3f

    #������Ϊ�㣬������Ԫ��Ϊ����ͷ����Ԫ������
    movq %rax, 8(%rax)
    movq %rax, 16(%rax)
    movq %rax, 24(%rdi)
    jmp 4f

3:
    #��ǰ��Ԫ������
    #ǰ��Ԫ�صĺ��ʹ��rcx
    movq 16(%rsi), %rcx
    movq %rcx, 16(%rax)
    movq %rsi, 8(%rax)

    movq %rax, 16(%rsi)
    movq %rax, 8(%rcx)

4:
    incq (%rdi)
    movq $0, %rax
    ret

#ɾ��
clist_rem_next_asm:
    #������Ϊ�㷵��-1
    cmpq $0, (%rdi)
    jne 1f
    movq $-1, %rax
    ret

1:
    #����Ԫ�صĺ��Ϊɾ��Ԫ�ش洢��rax
    movq 16(%rsi), %rax
    #�ж��Ƿ���������������ֻ��һ��Ԫ�أ�����������Ϊ��
    cmpq %rax, %rsi
    jne 2f
    movq $0, 24(%rdi)
    jmp 3f

2:
    #��ɾ��Ԫ����ǰ����Ԫ�ض���
    #ɾ���ĺ��Ԫ�ش洢��rcx
    movq 16(%rax), %rcx
    movq %rcx, 16(%rsi)
    movq %rsi, 8(%rcx)
    #�Ƚ�Ԫ���Ƿ�����ͷ��������������ͷΪ���
    cmpq %rax, 24(%rdi)
    jne 3f
    movq %rcx, 24(%rdi)

3:
    #ɾ�������ݳ�Ա����
    movq (%rax), %rcx
    movq %rcx, (%rdx)
    #�����ȼ�1
    decq (%rdi)
    #�ͷ�ɾ��Ԫ����ռ�ڴ�
    movq %rax, %rdi
    call free

    #����0
    movq $0, %rax
    ret

.global dlist_init_asm, dlist_destroy_asm, dlist_ins_next_asm, dlist_ins_prev_asm, dlist_remove_asm

#�����ʼ��
dlist_init_asm:
    #�������rdi����
    #���ó���
    movq $0, (%rdi)
    #���ñȽϺ���
    movq $0, 8(%rdi)
    #�������ݳ�Ա���ٺ���,����ָ����rsi����
    movq %rsi, 16(%rdi)
    #��������ͷ��β
    movq $0, 24(%rdi)
    movq $0, 32(%rdi)
    ret


#��������
dlist_destroy_asm:
    #��ջ
    push %rbp
    movq %rsp, %rbp
    subq $24, %rsp

    #���������rdi����,�������rsp+16,�Ա�����
    movq %rdi, 16(%rsp)
    #ȡ������ͷΪ����Ԫ��ʹ��rsp
    movq 24(%rdi), %rax
    movq %rax, (%rsp)
    #Ԫ�����ٺ���ʹ��rsp+8
    movq 16(%rdi), %rax
    movq %rax, 8(%rsp)

    #ѭ����������
    jmp 1f

2:
   #ȡ������Ԫ��
   movq (%rsp), %rdx
   #�ж�Ԫ�����ٺ����Ƿ�Ϊ��
   cmpq $0, 8(%rsp)
   je 3f
   #��Ϊ��,����Ԫ�����ٺ���
   movq 8(%rsp), %rax
   movq (%rdx), %rdi
   call *%rax
3:
    #�ͷ�Ԫ���ڴ�
    movq (%rsp), %rdi
    call free
    #������Ԫ���޸�Ϊ���Ԫ��
    movq (%rsp), %rax
    movq 16(%rax), %rax
    movq %rax, (%rsp)

 1:
    #�жϱ����������
    cmpq $0, (%rsp)
    jne 2b

    #��������
    #�������Ϊ��1������
    movq 16(%rsp), %rdi
    #0Ϊ��2������
    movl $0, %esi
    #����ṹ��Ϊ��3������
    movl $40, %edx
    call memset
    leave
    ret

#����Ԫ�غ������Ԫ��
dlist_ins_next_asm:
    #�����������rdi
    #ǰ��Ԫ�ش���rsi
    #���ݳ�Ա����rdx

    #�ж�ǰ��Ԫ���Ƿ��
    cmpq $0, %rsi
    jne 1f
    #�ж��������Ƿ�Ϊ�㣬ǰ��Ϊ���������Ȳ����򷵻�-1
    cmpq $0, (%rdi)
    je 1f
    movq $-1, %rax
    ret

1:
    #��������ջ������������������ܴ�������ļĴ����ᷢ���仯
    pushq %rdx
    pushq %rsi
    pushq %rdi

    #Ϊ��Ԫ�ط����ڴ�,������rax
    movq $24, %rdi
    call malloc

    #��������
    popq %rdi
    popq %rsi
    popq %rdx

    #�ж��ڴ�����Ƿ�ɹ�
    cmpq $0, %rax
    jne 2f
    movq $-1, %rax
    ret

2:
    #�������ݳ�Ա
    movq %rdx, (%rax)

    cmpq $0, %rsi
    jne 3f
    #���ǰ��Ԫ��Ϊ�գ�������Ϊ�㣩����Ԫ��Ϊ�����ͷ��β
    movq $0, 8(%rax)
    movq $0, 16(%rax)
    movq %rax, 24(%rdi)
    movq %rax, 32(%rdi)
    jmp 4f

3:
    #������ǰ��Ԫ�أ�����ǰ������
    movq 16(%rsi), %rcx
    movq %rcx, 16(%rax)
    movq %rsi, 8(%rax)

    #�ж�ǰ��Ԫ���Ƿ�Ϊ����β��������Ԫ������Ϊ����β
    cmpq  $0,16(%rsi)
    jne 5f
    #����Ϊ����β
    movq %rax, 32(%rdi)
    jmp 6f
5:
    #�޸�ǰ���ĺ��Ԫ�ص�ǰ��Ϊ��Ԫ��
    movq 16(%rsi), %rcx
    movq %rax, 8(%rcx)
6:
    #ǰ���ĺ��Ϊ��Ԫ��
    movq %rax, 16(%rsi)

4:
    #����������
    incq (%rdi)
    movq $0, %rax
    ret

#����Ԫ��ǰ������Ԫ��
dlist_ins_prev_asm:
    #�����������rdi
    #���Ԫ�ش���rsi
    #���ݳ�Ա����rdx

    #�жϺ��Ԫ���Ƿ��
    cmpq $0, %rsi
    jne 1f
    #�ж��������Ƿ�Ϊ�㣬���Ϊ���������Ȳ����򷵻�-1
    cmpq $0, (%rdi)
    je 1f
    movq $-1, %rax
    ret

1:
    #��������ջ������������������ܴ�������ļĴ����ᷢ���仯
    pushq %rdx
    pushq %rsi
    pushq %rdi

    #Ϊ��Ԫ�ط����ڴ�,������rax
    movq $24, %rdi
    call malloc

    #��������
    popq %rdi
    popq %rsi
    popq %rdx

    #�ж��ڴ�����Ƿ�ɹ�
    cmpq $0, %rax
    jne 2f
    movq $-1, %rax
    ret

2:
    #�������ݳ�Ա
    movq %rdx, (%rax)

    cmpq $0, %rsi
    jne 3f
    #������Ԫ��Ϊ�գ�������Ϊ�㣩����Ԫ��Ϊ�����ͷ��β
    movq $0, 8(%rax)
    movq $0, 16(%rax)
    movq %rax, 24(%rdi)
    movq %rax, 32(%rdi)
    jmp 4f

3:
    #��������Ԫ�أ�����������
    #���Ԫ�ص�ǰ��Ϊ��Ԫ�ص�ǰ��
    movq 8(%rsi), %rcx
    movq %rcx, 8(%rax)
    #��Ԫ�صĺ��Ϊ������Ԫ��
    movq %rsi, 16(%rax)

    #�жϺ��Ԫ���Ƿ�Ϊ����ͷ��������Ԫ������Ϊ����ͷ
    cmpq  $0, 8(%rsi)
    jne 5f
    #����Ϊ����ͷ
    movq %rax, 24(%rdi)
    jmp 6f
5:
    #�޸ĺ��Ԫ�ص�ǰ���ĺ��Ϊ��Ԫ��
    movq 8(%rsi), %rcx
    movq %rax, 16(%rcx)
6:
    #���Ԫ�ص�ǰ��Ϊ��Ԫ��
    movq %rax, 8(%rsi)

4:
    #����������
    incq (%rdi)
    movq $0, %rax
    ret

#ɾ��Ԫ��
dlist_remove_asm:
    #���������rdi
    #ɾ��Ԫ����rsi
    #���ݴ���ָ����rdx

    movq $-1, %rax
    #�ж�ɾ��Ԫ���Ƿ�Ϊ��
    cmpq $0, %rsi
    jne 1f
    ret
1:
    #�ж��������Ƿ�Ϊ��
    cmpq $0, (%rdi)
    jne 2f
    ret

2:
    #ȡ��Ԫ�ص�ǰ������
    movq 8(%rsi), %rax
    movq 16(%rsi), %rcx

    #�ж�Ԫ���Ƿ�Ϊ����ͷ��ǰ��Ϊ�գ�
    cmpq $0,  %rax
    jne 3f
    #�޸�����ͷΪԪ�صĺ��
    movq %rcx, 24(%rdi)
    jmp 4f
3:
    #Ԫ�ز�Ϊ����ͷ�����޸�Ԫ�ص�ǰ���ĺ��ΪԪ�صĺ��Ԫ��
    movq %rcx, 16(%rax)

4:
    #�ж�Ԫ���Ƿ�Ϊ����β�����Ϊ�գ�
    cmpq $0, %rcx
    jne 5f
    #�޸�����βΪԪ�ص�ǰ��
    movq %rax, 32(%rdi)
    jmp 6f
5:
    #Ԫ�ز�Ϊ����β�����޸�Ԫ�غ�̵�ǰ��ΪԪ�ص�ǰ��Ԫ��
    movq %rax, 8(%rcx)

6:
    #�����ȼ�1
    decl (%rdi)
    #�������ݳ�Ա
    movq (%rsi), %rcx
    movq %rcx, (%rdx)
    #�ͷ�Ԫ���ڴ�
    movq %rsi, %rdi
    call free
    movq $0, %rax
    ret

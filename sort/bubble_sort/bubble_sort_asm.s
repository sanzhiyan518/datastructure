.global _bubble_sort_asm

_bubble_sort_asm:
    #����Ĵ���
    pusha

    #ֱ��ʹ��ebx����Ԫ���׵�ַ
    movl 36(%esp), %ebx
    #ѭ������iֱ��ʹ��ecx
    #ȡ��Ԫ�س���
    movl 40(%esp), %ecx
    #��1
    decl %ecx
    #ĩ��
    leal (%ebx, %ecx, 4), %ecx

    jmp 1f

6:
    #������־exchangeFlagֱ��ʹ��eax,��0
    xorl %eax, %eax

    #ѭ������jֱ��ʹ��edx����0��ѭ����i
    movl %ebx, %edx

3:
    cmpl %ecx, %edx
    #����ʱ�����˴�ѭ��
    jg 4f

    #ȡ������Ԫ�أ��ж��Ƿ񽻻�
    movl (%edx), %esi
    cmpl 4(%edx), %esi
    jle 5f
    #����
    xchgl %esi, 4(%edx)
    movl %esi, (%edx)
    movl $1, %eax

5:
    #j����
    addl $4, %edx
    jmp 3b

4:
    #�жϽ�����־�Ƿ���1,û�����˳�����
    cmpl $0, %eax
    je 2f
    #i�Լ�
    subl $4, %ecx

1:
    #ѭ��i������0���ж�
    cmpl %ebx, %ecx
    #��С��0�˳�����
    jge 6b

2:
    #�ָ��Ĵ���
    popa
    ret

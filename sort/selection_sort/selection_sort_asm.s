.global _selection_sort_asm

_selection_sort_asm:
    #����ջλ����Ϣ����ջ
    pushl %ebp
    movl %esp, %ebp
    subl $12, %esp

    #�ֲ�����iʹ��ebp-4
    xorl %eax, %eax
    movl %eax, -4(%ebp)
    #����ֲ�����lenλ��ֱ��ʹ��edi�Ĵ���
    movl 12(%ebp), %edi
    decl %edi
    #ȡ�������ַʹ��ebx�Ĵ���
    movl 8(%ebp), %ebx

1:
    #�Ƚ�i�����Ƿ�С�ڱ���len1
    cmpl %edi, -4(%ebp)
    #���ڵ��ڽ���
    jae 2f

    #ʹ��iֵ��ʼ����Сֵ��������minIndexֱ��ʹ��esi�Ĵ���
    movl -4(%ebp), %esi

    #ʹ��i+1��ʼ���ֲ�����jֱ��ʹ��ecx�Ĵ���
    movl %esi, %ecx
    incl %ecx

3:
    #�Ƚϱ���jֵ�Ƿ�С��len
    cmpl %edi, %ecx
    #���ڵ���������һ��ѡ������
    ja 4f

    #ȡ������jֵ,ʹ�û�ַ�ӱ�ַ����Ѱַ��ʽ
    #���������Ĵ���ֵ
    movl (%ebx, %ecx, 4), %edx

    #�Ƚ�����jֵ����С����minIndexֵ
    cmpl (%ebx, %esi, 4), %edx
    #���ڵ��������´�ѭ��
    jge 5f
    #ʹ��j�滻minIndex
    movl %ecx, %esi

5:
    #�ֲ�����j����
    incl %ecx
    jmp 3b

4:
    #�ж�i��minIndex�Ƿ����
    cmpl -4(%ebp), %esi
    #������Թ�
    jz 6f
    #����iֵ��minIndex����ֵ
    #minIndexֵ
    movl (%ebx, %esi, 4), %edx
    #�γ�i����ֵ
    movl -4(%ebp), %eax
    xchgl %edx, (%ebx, %eax, 4)
    movl %edx, (%ebx, %esi, 4)

6:
    #�ֲ�����i����
    incl -4(%ebp)
    #������һ��ѡ������
    jmp 1b

2:
    #�ָ�ջ
    movl %ebp, %esp
    popl %ebp
    ret

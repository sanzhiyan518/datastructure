objects = main.o stack.o stack_asm.o

stack: $(objects)
	gcc -o stack $(objects)

%.o : %.c
	gcc -c $^ -o $@

%.o : %.s
	gcc -c $^ -o $@
    
.PHONY:clean

clean:
	-rm -rf stack $(objects)

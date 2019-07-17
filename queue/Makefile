objects = main.o queue.o queue_asm.o

stack: $(objects)
	gcc  -o queue $(objects)

%.o : %.c
	gcc  -c $^ -o $@

%.o : %.s
	gcc  -c $^ -o $@
    
.PHONY:clean

clean:
	-rm -rf queue $(objects)

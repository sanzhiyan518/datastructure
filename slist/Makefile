objects = main.o slist.o slist_asm.o

slist: $(objects)
	gcc -m32 -o slist $(objects)

%.o : %.c
	gcc -m32 -c $^ -o $@

%.o : %.s
	gcc -m32 -c $^ -o $@
    
.PHONY:clean

clean:
	-rm -rf dlist $(objects)

objects = main.o dlist.o dlist_asm.o

dlist: $(objects)
	gcc -o dlist $(objects)

%.o : %.c
	gcc -c $^ -o $@

%.o : %.s
	gcc -c $^ -o $@
    
.PHONY:clean

clean:
	-rm -rf dlist $(objects)

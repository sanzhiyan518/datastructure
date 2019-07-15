objects = main.o clist.o clist_asm.o

dlist: $(objects)
	gcc -o clist $(objects)

%.o : %.c
	gcc -c $^ -o $@

%.o : %.s
	gcc -c $^ -o $@
    
.PHONY:clean

clean:
	-rm -rf clist $(objects)

objects = main.o hashtable.o hashtable_asm.o

hashtable: $(objects)
	gcc  -o hashtable $(objects)

%.o : %.c
	gcc  -c $^ -o $@

%.o : %.s
	gcc  -c $^ -o $@
    
.PHONY:clean

clean:
	-rm -rf hashtable $(objects)


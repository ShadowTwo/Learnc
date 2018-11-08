CFLAGS=-Wall -g
Objects = logfind.o

base : $(Objects)
	cc -o base $(Objects)

base.o : logfind.c dbg.h
	cc -c base.c

.PHONY : clean
clean :
	rm -f base $(Objects)

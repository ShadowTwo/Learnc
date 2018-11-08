CFLAGS=-Wall -g
Objects = logfind.o

logfind: $(Objects)
	cc -o logfind $(Objects)

logfind.o: logfind.c dbg.h
	cc -c logfind.c

.PHONY: clean
clean:
	rm -f base $(Objects)

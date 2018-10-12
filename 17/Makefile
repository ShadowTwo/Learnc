CFLAGS=-Wall -g
Objects = base.o

base : $(Objects)
	cc -o base $(Objects)

base.o : base.c datastructs.h dbg.h interactive.h UserInput.h
	cc -c base.c

.PHONY : clean
clean :
	rm -f base $(Objects)

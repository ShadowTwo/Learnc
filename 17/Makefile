CFLAGS=-Wall -g
Objects = base.o dbg.o datastructs.o interactive.o UserInput.o

base : $(Objects)
	cc -o base $(Objects)

base.o : bace.c datastructs.h dbg.h interactive.h

	cc -c base.c

dbg.o : dbg.h
	cc - -c dbg.h

datastructs.o : datastructs.h
	cc -c datastructs.h

interactive.o : interactive.h dbg.h datastructs.h UserInput.h
	cc -c interactive.h

UserInput.o : UserInput.h
	cc -c UserInput.h

.PHONY : clean
clean :
	rm -f base $(Objects)

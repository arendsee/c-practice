CC=gcc

route1: bill.o
	# --- route 1 - default
	# link the whole thing (program.c only uses bill.o)
	${CC} program.c -o route1 bill.o

route2: bill.o fred.o program.o
	# --- route 2
	# alternatively we can build a library
	ar crv libfoo.a bill.o fred.o
	${CC} program.o -o route2 libfoo.a

bill.o:
	# compile bill.c individually to make object file
	${CC} -c bill.c

fred.o:
	${CC} -c fred.c

program.o:
	# compile the main program
	${CC} -c program.c

clean:
	# clean out existing libraries and archives
	rm -f *.a *.o route1 route2


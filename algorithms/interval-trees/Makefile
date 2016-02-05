CFLAGS=-Wall -g

all:
	cc ${CFLAGS} -o gen util/generate-intervals.c
	./gen > intervals.tab
	cc ${CFLAGS} -o tree *.c *.h

clean:
	rm -f gen tree intervals.tab

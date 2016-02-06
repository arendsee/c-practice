CFLAGS=-Wall -g

all:
	gcc ${CFLAGS} -o gen util/generate-intervals.c
	./gen > intervals.tab
	gcc ${CFLAGS} -o tree *.c *.h

clean:
	rm -f gen tree intervals.tab

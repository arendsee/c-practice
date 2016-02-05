CFLAGS=-Wall -g

all:
	cc ${CFLAGS} -o gen generate-intervals.c
	./gen > intervals.tab
	sort -n intervals.tab > sorted-intervals.tab
	cc ${CFLAGS} -o tree interval-tree.c

clean:
	rm -f gen tree intervals.tab sorted-intervals.tab

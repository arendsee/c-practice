#!/bin/bash

# clean out existing libraries and archives
rm *.a *.o 2> /dev/null

# compile fred.c and bill.c individually to make object files
gcc -c bill.c fred.c 

# compile the main program
gcc -c program.c

# --- route 1
# link the whole thing (program.c only uses bill.o)
gcc program.c bill.o

# --- route 2
# alternatively we can build a library
ar crv libfoo.a bill.o fred.o
gcc program.o libfoo.a
#

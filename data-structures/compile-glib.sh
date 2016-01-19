#!/usr/bin/bash
set -u

cflags=$(pkg-config --cflags glib-2.0)
libs=$(pkg-config --libs glib-2.0)
cmd="cc $cflags -o a.out $libs 04-glib-array.c"

printf "Compiling with the following cflags:\n$cflags\n-----\n" 

printf "And with the following cflags:\n$libs\n-----\n"

printf "Final command:\n$cmd\n-----\n" 

$cmd

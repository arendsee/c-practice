#IO Benchmarks

The purpose of the programs in this folder is to compare different
implementations of simple IO.

The input data file is a automatically generated 10 million line, 70 character per
line, file of ascii text.

fgets runs in ~1 second
fgetc runs in ~10 seconds
getline is slightly faster than fgets

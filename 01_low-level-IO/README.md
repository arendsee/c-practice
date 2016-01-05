# BLP - Chapter 3 

UNIX provides a small set of functions called *system calls* that comprise the
interface to the OS.

These include

 * open
 * read
 * write
 * close
 * ioctl

The first four are pretty self explanatory. But they are more general than one
might suppose. They can be used to interface with almost anything that is a
file on a UNIX OS, i.e. almost everything. Drivers for most devices will
support their calls in an intuitive way.

*ioctl* is used for more idiosyncratic functions devices need.

Surprisingly, these system calls are slow (being low level doesn't always mean
being fast). It is much faster to use an IO library; these provide buffers and
whatnot. But in this folder, I will write functions using just the raw system
calls.

When you read or write you need to specify a descriptor. The main three are:

 * 0: stdin
 * 1: stdout
 * 2: stderr

These are often opened by default. Alternatively you may open them with *open*.
You may specify other descriptors as well.

## open

oflags

 * O_APPEND
 * O_TRUNC - overwrite
 * O_CREAT - create file if necessary
 * O_EXCL - create file only if it does not exist

mode (requested permissions)
 * S_IRUSR - user can read
 * S_IWUSR - user can write
 * S_IXUSR - user can execute
 * S_IRGRP - group ...
 * S_IWGRP
 * S_IXGRP
 * S_IROTH - other ...
 * S_IWOTH
 * S_IXOTH

This is only a request for permissions. It cannot override the permission
restrictions of umask; it will be ORed against umask.

## umask

A umask of 022 forbids write permissions for anyone other than the user.

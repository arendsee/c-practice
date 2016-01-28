# DBM

DBM is a pre-relational database allowing fast access by key. All values are
held in an associative array, like a perl hash. It allows fast random access
and convenient iteration over the keys using nextkey() functions.

ndbm and gdbm (GNU) are two different implementations. gdbm supersets ndbm
functionallity and has no upper limit on database size (or at least has a limit
that is higher than in ndbm, I'll need to read the docs more carefully).

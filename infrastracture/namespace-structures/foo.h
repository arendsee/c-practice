#ifndef FOO_H
#define FOO_H

/**
 * The template struct
 */
typedef struct { 
  int  (* const bar)(int, int);
  void (* const baz)(void);
} namespace_struct;

// Make this global
extern namespace_struct const foo;

#endif

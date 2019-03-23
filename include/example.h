#ifndef EX_H
#define EX_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define T Example_T
typedef struct T *T;

extern T Example_new(void);
extern void Example_free(T *ex);

#undef T
#endif
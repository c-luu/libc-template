/**
 * @file example.h
 * @author Your name
 * @brief File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 * @see http://fnch.users.sourceforge.net/doxygen_c.html
 */

#ifndef EX_H
#define EX_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * @brief An example of an opaque structure.
 * 
 * It uses two levels of indirection, I think.
 */
#define T Example_T
typedef struct T *T;

/**
 * @brief Instantiates the object.
 * 
 * @code{.c}
 * Example_t ex = Example_new();
 * @endcode
 */
extern T Example_new(void);

/**
 * @brief Frees the object.
 * @param ex The opaque handle we want to free. 
 * @code{.c}
 * Example_free(ex);
 * @endcode
 */
extern void Example_free(T *ex);

#undef T
#endif

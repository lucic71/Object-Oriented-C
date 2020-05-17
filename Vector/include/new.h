#ifndef NEW_H
#define NEW_H

#include <sys/types.h>

/*
 * New and delete operations equivalents from C++.
 *
 */

void * new (const void * class, ...);
void delete (void * item);

/*
 * Returns the cloned object in a generic pointer.
 *
 */
void * clone (const void * self);

/*
 * Checks if the objects self and b differ. If an error
 * occurs it returns -1.
 *
 */
int differ (const void * self, const void * b);

/*
 * Returns the size of our object. If an error occurs it
 * returns -1.
 *
 */

ssize_t sizeOf (const void * self);

#endif

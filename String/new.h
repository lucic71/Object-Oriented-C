#ifndef NEW_H
#define NEW_H

#include <stddef.h>

/*
 * New and delete operations equivalents from C++.
 *
 */

void * new (const void * class, ...);
void delete (void * item);

/*
 * Clone and differ operations for our objects.
 *
 */

void * clone (const void * self);
int differ (const void * self, const void * b);

/*
 * Returns the size of our object.
 *
 */

size_t sizeOf (const void * self);

#endif

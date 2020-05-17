#ifndef CLASS_H
#define CLASS_H

#include <stddef.h>

// the abstract data type String
extern const void * String;

char * get_string(void * self);
size_t get_length(void * self);

#endif

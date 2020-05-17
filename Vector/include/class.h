#ifndef	CLASS_R
#define	CLASS_R

#include <stdarg.h>
#include <stdio.h>

struct Class {
    size_t size;                                            // size of the object
    void * (* ctor) (void * self, va_list * app);           // constructor
    void * (* dtor) (void * self);                          // destructor
    void * (* clone) (const void * self);                   // clone
    int (* differ) (const void * self, const void * b);     // differ
};

#endif

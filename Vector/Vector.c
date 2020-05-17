#include "Vector.h"
#include "class.h"
#include "new.h"
#include "memory.h"

#include <stdarg.h>

/*
 * v1.0 - vector only supports int type and the constructor receives
 *  the size of the newly created vector
 *
 */

/*
 * Vector class.
 *
 */

struct Vector {
    const void * class;
    int * content;
};

/*
 * Constructor and Destructor for Vector class.
 *
 */

static void * Vector_ctor (void * _self, va_list * app) {

    VectorT * self = _self;
    const size_t v_size = va_arg(* app, const size_t);

    CALLOC(self -> content, v_size * sizeof(int));

    return self;
}

static void * Vector_dtor (void * _self) {
    return NULL;
}

/*
 * Clone and differ operations for Vector class.
 *
 */

static void * Vector_clone (const void * _self) {
    return NULL;
}

static int Vector_differ (const void * _self, const void * _b) {
    return 0;
}

/*
 * Static structure containg all operations defined above.
 *
 */

static const struct Class _Vector = {
    sizeof(struct Vector),
    Vector_ctor,
    Vector_dtor,
    Vector_clone,
    Vector_differ
};

/*
 * This is the extern symbol exported from Vector.h.
 *
 */

const void * Vector = & _Vector;

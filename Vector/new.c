#include "new.h"
#include "class.h"

#include "memory.h"
#include "error.h"

/*
 * Notes
 * -----
 *
 *  We will work only with generic pointers to handle as much cases
 *  as possible.
 *
 *  We use double pointers where possible because it easier to make
 *  some sanity checks to check if the content is not NULL or to
 *  see if the class contains some imporant fields like ctor, dtor etc.
 *
 */

/*
 * Arguments
 * ---------
 *  1. A generic pointer to a class that we want to construct
 *  2. Variable number of arguments used to construct the object
 *
 * Description
 * -----------
 *
 *  1. Cast the generic pointer to a Class struct
 *  2. Allocate size for this class
 *  3. Call the ctor with the variable arguments we received
 *  4. Return a pointer to the newly created class
 *
 * Notes
 * -----
 *  When working with the generic pointer p, we do a rather odd thing.
 *
 *  Each class inherits struct Class, so it contains a field struct Class 
 *  on the first position.
 *  We fill this field with the class variable and let the constructor
 *  manage the rest of the fields
 *
 */

void * new (const void * _class, ...) {

    const struct Class * class = _class;

    void * p;
    CALLOC(p, class -> size);

    * (const struct Class **) p = class;

    if (class -> ctor) {

        va_list ap;
        va_start(ap, _class);

        p = class -> ctor(p, &ap);

        va_end(ap);

    }

    return p;

}

/*
 * Arguments
 * ---------
 *  1. The object to be deleted
 *
 * Description
 * -----------
 *  1. Take a double pointer to the object @self
 *  2. Check if the object is valid, then call the destructor
 *  3. Free the memory of the pointer how keept the object
 *
 */

void delete (void * self) {

    const struct Class ** cp = self;

    if (self && * cp && (* cp) -> dtor) {
        self = (* cp) -> dtor(self);
    }

    FREE(self);

}

/*
 * Arguments
 * ---------
 *  1. The object to be cloned
 *
 * Description
 * -----------
 *  1. Take a double pointer to the object @self
 *  2. Check if the object is valid, then call the clone method
 *  3. If the object is not valid the return NULL
 *
 */

void * clone (const void * self) {

    const struct Class ** cp = (const struct Class **) self;

    if (self && * cp && (* cp) -> clone) {
        return (* cp) -> clone (cp);
    }

    return NULL;

}

/*
 * Arguments
 * ---------
 *  1. First object
 *  2. Second object
 *
 * Description
 * -----------
 *  1. Convert the objects to a const struct Class
 *  2. Check if the first object is valid and call the differ method
 *  3. If the above step fails then return -1 and print an error.
 *
 */

int differ (const void * self, const void * b) {

    const struct Class ** cp = (const struct Class **) self;
    const struct Class ** cb = (const struct Class **) b;

    if (self && * cp && (* cp) -> differ) {
        return (* cp) -> differ (cp, cb);
    }

    ERROR(DIFFER_ERROR);

    return -1;

}

/*
 * Arguments
 * ---------
 *  1. The object for which we compute the size
 *
 * Description
 * -----------
 *  1. Convert the object to a const struct Class
 *  2. Check if the object is valid and call the size method
 *  3. If the above step fails then return -1 and print an error.
 *
 */

ssize_t sizeOf (const void * self) {

    const struct Class * cp = (const struct Class *) self;

    if (cp) {
        return cp -> size;
    }

    ERROR(SIZEOF_ERROR);
    
    return -1;
}

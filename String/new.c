#include "new.h"

#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <stdio.h>

void * new (const void * _class, ...) {
    const struct Class * class = _class;
    void * p = calloc(1, class -> size); // create a generic Class

    assert(p);
    // convert the generic Class to a specific _class
    * (const struct Class **) p = class;

    if (class -> ctor) {
        va_list ap;

        va_start(ap, _class);
        p = class -> ctor(p, &ap);
        va_end(ap);
    }

    return p;
}

void delete (void * self) {
    const struct Class ** cp = self;

    if (self && * cp &&  (* cp) -> dtor) {
        self = (* cp) -> dtor(self);
    }

    free(self);
}

void * clone (const void * self) {
    const struct Class ** cp = (const struct Class **) self;

    if (self && * cp && (* cp) -> clone) {
        return (* cp) -> clone (cp);
    }

    return 0;
}

int differ (const void * self, const void * b) {
    const struct Class ** cp = (const struct Class **) self;
    const struct Class ** cb = (const struct Class **) b;

    if (self && * cp && (* cp) -> differ) {
        return (* cp) -> differ (cp, cb);
    }

    puts("Error while comparing the objects");
    return -1;
}

size_t sizeOf (const void * self) {
    const struct Class * cp = (const struct Class *) self;

    assert(self);
    return cp -> size;
}

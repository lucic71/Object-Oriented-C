#include <stdio.h>

#include "new.h"
#include "Object.h"
#include "Set.h"

const void *Set = &_Set;
const void *Object = &_Object;

int main() {
    void *set1 = new(Set);
    void *set2 = new(Set);

    void *obj1 = new(Object);
    void *obj2 = new(Object);
    add(set1, obj1);
    add(set2, obj2);

    apply(set1, store, stdout);
    drop(set1, obj1);

    return 0;
}

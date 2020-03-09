#define _GNU_SOURCE
#include "Set.h"
#include "new.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#if ! defined MANY || MANY < 1
#define MANY 10
#endif

void *new(const void *type, ...) {
    const size_t size = *(const size_t *)type;
    void *p = calloc(1, size);

    assert(p);
    return p;
}

void delete(void *_item) {
    free(_item);
}

void *add(void *_set, const void *_element) {
    struct Set *set = _set;
    struct Object *element = (void*) _element;

    assert(set);
    assert(element);

    if (!contains(set, element)) {
        // add set in container of element
        for (void **p = &element->container_in[0]; p < &element->container_in[0] + MANY; p++) {
            if (! *p) {
                *p = set;
                break;
            }
        }

        // add element in container of set
        for (void **p = &set->container[0]; p < &set->container[0] + MANY; p++) {
            if (! *p) {
                *p = element;
                break;
            }
        }

    }

    ++element->count;
    ++set->count;

    return element;
}

void *find(void *_set, const void *_element) {
    struct Set *set = _set;
    const struct Object *element = _element;

    assert(set);
    assert(element);

    // check if element is in container of set
    for (void **p = &set->container[0]; p < &set->container[0] + MANY; p++) {
        if (*p == element) {
            return (void*)element;
        }
    }

    return 0;
}

int contains(const void *_set, const void *_element) {
    return find((void *)_set, _element) != 0;
}

void *drop(void *_set, const void *_element) {
    struct Set *set = _set;
    struct Object *element = find(set, _element);

    if (element) {
        if (contains(_set, _element)) {
            // remove element from set
            for (void **p = &set->container[0]; p < &set->container[0] + MANY; p++) {
                if (*p == element) {
                    *p = 0;
                    break;
                }
            }
            set->count--;

            // remove set from element
            for (void **p = &element->container_in[0]; p < &element->container_in[0] + MANY; p++) {
                if (*p == set) {
                    *p = 0;
                    break;
                }
            }
            element->count--;

        }

        return element;
    }

    return 0;
}

int differ(const void *a, const void *b) {
    return a != b;
}

unsigned count(const void *_set) {
    const struct Set *set = _set;

    assert(set);
    return set->count;
}

int store(const void *_object, FILE *fp) {
    struct Object *object = (void*) _object;
    char *description;
    int wchars = 0;

    wchars += asprintf(&description, "This is some info about an object:\n");
    fwrite(description, strlen(description), 1, fp);

    free(description);

    wchars += asprintf(&description, "This is the number of sets in which this element stands: %d\n",
        object->count);
    fwrite(description, strlen(description), 1, fp);

    free(description);

    wchars += asprintf(&description, "This is the address of a set in which this element stands: 0x%llx\n",
            (unsigned long long)object->container_in[0]);
    fwrite(description, strlen(description), 1, fp);

    free(description);
    return wchars;
}

int apply(const void *_set, int (*action)(const void *object, FILE *fp), FILE *fp) {
    struct Set *set = (void*)_set;
    assert(set);

  for (void **p = &set->container[0]; p < &set->container[0] + MANY; p++) {
        if (!*p) {
            break;
        }

        int result = action(*p, fp);
        if (!result) {
            return 0;
        }
    }

    return 1;
}

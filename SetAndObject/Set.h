#ifndef SET_H
#define SET_H
#include <stddef.h>
#include <stdio.h>

struct Set {
    unsigned count;
    void *container[10];
};

struct Object {
    unsigned count;
    void *container_in[10];
};

static const size_t _Set = sizeof(struct Set);
static const size_t _Object = sizeof(struct Object);

extern const void *Set;
void *add(void *set, const void *element);
void *find(void *set, const void *element);
void *drop(void *set, const void *element);
int contains(const void *set, const void *element);
unsigned count(const void *set);
int store(const void *object, FILE *fp);
int storev(const void *object, va_list ap);
int apply(const void *set, int (*action)(const void *object, FILE *fp), FILE *fp);

#endif

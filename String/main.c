#include <stdio.h>
#include <stdlib.h>

#include "String.h"
#include "new.h"

int main() {
    struct String * a = new(String, "this is a string encapsulated in my class");
    struct String * b = new(String, "new value");
    struct String * a_clone = clone(a);

    if (!differ(a, a_clone)) {
        puts("The strings are equal");
    }

    printf("This is string 1: %s\n", get_string(a));
    printf("Length of string 1 is: %ld\n", get_length(a));
    printf("This is its clone: %s\n", get_string(a_clone));

    delete(a);
    delete(b);
    delete(a_clone);

    puts("Let's pwn");
    //void * pointer = malloc(24);
    //get_string(pointer);

    return 0;
}

#ifndef ERROR_H_
#define ERROR_H_

/*
 * Macro that prints to stderr the errors.
 *
 */

#define ERROR(error)    \
    do {    \
        fprintf(stderr, "%s\n", error);     \
    } while (0)

/*
 * Errors related to new.c file.
 *
 */

#define DIFFER_ERROR "Error while comparing the objects"
#define SIZEOF_ERROR "Error while computing sizeOf"

#endif

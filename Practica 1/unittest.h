#ifndef __UNIT_TEST__
#define __UNIT_TEST__

/*
 * This file just contains helpers to make testing easier.
 * All you need to understand for the practica is running
 *     test(condition);
 * Will evaluate a condition and print a message if the condition fails.
 */

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * Runs a test function if the test name is valid
 * If you don't understand this syntax, just know its checking
 * the first command line argument from the main function
 * to determine if it should run the passed function.
 */
#define run_test(function) \
  if (argc == 1 || strcmp(#function, argv[1]) == 0) { \
      printf("-- Starting test %s --\n", #function); \
      int errors = function(); \
      if (errors == 0) { \
            printf("-- Test %s PASSED --\n\n", #function); \
      } else { \
            printf("-- Test %s FAILED with %d errors --\n\n", #function, errors); \
            exit_code += errors; \
      } \
  }

// for all check functions, we use a helper to automatically fill in the variable name
// again, don't worry about understanding it, just know it works
// static inline prevents issues from the header being included multiple times

/* Pointers */

/** Checks a pointer is not null */
static inline int _check_not_null(const void* actual, const char* name) {
    if (actual == NULL) {
        printf("FAILED: expected %s != NULL, got NULL\n", name);
        return 1;
    }
    return 0;
}
#define check_not_null(actual) _check_not_null(actual, #actual)

/** Checks that a pointer is null */
static inline int _check_null(const void* actual, const char* name) {
    if (actual != NULL) {
        printf("FAILED: expected %s == NULL, got %p\n", name, actual);
        return 1;
    }
    return 0;
}
#define check_null(actual) _check_null(actual, #actual)


/* Basic values */

/** Checks that an integer value is valid */
static inline int _check_bool(bool expected, bool actual, const char* name) {
    // double negation on expected ensures that any non-zero value is considered "true"
    if (!!expected != actual) {
        printf("FAILED: expected %s == %s, got %s\n", name, expected ? "true" : "false", actual ? "true" : "false");
        return 1;
    }
    return 0;
}
#define check_bool(expected, actual) _check_bool(expected, actual, #actual)

/** Checks that an integer value is valid */
static inline int _check_integer(int expected, int actual, const char* name) {
    if (expected != actual) {
        printf("FAILED: expected %s == %d, got %d\n", name, expected, actual);
        return 1;
    }
    return 0;
}
#define check_integer(expected, actual) _check_integer(expected, actual, #actual)
#define check_integer2(expected, actual) _check_integer(expected, actual, #expected)

/** Checks that a string value is valid */
static inline int _check_string(const char* expected, const char* actual, const char* name) {
    if (strcmp(expected, actual) != 0) {
        printf("FAILED: expected %s == \"%s\", got \"%s\"\n", name, expected, actual);
        return 1;
    }
    return 0;
}
#define check_string(expected, actual) _check_string(expected, actual, #actual)
#define check_string2(expected, actual) _check_string(expected, actual, #expected)


#endif

#include "hw09.h"
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>

#define INV_SYMBOL 36

// Useful static helper functions
static int char_to_int(char c);
const char *skip_whitespace(const char *ptr);


long string_to_long(const char *string, const char **endptr, int base) {
    // still fails test cases -- attend office hours for help
    // Initialize variables
    long result = 0;
    int sign = 1;
    const char *ptr = string;
    errno = 0;

    if (base > 36 || (base < 2 && base != 0)){
      *endptr = ptr;
      errno = 
      return 0;
    }

    // Skip leading whitespaces
    ptr = skip_whitespace(ptr);

    // Handle sign
    if (*ptr == '-') {
        sign = -1;
        ptr++;
    }

    // Handle base 0 (auto-detect hexadecimal or octal)
    if (base == 0) {
        if (*ptr == '0') {
            ptr++;
            if (*ptr == 'x' || *ptr == 'X') {
                base = 16;
                ptr++;
            } else {
                base = 8;
            }
        } else {
            base = 10;
        }
    }

    // Parsing number
    while (*ptr != '\0') {
        int digit = char_to_int(*ptr);
        if (digit == INV_SYMBOL || digit >= base) {
            break;  // Stop if invalid character or base overflow
        }

	if (result*base+digit > LONG_MAX || result*base+digit < LONG_MIN){
          break; // overflow
	}

        result = result * base + digit;
        ptr++;
    }

    // Set endptr to the first invalid character
    *endptr = ptr;

    // Apply sign
    return sign * result;
}

static int char_to_int(char c) {
  // What if c is '0' -- '9'
  if (isdigit(c)) {
    return c - '0';
  }

  // What if c is 'a' -- 'z'
  if (islower(c)) {
    // Only deal with one alphabetic case
    c = toupper(c);
  }

  if (isupper(c)) {
    // 'A' becomes 65 - 65 + 10 = 10, 'B' becomes 11, and so on
    return c - 'A' + 10;
  }

  return INV_SYMBOL;
}

const char *skip_whitespace(const char *ptr) {
  while (isspace(*ptr)) {
    ptr++;
  }

  return ptr;
}

#include "hw09.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Suggested testing function declaration
static void check_string_to_long(const char *string, int base);

int main(int argc, char **argv) {
  errno = 0;

  fprintf(stderr, "Welcome to ECE264, we are working on HW09!\n\n");

  // bases
  check_string_to_long("42", 10);
  check_string_to_long("42", 99);
  check_string_to_long("42", -1);

  // valid characters
  check_string_to_long("@!no way this is valid #&(!????)", 10);
  check_string_to_long("    4   !! 2", 10);

  // whitespace
  check_string_to_long("                 ", 10);
  check_string_to_long("     123      ", 10);

  // edge cases
  check_string_to_long("12    456", 10);
  check_string_to_long("zeqrrtepriot", 10);
  check_string_to_long("Aa23456dDbB", 26);

  // overflow
  check_string_to_long("99999999999999999999999999999999", 10);
  check_string_to_long("-99999999999999999999999999999999", 10);

  // signs
  check_string_to_long("-10", 9);
  check_string_to_long("10", 9);

  // 0 base
  check_string_to_long("x0hfidihiqw", 0);
  check_string_to_long("x12345hfidihiqw", 0);
  check_string_to_long("12344556", 0);
  
  fprintf(stderr, "\nTest cases complete.\n");

  return EXIT_SUCCESS;
}

// Check the string_to_long function and compare the result with expected values
static void check_string_to_long(const char *string, int base) {
  
  // define the end pointer
  const char **endptr_hw09 = NULL;
  const char **endptr_strtol = NULL;

  long long_hw09;
  long long_strtol;
  errno = 0;

  long_hw09 = string_to_long(string, endptr_hw09, base); 
  int errno_hw09 = errno;
  errno = 0;

  long_strtol = strtol(string, endptr_strtol, base);
  int errno_strtol = errno;
  errno = 0;

  // long int strtol(const char *str, char **endptr, int base)
  if (errno_hw09 != errno_strtol){
    printf("FAIL: String: %s, Base: %d, ERRNO: %d, Expected ERRNO: %d", string, base, errno_hw09, errno_strtol);
  }
  else if(long_hw09 != long_strtol){
    printf("FAIL: String: %s, Base: %d, Long: %ld, Expected Long: %ld", string, base, long_hw09, long_strtol);
  }
  else if(*endptr_hw09 != *endptr_strtol){
    printf("FAIL: String: %s, Base: %d, Endptr: %p, Expected Endptr: %p", string, base, *endptr_hw09, *endptr_strtol);
  }
  else{
    printf("PASS: String: %s, Base: %d", string, base);
  }
}


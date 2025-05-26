#include "practica.h"
#include <stdlib.h>
#include "unittest.h"

// whenever check is called, it is comparing arguments for equality
// and printing a message if they do not match


int read_missing() {
    int errors = 0;
    Index index = read_index("invalid/filename/invalid.bin");
    
    errors += check_null(index.entries);
    errors += check_integer(0, index.size);
    
    return errors;
}

int read_empty() {
    int errors = 0;
    Index index = read_index("inputs/empty.bin");
    
    errors += check_null(index.entries);
    errors += check_integer(0, index.size);
    
    return errors;
}

int read_1() {
    int errors = 0;
    
    Index index = read_index("inputs/input1.bin");
    
    errors += check_integer(1, index.size);
    errors += check_not_null(index.entries) * 3;
    // if entries is missing, just mark all those tests as an error
    if (index.entries != NULL) {
        if (index.size < 1) {
            errors += 2; // skipping 2 tests
        } else {
            errors += check_integer(1939, index.entries[0].value);
            errors += check_string("Bruce Wayne", index.entries[0].key);
        }
        
        free(index.entries);
    }
    
    return errors;
}

int read_3() {
    int errors = 0;
    
    Index index = read_index("inputs/input3.bin");
    
    errors += check_integer(3, index.size);
    errors += check_not_null(index.entries) * 7;
    // if entries is missing, just mark all those tests as an error
    if (index.entries != NULL) {
        if (index.size < 1) {
            errors += 6; // skipping 6 tests
        } else {
            errors += check_integer(1940, index.entries[0].value);
            errors += check_string("Richard Grayson", index.entries[0].key);
            
            if (index.size < 2) {
                errors += 4;
            } else {
                errors += check_integer(1983, index.entries[1].value);
                errors += check_string("Jason Todd", index.entries[1].key);
                if (index.size < 3) {
                    errors += 2;
                } else {
                    errors += check_integer(1939, index.entries[2].value);
                    errors += check_string("Bruce Wayne", index.entries[2].key);
                }
            }
        }
        
        free(index.entries);
    }
    
    return errors;
}

int read_5() {
    int errors = 0;
    
    Index index = read_index("inputs/input5.bin");
    
    errors += check_integer(5, index.size);
    errors += check_not_null(index.entries) * 11;
    // if entries is missing, just mark all those tests as an error
    if (index.entries != NULL) {
        if (index.size < 1) {
            errors += 10; // skipping 10 tests
        } else {
            errors += check_integer(1989, index.entries[0].value);
            errors += check_string("Tim Drake", index.entries[0].key);
            
            if (index.size < 2) {
                errors += 8;
            } else {
                errors += check_integer(1983, index.entries[1].value);
                errors += check_string("Jason Todd", index.entries[1].key);
                
                if (index.size < 3) {
                    errors += 6;
                } else {
                    errors += check_integer(1940, index.entries[2].value);
                    errors += check_string("Richard Grayson", index.entries[2].key);
                    
                    if (index.size < 4) {
                        errors += 4;
                    } else {
                        errors += check_integer(1939, index.entries[3].value);
                        errors += check_string("Bruce Wayne", index.entries[3].key);
                        
                        if (index.size < 5) {
                            errors += 2;
                        } else {
                            errors += check_integer(1987, index.entries[4].value);
                            errors += check_string("Damian Wayne", index.entries[4].key);
                        }
                    }
                }   
            }
        }
        
        free(index.entries);
    }
    
    return errors;
}


int main(int argc, const char** argv) {
    // may get mutated by run_test to be the number of failed tests
    int exit_code = EXIT_SUCCESS;
    
    // read tests
    run_test(read_missing);
    run_test(read_empty);
    run_test(read_1);
    run_test(read_3);
    run_test(read_5);
    
    return exit_code;
}

/*
** -----------------------------------------------------------------
** IMPORTANT NOTE: For this assignment, you are not allowed to use
** string.h or any header file other than what is defined below
** -----------------------------------------------------------------
*/
#include "stringm.h"

/*
** strlen_m calculates the length of a string
** const char *string - string to calculate length of
** return the size of the string
**
** note: you can assume string is not NULL
*/
size_t strlen_m(const char *string)
{
    size_t len = 0;
    while(string[len] != '\0'){
        len++;
    }
    return len;
}

/*
** strncpy_m copies n characters of string and returns it
** const char *string - string to copy
** size_t n - number of characters to copy (not including null character)
** return a copy of first n characters of string
**
** note: you can assume string is not NULL
** hint: you will need to malloc a size n + 1 string to accomodate the null character
*/
char *strncpy_m(const char *string, size_t n)
{

    char* copy = malloc((n+1) * sizeof(char));
    for(int i = 0; i<n; i++){
        copy[i] = string[i];
    }
    copy[n] = '\0';
    return copy;
}

/*
** join_m joins an array of strings separated by a delimiter
** Strings strings - structure that stores an array of strings
** const char *delimiter - delimiter string which joins each string
** return the string created by joining all strings with the delimiter
**
** note: you can assume delimiter is not NULL
** hint: return NULL if strings.num_strings is 0
*/
char *join_m(Strings strings, const char *delimiter)
{
    if (strings.num_strings == 0){
        return NULL;
    }

    // use local strlen to find the length before allocation
    int d_length = strlen_m(delimiter);
    int total_length = 0;

    for(int i = 0; i < strings.num_strings; i++){
        total_length += strlen_m(strings.strings[i]);
    }

    // add the delimeters after each string except the last
    total_length += d_length * (strings.num_strings - 1);
    total_length += 1; // '\0' terminator

    // allocate space 
    char *joined = malloc(sizeof(char) * total_length);

    int pos = 0;

    int first_len = strlen_m(strings.strings[0]);
    char *first_copy = strncpy_m(strings.strings[0], first_len);
    for (int i = 0; i < first_len; i++) {
        joined[pos++] = first_copy[i];
    }
    free(first_copy);  // Free temporary copy

    for (int i = 1; i < strings.num_strings; i++) {
        
        // Copy delimiter
        char *delim_copy = strncpy_m(delimiter, d_length);
        for (int j = 0; j < d_length; j++) {
            joined[pos++] = delim_copy[j];
        }
        free(delim_copy);

        // Copy next string
        int str_len = strlen_m(strings.strings[i]);
        char *str_copy = strncpy_m(strings.strings[i], str_len);
        for (int j = 0; j < str_len; j++) {
            joined[pos++] = str_copy[j];
        }
        free(str_copy);
    }
    joined[pos] = '\0';
    return joined;
}

/*
** free_strings frees all allocated elements in strings
** String strings - free each string in strings.strings and strings.strings itself
*/
void free_strings(Strings strings)
{
    // Free each individual string
    for (int i = 0; i < strings.num_strings; i++) {
        free(strings.strings[i]);
    }
    // Free the array itself
    free(strings.strings);
}

/*
** split_m splits a string at any occurence of pattern
** const char *string - string that is searched for the pattern
** const char *pattern - pattern which string should be split
** return a String structure which contains an array of each string
**
** note: you may assume string and pattern are not NULL
** hint 1: TA solution uses strlen_m, strstr_m, and strncpy_m
** hint 2: first calculate how many strings are needed, which is: 
**         (the number of times the delimiter appears + 1)
** hint 3: when trying to store a substring, think about how the length of 
**         that substring might be calculated in terms of pointer arithmetic
**         - what is the outcome of adding or subtract pointers?
** hint 3.5: strstr_m will return a pointer to the first character of the next occurence 
**           or NULL if not found
**          
*/
Strings split_m(const char *string, const char *pattern)
{
    Strings result = { .num_strings = 0, .strings = NULL };

    size_t str_len = strlen_m(string);
    size_t pat_len = strlen_m(pattern);

    // Count occurrences of pattern to determine the number of splits
    size_t count = 1;  // At least 1 substring exists
    const char *ptr = string;
    while ((ptr = strstr_m(ptr, pattern)) != NULL) {
        count++;
        ptr += pat_len;  // Move past the match
    }

    // Allocate space for array of substrings
    result.strings = malloc(count * sizeof(char *));
    result.num_strings = count;

    size_t index = 0;
    const char *start = string;
    const char *match;

    while ((match = strstr_m(start, pattern)) != NULL) {
        // Calculate substring length
        size_t sub_len = match - start;

        // Copy substring
        result.strings[index++] = strncpy_m(start, sub_len);

        // Move past the matched pattern
        start = match + pat_len;
    }

    // Copy the last remaining part after the last delimiter
    result.strings[index] = strncpy_m(start, strlen_m(start));

    return result;
}

/*
** find_and_replace_all_m finds each occurence of the pattern in the string and replaces it
** const char *string - string to search through
** const char *pattern - pattern to search for in the string
** const char *replacement - replacement string for each occurence of the pattern in the string
** return a string in which every occurence of pattern is replaced replacement
**
** note: you may assume string, pattern, and replacement are all not NULL
** hint: there are two main ways of implementing this function, one involves many lines, one involves four
*/
char *find_and_replace_all_m(const char *string, const char *pattern, const char *replacement)
{
    size_t str_len = strlen_m(string);
    size_t pat_len = strlen_m(pattern);
    size_t rep_len = strlen_m(replacement);

    // Count occurrences of pattern in string
    size_t count = 0;
    const char *ptr = string;
    while ((ptr = strstr_m(ptr, pattern)) != NULL) {
        count++;
        ptr += pat_len;  // Move past current occurrence
    }

    // Allocate new string based on replacements
    size_t new_len = str_len + count * (rep_len - pat_len) + 1;
    char *result = malloc(new_len);
    
    size_t src = 0, dest = 0;
    while (string[src] != '\0') {
        const char *match = strstr_m(&string[src], pattern);
        
        if (match == &string[src]) {
            // Copy replacement
            for (size_t i = 0; i < rep_len; i++)
                result[dest++] = replacement[i];
            
            src += pat_len;  // Skip past matched pattern
        } else {
            result[dest++] = string[src++];
        }
    }

    result[dest] = '\0';  // Null-terminate the new string
    return result;
}

/*
** The strstr function is implemented for you to use -- DO NOT MODIFY
** If you are curious about the algorithm used, look up the Knuth-Morris-Pratt (KMP)
** algorithm that can find a substring inside another string 'blazingly fast'
*/
const char *strstr_m(const char *haystack, const char *needle)
{
    size_t haystack_len = 0, needle_len = 0;
    for (const char *h = haystack; *h; h++)
        haystack_len++;
    for (const char *n = needle; *n; n++)
        needle_len++;

    if (needle_len > haystack_len)
        return NULL;

    char *lps_str = malloc(haystack_len + needle_len + 1);
    size_t i = 0;
    for (const char *n = needle; *n; n++, i++)
        lps_str[i] = *n;
    lps_str[i++] = '\1';
    for (const char *h = haystack; *h; h++, i++)
        lps_str[i] = *h;

    int *lps_arr = calloc((haystack_len + needle_len + 1), sizeof *lps_arr);
    size_t l = 0, r = 1;
    bool success = false;

    while (r < haystack_len + needle_len + 1)
    {
        if (lps_str[l] == lps_str[r])
        {
            l++;
            lps_arr[r] = l;
            r++;
        }
        else if (l)
            l = lps_arr[l - 1];
        else
        {
            lps_arr[r] = 0;
            r++;
        }

        if (l == needle_len)
        {
            success = true;
            break;
        }
    }

    free(lps_arr);
    free(lps_str);
    if (success)
        return haystack + (r - l - needle_len - 1);
    return NULL;
}

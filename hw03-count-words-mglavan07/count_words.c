// Modify this file

#include "count_words.h"

/*
Arguments:
    filename: name of the input file
    word: the word to search
    line: temporary space to store what is read from the file
    size: size of line

Return:
    frequency of word in file (subject to below constraints)    
*/
int countWord(char* filename, char* word, char* line, int size)
{
    // Open a file whose name is filename for reading
    // If fopen fails, return -1. 
    // Else, set ret to zero
    
    // Use fgets to read the file in line-by-line
    // If the word appears in the line, increment ret
    // It is possible that the same word appears multiple times in the line

    // EDGE CASES - READ CAREFULLY
    /* 1. If the word is split across multiple lines, DO NOT count the occurrence.
          For ex: line 1 - abcd, line 2 - efgh, word - cdef => Do not count occurrence of cdef */
    /* 2. If the line is "aaaaa" and the word is "aa", the count is defined as follows:
          The first two letters are consumed when the first match occurs. The next
          match starts at the third character. Thus, the correct answer is 2, not 4.*/


    // open the file
    FILE *pF = fopen(filename, "r");

    // validate the file exists
    if (pF == NULL) {
        return -1; 
    }

    // define variables
    int ret = 0; // word count
    int wordLen = strlen(word); // word length

    // read each line of the file
    while (fgets(line, size, pF)) 
    {

        // create a temporary string
        char *current = line;

        // search the temporary string iteratively until no match
        while ((current = strstr(current, word)) != NULL) 
        {

            // increment count
            ret++;

            // "delete" by moving the pointer forward
            current += wordLen; 
        }
    }

    // close the file to stop mem leak
    fclose(pF);

    // return the word count
    return ret;
}
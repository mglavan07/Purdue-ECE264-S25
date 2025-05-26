#include <stdio.h>
#include <stdbool.h>

bool countChar(char * filename, int * counts, int size)
{
  // open a file whose name is filename for reading
  // if fopen fails, return false. Do NOT fclose
  // if fopen succeeds, read every character from the file
  //
  // if a character (call it onechar) is between
  // 0 and size - 1 (inclusive), increase
  // counts[onechar] by one
  // You should *NOT* assume that size is 256
  // reemember to call fclose
  // you may assume that counts already initialized to zero
  // size is the size of counts
  // you may assume that counts has enough memory space
  //
  // hint: use fgetc
  // Please read the document of fgetc carefully, in particular
  // when reaching the end of the file
  //

  // intialize an array of zeros
  // int *arr = calloc(size, sizeof(int));   --> assume counts already 0


  FILE *pF = fopen(filename, "r");
  if (pF == NULL)
  {
    // if failed, return false
    return false;
  }

  // read all characters from the file

  int onechar;
  while ((onechar = fgetc(pF)) != EOF) 
  {
    // Check if the character is within the specified range
    if (onechar >= 0 && onechar < size) 
    {
      counts[onechar]++;
    }
  }

  // close the file
  fclose(pF);

  free(counts);
  return true;
}


void printCounts(int * counts, int size)
{
  // print the values in counts in the following format
  // each line has three items:
  // ind, onechar, counts[ind]
  // ind is between 0 and size - 1 (inclusive)
  // onechar is printed if ind is between 'a' and 'z' or
  // 'A' and 'Z'. Otherwise, print space
  // if counts[ind] is zero, do not print

  // iterate through the array
  for(int i = 0; i < size; i++)
  {
    // check nonzero
    if (counts[i] > 0)
    {
      // print index
      printf("%d, ", i);

      // check  65-90 or 97-122
      if(((i >= 65) && (i <= 90)) || (((i >= 97) && (i <= 122))))
      {
        printf("%c, ", i);
      }

      // print blank if not
      else
      {
        printf(" , ");
      }

      // print count
      printf("%d", counts[i]);
    }
  }
}
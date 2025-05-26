#include <stdio.h>
#include <stdbool.h>


bool addFile(char * filename, int * sum)
{
  // You cannot assume * sum is zero. Thus, * sum needs to be set 0
  // open a file whose name is filename for reading
  // if fopen fails, return false. Do NOT fclose
  // if fopen succeeds, read integers using fscan (do not use fgetc)
  //
  // * sum stores the result of adding all numbers from the file
  // When no more numbers can be read, fclose, return true
  //

  // initialize sum to 0
  *sum = 0; 

  // check the opening of the file 
  FILE *pF = fopen(filename, "r");

  if (pF == NULL)
  {
     // exit the function
     return false;  
  }

  // increment the sum with the read integers
  int value; 

  while (fscanf(pF, "%d", &value) != EOF)
  {
    *sum += value; 
  }

  // close the file
  fclose(pF);

  return true;
}


bool writeSum(char * filename, int sum)
{
  // open a file whose name is filename for writing
  // if fopen succeeds, write sum as an integer using fprintf
  // fprintf should use one newline '\n'
  // fclose, return true
  //

  // attempt to open the file 
  FILE *pF = fopen(filename, "w");

  // exit if NULL
  if (pF == NULL)
  {
    return false;     
  }

  // write the sum 
  fprintf(pF, "%d", sum);

  return true;
}
// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h> 

void eliminate(int n, int k)
{
  // allocate an arry of n elements
  int * arr = malloc(sizeof(* arr) * n);
  // check whether memory allocation succeeds.
  // if allocation fails, stop
  if (arr == NULL)
    {
      fprintf(stderr, "malloc fail\n");
      return;
    }
  // initialize all elements
  // You may initialize the elements to a number of your choice (e.g., 0)
  for (int i = 0; i < n; i++)
  {
    arr[i] = 0;
  }  
  
  // counting to k,
  // mark the eliminated element; you choose the mark (e.g., 1)
  // print the index of the marked element
  // repeat until only one element is unmarked
  int zeros = n;

  // count the number of zeros found
  int found = 0;
  int idx = 0; // index tracker

  while (zeros > 1)
  {
    
    // check the current element
    if (arr[idx] == 0)
    {
      // increment the found counter 
      found++;

      // check if the kth found
      if (found == k)
      {
        arr[idx] = 1;
        // printf("%d\n", idx);
        found = 0;
        zeros--; 
      }
    }
    // cycle the list
    idx = (idx + 1) % n;
  } 
  
  // print the last remaining index

  for (int j = 0; j < n; j++)
  {
    // find the element
    if (arr[j] == 0)
    {
      printf("%d\n", j);
    }
  }

  // release the memory of the array
  free (arr);
}




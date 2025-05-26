#include <stdlib.h>
#include <stdio.h>
#include "hw04.h"

/* The first function you write counts the numbers of vectors
(that is, the number of triads of 32-bit integers) found in the
file with name 'filename'.  It assigns this value to the location
pointed to by 'vector_count'.  If it is unable to open the file,
OR if the file cannot be interpreted as a binary file of vectors
(that is, it does not contain a multiple of three integers' worth of data), it returns
EXIT_FAILURE.  Else, it returns EXIT_SUCCESS.  */
int count_vectors_in_file(char * filename, int * vector_count) {
    // Open the file in "rb" (read binary) mode
    FILE *pFB = fopen(filename, "rb");

    // Return EXIT_FAILURE if unable to be opened
    if (pFB == NULL)
    {
        return EXIT_FAILURE;
    }

    // Set up a buffer of three integers to read to
    int buffer[3];

    // a count of how many integers are read in on the last pass
    size_t triplets = 0;

    // While not encountering the end of the file or receiving an error,
    // call fread with the buffer to retrieve three integers.  Update
    // the counts.
    while(fread(buffer, sizeof(int), 3, pFB) == 3)
    {
        triplets++;
    }

    // Check if we encountered an error or not the expected triplet count
    if (ferror(pFB)) {
        fclose(pFB);
        return EXIT_FAILURE;
    }

    // Assign vector count
    *vector_count = (int)triplets;

    // Close the file
    fclose(pFB);

    // Return EXIT_SUCCESS if the last pass read no partial triplet (end of file)
    return EXIT_SUCCESS;
}

/* The second function you write allocates space for the vectors
counted before - there are vector_count vectors stored in the file at
filename.  It reads in those vector_count vectors from the file 'filename'
to the space it allocates and returns a pointer to that space.

That space will need to be freed - though, of course, not in this function.

In the event of a file read failure or memory allocation failure (both
are unlikely), you can return NULL. */
struct vector * read_vectors_from_file(char * filename, int vector_count) {
    // Open the file in "rb" (read binary) mode
    FILE *pFB = fopen(filename, "rb");

    // Return NULL if unable to open the file
    if (pFB == NULL)
    {
        return NULL;
    }

    // Allocate sufficient space for all the vector structs
    struct vector *vector_list = malloc(vector_count * sizeof(struct vector));
    if (vector_list == NULL) 
    {
        fclose(pFB);
        return NULL;
    }

    // Read in all the vectors from the file
    for (size_t i = 0; i < (size_t)vector_count; i++)
    {
        if (fread(&vector_list[i], sizeof(struct vector), 1, pFB) != 1) {
            free(vector_list);
            fclose(pFB);
            return NULL; // Return NULL if any error occurs while reading
        }
    }

    // Close the file
    fclose(pFB);
    
    return vector_list;
}

/* The third function you write takes in two pointers of type
const void*, casts them to access the attributes of the 
structs to which they point, and returns a positive value if the
first is greater, a negative value if the second is greater,
and 0 if they are equal.  Being greater is determined by the 
x-coordinate's being greater, or, those being equal, by the
y-coordinate's being greater, or, those also being equal, by 
the z-coordinate's being greater. */
int compare_vectors(const void* a, const void* b) {

    // Cast to vectors
    const struct vector* v1 = (const struct vector*)a;
    const struct vector* v2 = (const struct vector*)b;

    // Compare x-coordinates
    if (v1->x != v2->x) 
    {
        return v1->x - v2->x;
    }

    // Compare y-coordinates
    if (v1->y != v2->y) 
    {
        return v1->y - v2->y;
    }

    // Compare z-coordinates
    return v1->z - v2->z;
}

/* The fourth function calls qsort with the appropriate
parameters, including the function above. */
void call_qsort(struct vector * vector_list, int vector_count) {
    qsort(vector_list, vector_count, sizeof(struct vector), compare_vectors);
}

/* The fifth function writes the vectors in 'vector_list' (which
has length 'vector_count') to a binary file at 'filename'.  If the
file cannot be opened, it returns EXIT_FAILURE. */
int write_vectors_to_file(char * filename, struct vector * vector_list, int vector_count) {
    // Open the file in "wb" (write binary) mode
    FILE *pFB = fopen(filename, "wb");

    // Validate the file was opened
    if (pFB == NULL)
    {
        return EXIT_FAILURE;
    }

    // Write the coordinates of each vector to the binary file
    for (size_t i = 0; i < (size_t)vector_count; i++)
    {
        // Get the vector
        if (fwrite(&vector_list[i], sizeof(struct vector), 1, pFB) != 1) {
            fclose(pFB);
            return EXIT_FAILURE; // Return EXIT_FAILURE if writing fails
        }
    }

    // Free memory
    free(vector_list);

    // Close file
    fclose(pFB);
    
    return EXIT_SUCCESS;
}
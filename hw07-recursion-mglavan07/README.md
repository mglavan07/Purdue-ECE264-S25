[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/YAe0DjfE)

# Recursive grid traversal with obstacles

There is a *lot* of background reading in this README, covering enumerations
and 2D arrays. Please read the README fully to make sure
you understand the concepts used in this homework.

Learning Goals
==============

You will learn:

* Enumerations
* 2D arrays
* Recursion

Background
==========

Enumerations
------------

An enumeration data type specifies a set of constant (integer) values that are
all distinct. You can either set the constant values yourself:

```
typedef enum Month {
  JANUARY = 1,
  FEBRUARY = 2,
  MARCH = 3,
  APRIL = 4,
  MAY = 5,
  JUNE = 6,
  JULY = 7,
  AUGUST = 8,
  SEPTEMBER = 9,
  OCTOBER = 10,
  NOVEMBER = 11,
  DECEMBER = 12
} Month;
```

Or you can let the compiler choose the values for you:

```
typedef enum Day {
  SUNDAY,
  MONDAY,
  TUESAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY
} Day;
```

(Note that by convention we make the constants in the enumeration ALL CAPS)

You can then use these values as constants throughout your program. If you
define a variable as having an enumeration type, you're saying that you want
its values to be restricted to those constants:

`Month birthmonth = AUGUST;`

Enumerations are a convenient way of defining a set of constants that are
related to each other. This will let us use specific constants throughout our
program without having to change all of them if we decide to change the values
of the constants.

In this assignment, we are using two enumerations. The first defines the
"types" of grid squares: a wall, an empty space, the starting point, and the
ending point:

```
typedef enum SquareType {
	WALL = '#',
	SPACE = '.',
	START = 's',
	END = 'e'
} SquareType;
```

(Note that we're taking advantage of the fact that C treats characters as
integers of the appropriate ASCII value). 

For the purpose of this assignment, we assume that the START square is always the
upper leftmost square of the grid, but the END square can be anywhere.

Throughout your code, when you want to see whether a particular value is a
wall, you should test if it is equal to `WALL`, not `#`. That way, if we later
want to change what walls look like in our grid, it will be easy.

The second enumeration defines the possible directions you can move in your
path:

```
typedef enum PathType {

	SOUTH = 's',
	EAST = 'e',
} PathType;
```
Generally, in grid traversal problems, you can have multiple additional directions to move, 
(for example	NORTH = 'n', WEST = 'w', SOUTHEAST = 'se',  etc...), but for the purpose of this 
assignment, we assume we can only move down and right to avoid visiting squares more than once.

2D Arrays
---------

What are two-dimensional arrays? If you know how many rows and columns you
want your array to have, you can define a 2D array easily:

```
float matrix[10][20]; //a 10x20 matrix
```

But what if you don't know how many rows and columns you need? We'll have to
use *dynamic memory allocation*, just like we did when we needed arrays of
unknown size.

To allocate a 2D array, we will build an *array of arrays*. We will have an
array (representing the rows of the 2D array) where each element of the array
is *another array*. Allocating 2D arrays is tricky, since we don't know how
many rows and columns we need. We have to do it in two steps.

First, we allocate the array of rows. Because each entry needs to be an array
of floats itself, the type of this array is a *pointer to a pointer to a float*:

```
float * * matrix = malloc(nrows * sizeof(float *));
```

This creates an array of `nrows` pointers to floats. Second, for *each of those pointers* we allocate an array of floats:

```
for (int i = 0; i < nrows; i++) {
  matrix[i] = malloc(ncols * sizeof(float));
}
```

We can now use `matrix` as a normal 2D array. To access the 2nd row and 5th
column, we can write `matrix[1][4]`.

Freeing a 2D Array
------------------

To deallocate a 2D array, we reverse the steps. First, we free each of the
rows, then we free the array that points to all the rows.

```
for (int i = 0; i < nrows; i++) {
  free(matrix[i]);
}
free(matrix);
```

Note that we can't do this in the other order! If we `free(matrix)` first, we
will have no way of getting the addresses of the row arrays we need to
free.

2D Array Coordinates vs. Cartesian Coordinates
----------------------------------------------

Note that 2D arrays (and matrices) work very differently than Cartesian
coordinates. Suppose you have a 2D grid of letters:

```
a b c d
e f g h
i j k l
```

Then your 2D grid has 4 columns (width = 4) and 3 rows (height = 3) You should
thus create a 2D array with 3 rows and 4 columns (note that with arrays we
list the rows first, then the columns).

The coordinate system we use for 2D arrays (and matrices) is different than
Cartesian coordinates.

In Cartesian coordinates, `(0, 0)` is at the bottom left of the grid (the
letter 'i'). In 2D arrays (and matrices), `[0][0]` is at the top left of the
grid (the letter 'a').

In Cartesian coordinates, we list the x position first and then the y
position. For 2D arrays (and matrices), we list the y position (the row) first
and then the x position (the column).

In Cartesian coordinates, incrementing the "y" position moves *up*. In 2D
arrays (and matrices), incrementing the row number moves *down* (the first row
is row 0, the second row is row 1, etc.).

So in Cartesian coordinates, `(2, 3)` would represent the letter 'b', but in
2D arrays, `[2][3]` would represent the letter 'l'.

Grid Traversal with Obstacles
==============

Overview
----------------------------------------------
In this assignemnt, you will implement the functions declared for you in 
`grid_traversal.c`. This is the file where you read a grid from an input file, use 
recursion to find the lexicographically smallest path from the START cell to 
the END cell, and print the path as a sequence of moves. Only moves to the right 
(east) and down (south) are allowed. 

Since we can only move south or east, any valid path will have the 
same number of south and east moves regardless of obstacles in the grid. Thus, 
the lexicographical smallest path is the valid path where we always move east when we can, and 
move south only when we have to. Thus, using recursion, you need to find the path where 
you move east until you cannot move east anymore (because of an obstacle or because 
you reached the boudanries of your grid), then move south just enoough until you can 
move east again (if you can). 

We are not asking you to collect all potential path and then sort them to find the 
smallest lexicographical one, you should make sure to find and print the correct path 
with the recursion logic.

## Function Requirements
The function `read_grid_from_file` must:
1. Allocate a dynamic 2D array.
2. Read the grid from an input file into the array (implemented for you).

The function `lexicographically_smallest_path_util` must:
1. Use recursion to find the lexicographically smallest path from the START cell ('s') to the END cell ('e').
2. Only allow moves to the right (East) and down (South).
3. Print the path as a sequence of moves (using 'e' for East and 's' for South).
4. Return a value to know if it found a path or not

The function `lexicographically_smallest_path` must:
1. Call the `lexicographically_smallest_path_util` function with the proper parameters.
2. Print `-1` if no valid path exists.

The function `free_grid` must:
1. Properly free any dynamically allocated memory after the computation.

## Input Format
The input is provided via a file with the following format:
- The first line contains two integers: the number of rows and the number of columns.
- The subsequent lines contain the grid layout, with each cell represented by one character (`#`, `.`, `s`, or `e`).

### Example Input
```
5 5
s..##
.##..
...#.
.###.
....e
```
## Output Format
- If a valid path exists, print the lexicographically smallest path as a string of moves.
- If no valid path exists, print `-1`.

### Example Output
sssseeee


Testing your code
-----------------

We have provided several test cases for you. Some have valid solutions while others don't.
You can inspect the text files in the expected folder to see what the solution for each grid is.
You can test individual testcases using make test# or the entire suite using make testall.


What do you need to turn in?
----------------------------

Turn in your version of `grid_traversal.c`.
You do not need to modify any other files.


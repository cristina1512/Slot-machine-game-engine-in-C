This program simulates the behavior of a slot machine using custom data structures in C. The program calculates scores for each spin, tracks winning lines and also bonuses, providing a realistic simulation of slot machine mechanics.

=============================================================================================================================================================================

# Specifications

There will be a number N of rows and M of columns, representing all the symbols in this simulator. The columns can move independently of each other, and the symbols within a column always remain in the same relative order (for example, [1, 2, 3, 4] may become [3, 4, 1, 2], but never [1, 3, 2, 4]), following the rotation movement of the columns. There will be at most 10 distinct symbols, which we conveniently number from 0 to 9 (each digit representing a symbol code).

As mentioned above, not all symbols in the matrix can form winning combinations at any given time, but only those located inside a predefined quadrant. The quadrant is a 3 × M rectangle (it spans the entire width of the matrix and contains three symbols from each column). We consider this quadrant to be located at the “top end” of the matrix, meaning it always contains the first three rows of the matrix and cannot be moved.

Example:
N = 8, M = 4;

1 2 3 4  
1 6 2 5  
3 4 2 2  
9 0 1 3  
5 5 5 2  
1 7 8 8  
3 3 6 5  
7 7 7 7  


The quadrant contains the first three rows, i.e. the symbols:
[ [1, 2, 3, 4], [1, 6, 2, 5], [3, 4, 2, 2] ]


=============================================================================================================================================================================

# How to run the program

To test the implementation, run in the terminal the following commands:
`````
make
./main
`````

=============================================================================================================================================================================

# Input Format

The first line contains the number of the task that the user wants the program to execute.
On the second line, 2 integers, N and M separated by space. N is the number of lines of the slot machine, M is the number of collums.
On each of the next N lines should be M integers separated by space.
The rest is tailored to each task.

=============================================================================================================================================================================

# TASK 1

We want to rotate a specified column. For example, if we have a matrix with 5 rows and 3 columns, and we want to rotate the second column by 3 positions, the operation means shifting the symbols of that column downward by three positions, while keeping the first and last columns unchanged. The rotation occurs in the natural direction (top to bottom), and the symbols that “fall out of the matrix” are placed back at the beginning of the same column.

Example:

N = 5, M = 3;
1 2 3
4 5 6
7 8 9
0 1 2
3 4 5
c = 1, r = 3 // column index starts from 0

Rotating the second column by 3 positions results in:

1 8 3
4 1 6
7 4 9
0 2 2
3 5 5


Input format:
```````````
1
N M
......N X M  matrix......
column_number number_of_positions
```````````

Output:
The matrix obtained after the specified rotation will be displayed. Each row will have its elements separated by a single space, and the rows will be separated by a newline character \n.

=============================================================================================================================================================================

# TASK 2

Given a matrix configuration, the program finds all winning combinations. A winning combination is a sequence of symbols located inside the 3×M quadrant that satisfies the following rules:

    - Row wins: a row contains at least 3 identical symbols in a row. Note: for any single row only the longest run of identical symbols is considered.

    - Diagonal wins: there are 3 identical symbols on a diagonal (for example, the symbols at positions (1, i), (2, i+1) and (3, i+2) are identical — the diagonal does not have to start at column 1). Both “main” and “secondary” diagonals are considered, i.e. diagonals of the form [(1,i),(2,i+1),(3,i+2)] and [(3,i),(2,i+1),(1,i+2)].

    - X intersection rule: if two such diagonals form an “X” (they intersect at the middle symbol), that intersection counts as a single winning combination, not two.


The program computes the number of such winning combinations.

The program also computes the score for the given configuration. The score is the sum of the values of all unit winning combinations found in the board. Unit values are:

    - A winning row of K identical symbols has value K (where K >= 3).

    - A winning diagonal of 3 identical symbols has value 7.

    - An X (two diagonals intersecting at the center) has value 21.


Additional bonus rules:

    - For any winning combination above, if the symbol involved is 7, the value of that combination is doubled.

    - If the quadrant contains at most 4 distinct symbols, add 15 to the total score.

    - If the quadrant contains at most 2 distinct symbols, add 100 to the total score.

    - The two distinct-symbol bonuses do not stack (i.e., only one of them can apply).

    - The task is to compute Gigel’s total score for the quadrant under these rules.


Input format:
```````````
2
N M
......N X M  matrix......
```````````

Output format:
Two numbers will be displayed, each on a separate line: the first value represents the number of winning combinations found in the configuration, and the second represents the score obtained from that configuration.

=============================================================================================================================================================================

# TASK 3

The input will first provide the dimensions of the matrix, followed by the matrix itself, and then a series of operations in the form of pairs (column, rotation). Finally, the program will output the total score obtained from the final matrix configuration, summing all scores accumulated during each intermediate stage.

Input format:
```````````
3
N M
......N X M  matrix......
number_of_rotations (T)
column_number_1 number_of_positions_1
column_number_2 number_of_positions_2
.
.
.
column_number_T number_of_positions_T
```````````

Output fornat:
A single number will be displayed, representing the sum of all scores obtained from each configuration.

=============================================================================================================================================================================

# TASK 4

The user might wonder what could be achieved if they were allowed to change a single symbol in the matrix. The program implements this functionality. Specifically, the user wants to replace a symbol at a given position with another symbol in order to maximize the possible score from this operation.

The program should output the theoretical maximum score that could be obtained under these conditions.

Input format:
```````````
4
N M
......N X M  matrix......
```````````

Output format:
A single number will be displayed, representing the maximum total score achievable under the conditions of this task.

=============================================================================================================================================================================

# TASK 5

The user may consider another possibility: since they cannot change the values already in the machine, they envision being able to rotate any two columns of their choice to achieve the maximum score. The program determines the maximum possible score obtainable from two such rotations.

Both rotations are performed simultaneously, with both the columns to rotate and the number of positions to rotate each column being chosen freely. The score is therefore calculated for a single resulting configuration.

Input format:
```````````
5
N M
......N X M  matrix......
```````````

Output format:
A single number will be displayed, representing the maximum total score achievable under the conditions of this task.

=============================================================================================================================================================================

Constraints

1 <= N <= 1000
1 <= M <= 500
1 <= T <= 1000
0 <= any element of the matrix <= 9
1 <= column_number <= M
0 <= number_of_positions <= 2 ^31 - 1

=============================================================================================================================================================================

# Documentation

Functions:
    - AlocateMatrix: Allocates memory for a matrix of size N x M

    - AlocateArray: Allocates memory for an array of size y.

    - ReadMatrix: Reads matrix elements from standard input.

    - DisplayMatrix: Prints the matrix to standard output.

    - CopyMatrix: Copies contents from one matrix to another.

    - SpinThePixels: Rotates column c downward by r positions, wrapping around the values.

    - ScoreLines: Detects horizontal winning sequences of 3+ identical symbols and computes line scores, including bonuses for symbol 7 or low variety of symbols in the top quadrant.

    - ScoreDiagonals: Detects diagonal winning sequences of 3 identical symbols (including X-shapes) and computes diagonal scores with bonuses.

    - FreeMatrix: Frees allocated memory for matrices and arrays.

Main Function:
The program reads the task number (nrtask), matrix dimensions (N, M), and the matrix itself. Then, depending on the task, it read other data.

The program allocates memory for the matrix and auxiliary arrays using AlocateMatrix and AlocateArray. At the end, it frees all allocated memory at the end to avoid leaks.

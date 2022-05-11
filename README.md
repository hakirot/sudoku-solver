
# Sudoku Solver

## Compiling

Clone repository and use command `make` to compile source file from the directory containing the makefile, or use the following command with gcc or a similar C language compiler:

`gcc -std=c99 -o sudoku sudoku.c`

## Running (Linux)

Simply enter this command after compiling in the same directory as the source file:

`./sudoku [filename]` 

The filename must be a valid sudoku file.

## Sudoku Files

Example sudoku puzzle files are included in this repository. They are simple files that follow a basic structure, containing a 9x9 grid with integers from 1-9 for given numbers and 'x's for any spaces that must be solved.

Sudoku files must be exactly 9 lines long with 9 characters on each line separated by spaces, the program will not behave properly if the files do not match the specified format.

Example:

    ----START OF FILE-->x 3 x x 1 x x 6 x>EOL
                        7 5 x x 3 x x 4 8>EOL
                        x x 6 9 8 4 3 x x>EOL
                        x x 3 x x x 8 x x>EOL
                        9 1 2 x x x 6 7 4>EOL
                        x x 4 x x x 5 x x>EOL
                        x x 1 6 7 5 2 x x>EOL
                        6 8 x x 9 x x 1 5>EOL
                        x 9 x x 4 x x 3 x>EOF <-----END OF FILE-----

To test the basic functionality of the program, example sudoku files are provided

    ./sudoku test.su

## Playing

Follow the instructions provided on the main page. Simply enter 5-character strings
containing 3 values separated by two spaces. Respectively, these values represent
the x-coordinate, or column containing the value you wish to change, followed by the
y-coordinate, or row which contains the value you wish to change, and then the value
(1 through 9) you would like to place on that tile in the grid.

Ex.

    > 4 5 6 [enter]

Otherwise, press 'm' (followed by [enter]) to open the menu. Menu options are:

###  1. Reset Puzzle
    
This resets the puzzle to the state it was in when the program first began

### 2. Solve This Puzzle For Me

This option will solve the puzzle using a recursive backtracing algorithm (explained below)

-> [Program behavior is indefined for custom unsolvable puzzles uploaded by user]

### 3. Resume Puzzle (exit menu)

This simply places the user back to the main interface.

### 4. Check My Solution

This will run the Check Solution algorithm, If the puzzle is yet unsolved, the
user is notified of such on the main screen just above the command prompt. If
the puzzle is solved, a simple congratulatory message is displayed before the 
program terminates.

### 5. Quit Game

Exits Program immediately.


> Thanks For Playing!
> hakirot

## Solving Algorithm

Traditional Sudoku, existing in a 9x9 grid, is a game that can be solved in what is commonly referred to among computer scientists as "constant" or O(1) time. This can be accomplished by generating (or referencing) a list, dictionary, or 2D array of every possible configuration of integers between 1 and 9 that are allowed to exist by the rules of a solvable Sudoku grid, and then searching that list for a set that matches the placements of integers for the particular puzzle that you are attempting to solve. However, because there are 6.6x10^21 (6.6 sextillion) possible solvable grids, a different (less memory intensive) approach is used.

### Recursive Backtracing



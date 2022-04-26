
# Sudoku Solver

## Compiling

Clone repository and use command `make` to compile source file from the directory containing the makefile, or use the following command with gcc or a similar C++ compiler:

`gcc -std=c99 -o sudoku sudoku.c`

## Running

Enter the command 

`./sudoku [filename]` 

The "filename" must be a valid sudoku file.

## Sudoku Files

        Sudoku puzzle files are included, but they follow a simple structure.

        They are simple text files of a 9x9 grid with integers from 1-9 for given numbers
        and 'x's for any space that will be represented by a blank, giving the user spaces
        to solve.

        Sudoku files must be exactly 9 lines long with 9 characters on each line separated by
        spaces, program will likely not behave properly if custom sudoku files do not match
        format.

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

        [To test the most basic functionality of the program, I recommend ./sudoku test.su]

    To Play:

        Follow the instructions provided on the main page. Simply enter 5-character strings
        containing 3 values separated by two spaces. Respectively, these values represent
        the x-coordinate, or column containing the value you wish to change, followed by the
        y-coordinate, or row which contains the value you wish to change, and then the value
        (1 through 9) you would like to place on that tile in the grid.

        Ex.

            > 4 5 6 [enter]

        Otherwise, press 'm' (followed by [enter]) to open the menu. Menu options are:

            1. Reset Puzzle
                
                This resets the puzzle to the state it was in when the program first began

            2. Solve This Puzzle For Me

                This option will solve the puzzle and exit the program.

                [Program behaviour is indefined for custom unsolvable puzzles uploaded by user]

            3. Resume Puzzle (exit menu)

                This simply places the user back to the main interface.

            4. Check My Solution

                This will run the Check Solution algorithm, If the puzzle is yet unsolved, the
                user is notified of such on the main screen just above the command prompt. If
                the puzzle is solved, a simple congratulatory message is displayed before the 
                program terminates.

            5. Quit Game

                Exits Program immediately.


    Thanks For Playing!
                    > hakirot



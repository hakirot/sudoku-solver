/*********************************************
 * Author: hakirot 
 * Date: 3/6/2021
 * Description: Sudoku solver program. Details
 *  are in README.txt with a more detailed
 *  version in provided PDF
**********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int checkCol(int, int, int sudoku[9][9]);
int checkRow(int, int, int sudoku[9][9]);
int checkSquare(int, int, int, int sudoku[9][9]);
int checkSingleSquare(int, int, int sudoku[9][9]);
int getInput(char *);
void printGrid(int sudoku[9][9], int error);
void readFile(int sudoku[9][9], char *);
void play(int sudoku[9][9]);
int validate(char [], int, int savestate[9][9]);
int checkSolution(int sudoku[9][9]);
int solvePuzzle(int sudoku[9][9], int, int);

// MAIN - Starting point of program
// @params
// - filename - pass the program the name of the file containing sudoku puzzle
int main(int argc, char * argv[]){

    if(argc != 2){
        printf("Incorrect usage. Include sudoku puzzle file as ./sudoku [filename]");
        exit(1);
    }

    // Initialize 9x9 sudoku grid
    int sudoku[9][9];
    for(int i = 0; i < 9 ; i++){
        for(int j = 0; j < 9; j++){
            sudoku[i][j] = 0;
        }
    }

    // Get sudoku data from file
    readFile(sudoku, argv[1]);
    // Begin game after puzzle is loaded
    play(sudoku);

    return 0;
}

// VALIDATE - validates user input
// @params
//  - input - character string entered by user to be validated
//  - mode - integer 1 or 2 to specify behavior of function
//  - savestate - preserved 9x9 sudoku grid of first load state
// Returns INT
//  - Specifies whether input is accepted, and resulting behaviour
//    in parent function
int validate(char input[], int mode, int savestate[9][9]){

    // remove trailing newline from input
    input[strcspn(input, "\n")] = 0;

    // if mode is 1, function is used to validate main screen entries
    if(mode == 1){
        // no input
        if(strlen(input) == 0){
            return 1;
        }

        // Unusually large input
        if(strlen(input) > 5){
            return 2;
        }

        // User is requesting the menu
        if(strcmp(input, "m") == 0){
            return 9;
        }

        // Test each character in input string for correctness
        else{
            char a, b, c, d, e;

            a = input[0];
            b = input[2];
            c = input[4];
            d = input[1];
            e = input[3];

            // Ensure characters are integers in proper range
            if(a < 49 || a > 57){
                return 3;
            }
            if(b < 49 || b > 57){
                return 3;
            }
            if(c < 48 || c > 57){
                return 3;
            }
            // ensure command is properly spaced
            if(d != ' ' || e != ' '){
                return 3;
            }

            int x, y, num = 0;

            // Convert input coordinates into C-array standard
            x = a - 48;
            y = b - 48;

            // Depth of grid
            y = 9 - y;
            // Span of grid
            x = x - 1;

            // Check user command against the savestate,
            // prevents the user from changeing immutable spaces
            if(savestate[y][x] != 0)
            {
                return 4;    
            }

        }
    }

    // Mode 2 used for checking menu inputs
    if(mode == 2){

        // No input
        if(strlen(input) == 0){
            return 1;
        }

        // Input unneededly large
        if(strlen(input) > 1){
            return 1;
        }

        // Check range
        char a = input[0];
        if(a < 49 || a > 53){

            return 1;
        }
    }

    return 0;
}
// CHECK COLUMN
// - Checks viability of a possible solution provided by
//   solver function by checking a single column
// @params
//  - int x - The column to be checked in the grid
//  - int num - The number the column is being tested against
// RETURNS
//  - BOOLEAN INT - Specifies whether num in column is repeated
//      Returns 0 if not repeated.
int checkCol(int x, int num, int sudoku[9][9]){

    for (int i = 0; i < 9; i++) {
        if(sudoku[x][i] == num) {
            return 1;
        }
    }

    return 0;
}
// CHECK ROW
// - Checks viability of a possible solution provided by
//   solver function by checking a single row
// @params
//  - int y - The row to be checked in the grid
//  - int num - The number the row is being tested against
// RETURNS
//  - BOOLEAN INT - Specifies whether num in row is repeated
//      Returns 0 if not repeated.
int checkRow(int y, int num, int sudoku[9][9]){

    for (int i = 0; i < 9; i++) {
        if(sudoku[i][y] == num) {
            return 1;
        }
    }

    return 0;
}

// CHECK SQUARE
// - Checks viability of a possible solution provided by
//   solver function by checking a single square
// @params
//  - int y - The row of the square
//  - int x - The column of the square
//  - int num - The number the square is being tested against
// RETURNS
//  - BOOLEAN INT - Specifies whether num in square is repeated
//      Returns 0 if not repeated.
int checkSquare(int x, int y, int num, int sudoku[9][9]){

    // Set coordinates to top-left corner of square before checking viability
    if(x < 3){
        x = 0;
    }
    else if (x < 6){
        x = 3;
    }
    else{
        x = 6;
    }
    
    if(y < 3){
        y = 0;
    }
    else if (y < 6){
        y = 3;
    }
    else{
        y = 6;
    }

    // Starting at top-left corner, iterate through all nine squares checking repeats
    for(int i = x; i < x+3; i++){
        for(int j = y; j < y+3; j++){
            if(sudoku[i][j] == num) {
                return 1;
            }
        }
    }

    return 0;
}

// SOLVE PUZZLE
// - Solves a single 9x9 sudoku puzzle using recursive backtracing
// @Params
// - sudoku - a 9x9 sudoku grid to be solved
// - int x - current x position in solution tree
// - int y - current y position in solution tree
int solvePuzzle(int sudoku[9][9], int x, int y){

    int num = 1;

    // 'variable' x and y will test possible solutions in recursive function
    int vx = 0;
    int vy = 0;

    // Find whether value is assigned to current space
    if(sudoku[x][y] != 0){

        // Final Case: Last tile is found to already be a given value
        if (x == 8 && y == 8){
            return 1;
        }

        // Increment if boundary is not reached before iterating next square
        if(x < 8){
            x++;
        }

        // If x is 8, start on the next row
        else{
            if ( y < 8 ){
                x = 0;
                y++;
            }
        }

        // Recursively call solver on the next space because current space is a given
        if(solvePuzzle(sudoku, x, y)) {
            return 1;
        }
        else{
            return 0;
        }
    }
    
    // Begin finding solution for current blank space
    if(sudoku[x][y] == 0){
        // Try all nine integers at current space
        while (num < 10) {
            // Only use integers that meet sudoku rules
            if(!checkSquare(x, y, num, sudoku) && !checkRow(y, num, sudoku) && !checkCol(x, num, sudoku)){
                // Place integet at current space
                sudoku[x][y] = num;

                // Final case: Reached last tile while passing sudoku rules
                if(x == 8 && y == 8) {
                    return 1;
                }

                // Update variable x to next position to test next square
                // Using vx and vy to preserve x and y for incremented num
                if(x < 8) {
                    vx = x + 1;
                }

                // Do the same for y if at last x in grid
                else{
                    if(y < 8) {
                        vx = 0;
                        vy = y + 1;
                    }
                }
                // Test next position
                if(solvePuzzle(sudoku, vx, vy)){
                    return 1;
                }
                // If the function doesn't work, we backtrack to the next num in while loop
            }
            // Increment to try next integer in same place using preserved x/y
            num++;
        }
        // Reset to 0 because none of the numbers in this tree were solvable,
        // return to parent call and try next num
        sudoku[x][y] = 0;

        // Return
        return 0;
    }
}

// PRINT GRID - prints the sudoku grid
// @params
//  - sudoku - current 9x9 sudoku grid the user is playing with
//  - error - error number to be printed along with grid UI
void printGrid(int sudoku[9][9], int error){

    // Array of errors for printing with UI
    char errors[10][100] = {
        "",
        ">>> Input Error: No input entered <<< ",
        ">>> Input Error: Input too long <<<",
        ">>> Input Error: Invalid character string <<<",
        "> Sudoku numbers given at start cannot be changed <",
        "Puzzle Reset!",
        "> Puzzle has not been solved <",
        "",
        "",
        "",
    };

    // Menu strings used to give user options
    char menu[10][100] = {
        "MENU",
        "",
        "",
        "Enter a single integer to choose an option:",
        "1. Reset Puzzle",
        "2. Solve This Puzzle For Me",
        "3. Resume Puzzle (exit menu)",
        "4. Check My Solution",
        "5. Quit Game",
        "",
    };

    // Main screen instructions
    char inst[10][100] = {
        "INSTRUCTIONS",
        "Enter a three-digit string (ex: '1 9 5'). The first",
        "number entered is the x(column), then y(row), and",
        "finally the value you wish to place in the space.",
        "Also, you may place a zero on a square to reset it.",
        "Fill the grid so that every column, row, and 3x3",
        "box contains every digit from 1 to 9.",
        "Enter 'm' to open the menu options.",
        "",
        "",
    };

    // clear screen
    for(int i = 0; i < 80; i++){
        printf("\n");
    }

    // Check if the menu has been requested
    if(error == 9){
        printf("\t\t\t   - = S U D O K U = -     \t\t\t    %s\n\n", menu[0]);
    }

    // Otherwise leave main screen instructions
    else{
        printf("\t\t\t   - = S U D O K U = -  \t\t\t%s\n\n", inst[0]);
    }
    printf("\t\t\t+-------+-------+-------+");

    // Begin printing bulk of screen
    for(int i = 0; i < 9 ; i++){

        // Y-axis
        printf("\n\t\t    %d   |", (9 - i));

        // Print numbers
        for(int j = 0; j < 9; j++){

            // Print a simple . for empty spaces
            if(sudoku[i][j] == 0){
                printf(" .");
            }
            // Otherwise print given numbers
            else{
                printf(" %d", sudoku[i][j]);
            }
            // Print grid separators
            if((j + 1) % 3 == 0){
                printf(" |");
            }
            // Print either menu or instructions based on specification
            if(j == 8){
                if(error == 9){
                    printf("\t%s", menu[i + 1]);
                }

                else{
                    printf("\t%s", inst[i + 1]);
                }
            }
        }

        if((i + 1) % 3 == 0){
            printf("\n\t\t\t+-------+-------+-------+");
        }
    }
    // Errors are printed here
    printf("\n\t\t\t\t\t\t\t    %s", errors[error]);
    // X-Axis
    printf("\n\t\t\t  1 2 3   4 5 6   7 8 9\t\t> ");
}

// PLAY - Initializes the game
// @params
//  - sudoku - takes the 9x9 sudoku grid loaded from the file
void play(int sudoku[9][9]){

    int solved = 0;
    int quit = 0;
    char input[64];
    int error = 0;
    int message = 0;

    // Create savestate for reload
    int savestate[9][9];
    for(int i = 0 ; i < 9; i++){
        for(int j = 0; j < 9; j++){
            savestate[i][j] = sudoku[i][j];
        }
    }

    // Game Start
    while (solved == 0 && quit == 0){

        error = 0;

        // Check messages for printing to user
        if(message > 0){
            if (message == 1){
                error = 5;
            }

            if (message == 2){
                error = 6;
            }
            //reset
            message = 0;
        }

        // Print grid to screen
        printGrid(sudoku, error);

        // Get user input and validate
        memset(input, '\0', 64);
        fgets(input, 63, stdin);
        error = validate(input, 1, savestate);

        // Reprint the grid if there are errors
        if(error != 0 && error != 9){

            // Keep printing until input is properly inputted
            while(error != 0){

                printGrid(sudoku, error);

                memset(input, '\0', 64);
                fgets(input, 63, stdin);
                error = validate(input, 1, savestate);

                // Break if user requests the menu
                if(error == 9){
                    break;
                }
            }

        }

        // Enter the menu
        if (error == 9){

            printGrid(sudoku, error);
            memset(input, '\0', 64);
            fgets(input, 63, stdin);


            while(validate(input, 2, savestate) != 0){

                printGrid(sudoku, error);
                memset(input, '\0', 64);
                fgets(input, 63, stdin);

            }

            // Reset board
            if(input[0] == '1'){
                for (int i = 0; i < 9; i++){
                    for (int j = 0; j < 9; j++){
                        sudoku[i][j] = savestate[i][j];
                        message = 1;
                    }
                }
            }

            // Solve Puzzle!
            if(input[0] == '2'){

                // Reset board
                for (int i = 0; i < 9; i++){
                    for (int j = 0; j < 9; j++){
                        sudoku[i][j] = savestate[i][j];
                        //message = 1;
                    }
                }
                solved = solvePuzzle(sudoku, 0, 0);
                printGrid(sudoku, 9);
                printf("\n\n\t\t\t\tPuzzle has been solved by computer!\n(exited)\n");
            }

            // Check solution
            if(input[0] == '4'){

                solved = checkSolution(sudoku);

                if(solved == 1){
                    printf("\n\t\t\t\t\tYou've done it!\nThx4Playing!\n(exited)\n");
                }
                else{
                    message = 2;
                }
            }

            // Quit game
            if(input[0] == '5'){
                for(int i = 0; i < 80; i++){
                    printf("\n");
                }
                printf("(Exited)\nThx4playing\n");
                quit = 1;
            }
        }

        // Regular command
        if(error == 0){

            // Process input
            int x, y, num = 0;
            x = atoi(strtok(input, " "));
            y = atoi(strtok(NULL, " "));
            num = atoi(strtok(NULL, " \n\0"));

            // Depth of grid
            y = 9 - y;
            // Span of grid
            x = x - 1;

            sudoku[y][x] = num;
        }
    }
}

// CHECK SOLUTION - Check grid for final correctness
// @param
//  - The sudoku grid to be checked
// Returns BOOLEAN INT
//  - 0 if unsolved, 1 if solved
int checkSolution(int sudoku[9][9]){

    int array[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    // Check that all rows do not have repeated integers
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if(sudoku[i][j] == 0){
                return 0;
            }
            else{
                array[sudoku[i][j] - 1] = sudoku[i][j];
            }
        }

        // Check array
        for(int j = 0; j < 9; j++){
            int k = j + 1;
            if(array[j] != k){
                return 0;
            }
        }

        //reset array
        for(int j = 0; j < 9; j++){
            array[j] = 0;
        }
    }

    // Check that all columns do not have repeated integers
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            array[sudoku[j][i] - 1] = sudoku[j][i];
        }

        // Check array
        for(int j = 0; j < 9; j++){
            int k = j + 1;
            if(array[j] != k){
                return 0;
            }
        }

        //reset array
        for(int j = 0; j < 9; j++){
            array[j] = 0;
        }
    }

    // Check all nine squares for repeating integers
    if(checkSingleSquare(0, 0, sudoku) == 0){
        return 0;
    }
    if(checkSingleSquare(0, 3, sudoku) == 0){
        return 0;
    }
    if(checkSingleSquare(0, 6, sudoku) == 0){
        return 0;
    }
    if(checkSingleSquare(3, 0, sudoku) == 0){
        return 0;
    }
    if(checkSingleSquare(6, 0, sudoku) == 0){
        return 0;
    }
    if(checkSingleSquare(3, 3, sudoku) == 0){
        return 0;
    }
    if(checkSingleSquare(3, 6, sudoku) == 0){
        return 0;
    }
    if(checkSingleSquare(6, 3, sudoku) == 0){
        return 0;
    }
    if(checkSingleSquare(6, 6, sudoku) == 0){
        return 0;
    }
    
    // Return solved after all checks are passed
    return 1;
}

// CHECK SINGLE SQUARE - Checks a single sudoku square for correctness
// @params
//  - int y - the y-coordinate of the top-left square to be verified
//  - int x - the x-coordinate of the top-left square to be verified
//  - sudoku[][] - the sudoku grid
int checkSingleSquare(int y, int x, int sudoku[9][9]){

    // Generate 9-space array to be filled by each square
    int array[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    // Extract all nine integers and place in array in order
    for(int i = y; i < y + 3; i++){
        for(int j = x; j < x + 3; j++){

            array[sudoku[i][j] - 1] = sudoku[i][j];
        }
    }

    // Check that all nine spots are filled
    for(int j = 0; j < 9; j++){
        int k = j + 1;
        if(array[j] != k){
            return 0;
        }
    }

    return 1;
}

// READ FILE - Reads a single sudoku file and populates 2D array with integers
// @params
//  - sudoku - 9x9 sudoku grid, initialized to zero
//  - filename - the name of the sudoku file to be extracted
void readFile(int sudoku[9][9], char * filename){

    // Open file and check for error
    FILE * inFD = fopen(filename, "r");
    if(inFD == NULL){
        printf("Failed to open file %s\n", filename);
        exit(1);
    }

    char line[128];
    memset(line, '\0', 128);

    char * token = NULL;
    int index = 0;

    // Begin reading file
    while(fgets(line, 127, inFD)){

        // Get first number on single line
        token = strtok(line, " \n");

        // Populate space if not zero
        if(strcmp(token, "x") != 0){
            sudoku[index][0] = atoi(token);
        }

        // Populate remaining 8 integers on the line
        for(int i = 1; i < 9; i++){

            token = strtok(NULL, " \n");

            if(strcmp(token, "x") != 0){

                sudoku[index][i] = atoi(token);
            }
        }

        memset(line, '\0', 128);
        index++;
    }

    // Close file
    fclose(inFD);
}

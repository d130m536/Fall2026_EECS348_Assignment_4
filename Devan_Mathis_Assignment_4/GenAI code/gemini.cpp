// Source Attribution: Authored by student with assistance from Generative AI
// Description: Main inclusion headers for input/output streams, file handling, and vector/string containers.
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Source Attribution: Authored by student with assistance from Generative AI
// Description: Class definition for SudokuSolver encapsulating state and backtracking logic using objects.
class SudokuSolver {
private:
    // Source Attribution: Authored by student with assistance from Generative AI
    // Description: Private member variables storing the 9x9 board character array, filename, and solution status flag.
    char board[9][9];
    string fileName;
    bool foundAny;

    // Source Attribution: Authored by student with assistance from Generative AI
    // Description: Member function checking if a given digit is valid at a specified row and column.
    bool isValid(int row, int col, char digit) {
        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Loop iterating through all indices 0 to 8 to check row and column constraints.
        for (int i = 0; i < 9; i++) {
            // Source Attribution: Authored by student with assistance from Generative AI
            // Description: Returns false if the digit already exists in the current row.
            if (board[row][i] == digit) return false;
            // Source Attribution: Authored by student with assistance from Generative AI
            // Description: Returns false if the digit already exists in the current column.
            if (board[i][col] == digit) return false;
        }
        
        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Calculates the starting row index of the 3x3 sub-grid block.
        int startRow = row - (row % 3);
        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Calculates the starting column index of the 3x3 sub-grid block.
        int startCol = col - (col % 3);
        
        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Nested loop iterating through the 3x3 sub-grid block rows.
        for (int r = 0; r < 3; r++) {
            // Source Attribution: Authored by student with assistance from Generative AI
            // Description: Nested loop iterating through the 3x3 sub-grid block columns.
            for (int c = 0; c < 3; c++) {
                // Source Attribution: Authored by student with assistance from Generative AI
                // Description: Returns false if the digit is found anywhere within the 3x3 sub-grid block.
                if (board[startRow + r][startCol + c] == digit) return false;
            }
        }
        
        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Returns true if no rule violations were detected for the chosen digit.
        return true;
    }

    // Source Attribution: Authored by student with assistance from Generative AI
    // Description: Recursive backtracking function to traverse cells and test candidates.
    void solve(int row, int col) {
        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Base case checking if row has reached 9, meaning a full valid board has been completed.
        if (row == 9) {
            // Source Attribution: Authored by student with assistance from Generative AI
            // Description: Prints the completed board solution to standard output.
            printBoard();
            // Source Attribution: Authored by student with assistance from Generative AI
            // Description: Sets the flag indicating at least one valid solution has been found.
            foundAny = true;
            // Source Attribution: Authored by student with assistance from Generative AI
            // Description: Returns from the current recursive stack frame.
            return;
        }

        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Determines the row coordinate for the next recursive step, advancing if column is 8.
        int nextRow = (col == 8) ? row + 1 : row;
        
        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Determines the column coordinate for the next recursive step, wrapping around to 0 if 8.
        int nextCol = (col == 8) ? 0 : col + 1;

        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Checks if the current cell is pre-filled with a character other than an underscore.
        if (board[row][col] != '_') {
            // Source Attribution: Authored by student with assistance from Generative AI
            // Description: Bypasses pre-filled cells by recursively calling solve on the next cell coordinates.
            solve(nextRow, nextCol);
        } else {
            // Source Attribution: Authored by student with assistance from Generative AI
            // Description: Iterates through character digits from '1' through '9' to test as candidates.
            for (char d = '1'; d <= '9'; d++) {
                // Source Attribution: Authored by student with assistance from Generative AI
                // Description: Tests if candidate digit 'd' is valid in the current empty cell.
                if (isValid(row, col, d)) {
                    // Source Attribution: Authored by student with assistance from Generative AI
                    // Description: Places candidate digit 'd' into the current cell board position.
                    board[row][col] = d;     
                    
                    // Source Attribution: Authored by student with assistance from Generative AI
                    // Description: Recursively calls solve for the next cell coordinates with the placed digit.
                    solve(nextRow, nextCol); 
                    
                    // Source Attribution: Authored by student with assistance from Generative AI
                    // Description: Backtracks by resetting the cell back to an underscore character for further searching.
                    board[row][col] = '_';   
                }
            }
        }
    }

public:
    // Source Attribution: Authored by student with assistance from Generative AI
    // Description: Constructor initializing the solver object with a specific puzzle filename and default states.
    SudokuSolver(string name) {
        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Assigns the input filename string to the member variable.
        fileName = name;
        
        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Initializes foundAny tracking flag to false.
        foundAny = false;
        
        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Loop iterating across rows to initialize the 9x9 board array.
        for (int i = 0; i < 9; i++) {
            // Source Attribution: Authored by student with assistance from Generative AI
            // Description: Loop iterating across columns to clear board cells with underscores.
            for (int j = 0; j < 9; j++) {
                // Source Attribution: Authored by student with assistance from Generative AI
                // Description: Sets individual board cell to underscore character.
                board[i][j] = '_';
            }
        }
    }

    // Source Attribution: Authored by student with assistance from Generative AI
    // Description: Member function that opens and loads the puzzle file contents into the board array.
    bool loadPuzzle() {
        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Declares and opens an input file stream using the stored filename.
        ifstream file(fileName);
        
        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Checks if the file stream failed to open and returns false if unsuccessful.
        if (!file.is_open()) {
            return false;
        }
        
        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Loop reading puzzle rows from the opened file stream.
        for (int i = 0; i < 9; i++) {
            // Source Attribution: Authored by student with assistance from Generative AI
            // Description: Loop reading puzzle columns and populating board grid elements.
            for (int j = 0; j < 9; j++) {
                // Source Attribution: Authored by student with assistance from Generative AI
                // Description: Extracts character tokens from file into the board matrix.
                file >> board[i][j];
            }
        }
        
        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Closes the input file stream after reading is complete.
        file.close();
        
        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Returns true indicating successful file loading.
        return true;
    }

    // Source Attribution: Authored by student with assistance from Generative AI
    // Description: Member function that prints the current contents of the Sudoku board.
    void printBoard() {
        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Loop iterating through each row of the board.
        for (int i = 0; i < 9; i++) {
            // Source Attribution: Authored by student with assistance from Generative AI
            // Description: Loop iterating through each column of the board row.
            for (int j = 0; j < 9; j++) {
                // Source Attribution: Authored by student with assistance from Generative AI
                // Description: Outputs board cell character followed by a space or empty string at row end.
                cout << board[i][j] << (j == 8 ? "" : " ");
            }
            // Source Attribution: Authored by student with assistance from Generative AI
            // Description: Outputs a newline character at the end of each board row.
            cout << endl;
        }
    }

    // Source Attribution: Authored by student with assistance from Generative AI
    // Description: Driver member function to execute solving operations and print status headers and results.
    void run() {
        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Prints the target puzzle file name indicator header.
        cout << "Puzzle File: " << fileName << endl;
        
        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Prints label for the original un-solved puzzle configuration.
        cout << "Original Puzzle:" << endl;
        
        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Calls printBoard to display the loaded initial puzzle state.
        printBoard();
        
        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Prints label header introducing solutions.
        cout << "\nSolution(s):" << endl;

        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Initiates the recursive backtracking search starting from top-left cell (0,0).
        solve(0, 0);

        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Checks if no solutions were found across the exhaustive search.
        if (!foundAny) {
            // Source Attribution: Authored by student with assistance from Generative AI
            // Description: Prints error message when no solution exists for the puzzle.
            cout << "No solution found" << endl;
        }
        
        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Prints a visual separator line between distinct puzzle output blocks.
        cout << "----------------------------------------" << endl;
    }
};

// Source Attribution: Authored by student with assistance from Generative AI
// Description: Main entry point function for executing the program logic across all puzzle files.
int main() {
    // Source Attribution: Authored by student with assistance from Generative AI
    // Description: Initializes an array containing the names of the five target puzzle text files.
    string files[5] = {"puzzle1.txt", "puzzle2.txt", "puzzle3.txt", "puzzle4.txt", "puzzle5.txt"};

    // Source Attribution: Authored by student with assistance from Generative AI
    // Description: Loop iterating sequentially over each of the five puzzle files.
    for (int i = 0; i < 5; i++) {
        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Instantiates a SudokuSolver object passing the current filename from the array.
        SudokuSolver solver(files[i]);
        
        // Source Attribution: Authored by student with assistance from Generative AI
        // Description: Checks if the puzzle file successfully loads its contents.
        if (solver.loadPuzzle()) {
            // Source Attribution: Authored by student with assistance from Generative AI
            // Description: Executes the solver run routine for the loaded puzzle object.
            solver.run();
        } else {
            // Source Attribution: Authored by student with assistance from Generative AI
            // Description: Prints an error message if a file fails to open.
            cout << "Error: Could not open " << files[i] << endl;
        }
    }

    // Source Attribution: Authored by student with assistance from Generative AI
    // Description: Returns 0 to indicate successful program termination.
    return 0;
}
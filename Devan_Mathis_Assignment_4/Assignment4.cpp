/* Program Name: EECS 348 Assignment 4
 * Brief Description: A recursive object-oriented brute-force 
 *                    sudoku puzzle solver
 * Inputs: puzzle1.txt, puzzle2.txt, puzzle3.txt, 
 *         puzzle4.txt, puzzle5.txt
 * Output: puzzle file name (i.e., puzzle1.txt), puzzle file contents,
 *         and a solution to puzzle or "No solution found" printed out
 * Collaborators: Claude.ai Sonnet 5.5 Medium to write hybrid code of sources' programs
 * Other Sources: Claude.ai and Google Gemini
 * Author's Full Name: Devan Mathis
 * Creation Date: 10/15/2026
*/

#include <iostream>   // used for console output
#include <fstream>    // reads puzzle files 
#include <vector>     // acts as a dynamic array to contain: list of solutions and file names
#include <string>     // file name type

using namespace std;

/*
 * AUTHORSHIP: 
 *      Code: Claude.ai    
 *      Comments: Devan Mathis
 */
class SudokuSolver {
private:
    // represent puzzle w/ wrapper -> can be stored in a vector for printing
    // eliminates need for #include <array>, saving memory
    struct Grid { char cells[9][9]; }; // blank 9x9 grid--currently 0s
 
    char board[9][9];          // blank 9x9 char array
    string fileName;           // puzzle file name
    vector<Grid> solutions;    // grid of solutions
    
    /*
    * AUTHORSHIP: 
    *      Code: Claude.ai    
    *      Comments: Devan Mathis
    */
    // checks if a digit is already present in (row, col) of 3x3 section of puzzle:
    // present --> false, not present --> true 
    bool isValid(int row, int col, char digit) const {
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == digit) return false;   // already in row
            if (board[i][col] == digit) return false;   // already in column
        }
        int startRow = row - (row % 3);                 // adjust to top of 3x3 block
        int startCol = col - (col % 3);                 // adjust to left of 3x3 block
        for (int r = 0; r < 3; r++)
            for (int c = 0; c < 3; c++)
                if (board[startRow + r][startCol + c] == digit) return false;
        return true;                                    // not present
    }
    
    /*
    * AUTHORSHIP: 
    *      Code: Claude.ai    
    *      Comments: Devan Mathis
    */
    // recursive backtracking over cells' digits, one cell per run
    void solve(int row, int col) {
        if (row == 9) {                                 // base case: 9x9
            Grid g;                                     // row == 9, thus full grid 
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 9; j++)
                    g.cells[i][j] = board[i][j];        // copy solution
            solutions.push_back(g);                     // record in g grid
            return;
        }
 
        int nextRow = (col == 8) ? row + 1 : row;       // next cell's row
        int nextCol = (col == 8) ? 0 : col + 1;         // next cell's column
 
        if (board[row][col] != '_') {                   // pre-filled cell
            solve(nextRow, nextCol);
        } else {
            for (char d = '1'; d <= '9'; d++) {         // try each digit
                if (isValid(row, col, d)) {
                    board[row][col] = d;                // place
                    solve(nextRow, nextCol);            // recurse
                    board[row][col] = '_';              // backtrack
                }
            }
        }
    }
    /*
    * AUTHORSHIP: 
    *      Code: Claude.ai    
    *      Comments: Devan Mathis
    */
    // prints a given 9x9 grid w/ seprators between all 3x3 blocks
    void printGrid(const char g[9][9]) const {
        for (int r = 0; r < 9; r++) {
            if (r % 3 == 0 && r != 0) cout << "------+-------+------\n";
            for (int c = 0; c < 9; c++) {
                if (c % 3 == 0 && c != 0) cout << "| ";   // block divider
                cout << g[r][c] << (c < 8 ? " " : "");    // cell + spacing
            }
            cout << '\n';
        }
    }
 
public:
    /*
    * AUTHORSHIP: 
    *      Code: Claude.ai    
    *      Comments: Devan Mathis
    */
    // blanks a board and stores a corresponding filename w/ it
    SudokuSolver(string name) {
        fileName = name;
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                board[i][j] = '_';
    }
    /*
    * AUTHORSHIP: 
    *      Code: Claude.ai    
    *      Comments: Devan Mathis
    */
    // Checks if puzzle file can load a 9x9 grid: yes-->true, no-->false
    bool loadPuzzle() {
        ifstream file(fileName);
        if (!file.is_open()) return false; // can't be opened/DNE
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                if (!(file >> board[i][j])) return false;   // ran out of data
        file.close();
        return true;
    }
    /*
    * AUTHORSHIP: 
    *      Code: Claude.ai    
    *      Comments: Devan Mathis
    */
    // method to run program; acts as a main file, while main checks for conflicts
    void run() {
        cout << "Puzzle:\n";
        printGrid(board);                                           // original puzzle
        cout << '\n';
 
        solve(0, 0);                                                // find all solutions
 
        int n = static_cast<int>(solutions.size());
        if (n == 0) {
            cout << "No solution found\n\n";                       // no solution found
        } else {
            for (int i = 0; i < n; i++) {
                cout << "Solution";
                if (n > 1) cout << " " << (i + 1) << " of " << n; // print solution count
                cout << ":\n";
                printGrid(solutions[i].cells);                    // print solution grids
                cout << '\n';
            }
        }
    }
};
/*
 * AUTHORSHIP: 
 *      Code: Claude.ai    
 *      Comments: Devan Mathis
 */
// reads input file(s), then mainly checks for errors before running whole program
int main(int argc, char* argv[]) {
    vector<string> files;
    for (int i = 1; i < argc; ++i) files.push_back(argv[i]);   // command-line given files
    if (files.empty())                                         // if given none, print all puzzles
        for (int i = 1; i <= 5; ++i) files.push_back("puzzle" + to_string(i) + ".txt");
 
    for (size_t i = 0; i < files.size(); ++i) {
        cout << "==============================\n";            // formatting separator
        cout << "File: " << files[i] << "\n\n";                // file name
 
        SudokuSolver solver(files[i]);                         // load solver object w/ puzzle files
        if (solver.loadPuzzle()) {
            solver.run();                                      // run whole program from solver object
        } else {
            cout << "Could not read a valid 9x9 puzzle from this file.\n\n";
        }
    }
    return 0;
}
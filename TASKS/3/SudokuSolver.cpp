#include <iostream>
using namespace std;
const int N = 9;
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
            if ((col + 1) % 3 == 0 && col != N - 1) {
                cout << "| ";
            }
        }
        cout << endl;
        if ((row + 1) % 3 == 0 && row != N - 1) {
            cout << "---------------------\n";
        }
    }
}
bool findEmptyLocation(int grid[N][N], int &row, int &col) {
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}
bool isSafe(int grid[N][N], int row, int col, int num) {
    for (int c = 0; c < N; c++) {
        if (grid[row][c] == num) {
            return false;
        }
    }
    for (int r = 0; r < N; r++) {
        if (grid[r][col] == num) {
            return false;
        }
    }
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (grid[r + startRow][c + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}
bool solveSudoku(int grid[N][N]) {
    int row, col;
    if (!findEmptyLocation(grid, row, col)) {
        return true; 
    }
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid)) {
                return true;
            }
            grid[row][col] = 0; 
        }
    }
    return false; 
}
int main() {
    int grid[N][N];
    cout << "=======================================\n";
    cout << "           Sudoku Solver\n";
    cout << "=======================================\n";
    cout << "Enter the 9x9 Sudoku grid row by row:\n";
    cout << "Use '0' for empty cells.\n\n";
    for (int row = 0; row < N; row++) {
        cout << "Enter 9 numbers for Row " << row + 1 << ": \n";
        for (int col = 0; col < N; col++) {
            if (!(cin >> grid[row][col])) {
                cout << "Error: Invalid input detected. Exiting.\n";
                return 1;
            }
            if (grid[row][col] < 0 || grid[row][col] > 9) {
                cout << "Error: Numbers must be between 0 and 9!!! Exiting!\n";
                return 1;
            }
        }
    }
    cout << "\n---|| Entered Sudoku Grid ||---\n";
    printGrid(grid);
    cout << "\nAttempting to solve...\n\n";
    if (solveSudoku(grid)) {
        cout << "---|| Solved Sudoku Grid ||---\n";
        printGrid(grid);
    } else {
        cout << "No solution exists for the given puzzle.\n";
    }
    return 0;
}
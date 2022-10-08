// Solving Sudoku Using CPP And Backtracking
#include <bits/stdc++.h>
using namespace std;

// N is used for the size of Sudoku grid.
// Size will be NxN
#define N 9



/* Searches the grid to find an entry that is
still 0. If found, the reference
parameters row, col will be set the location
that is 0, and true is returned.
If no 0 entries remain, false is returned. */
bool Find0Location(int grid[N][N], int& row, int& col) {
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == 0)
                return true;
    return false;
}
 
/* Returns a boolean which indicates whether
an assigned entry in the specified row matches
the given number. */
bool UsedInRow(int grid[N][N], int row, int num)
{
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}
 
/* Returns a boolean which indicates whether
an assigned entry in the specified column
matches the given number. */
bool UsedInCol(int grid[N][N], int col, int num)
{
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}
 
/* Returns a boolean which indicates whether
an assigned entry within the specified 3x3 box
matches the given number. */
bool UsedInBox(int grid[N][N], int boxStartRow,
               int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row + boxStartRow]
                    [col + boxStartCol] ==
                                       num)
                return true;
    return false;
}
 
/* Returns a boolean which indicates whether
it will be legal to assign num to the given
row, col location. */
bool isSafe(int grid[N][N], int row,
            int col, int num)
{
    /* Check if 'num' is not already placed in
    current row, current column
    and current 3x3 box */
    return !UsedInRow(grid, row, num)
           && !UsedInCol(grid, col, num)
           && !UsedInBox(grid, row - row % 3,
                         col - col % 3, num)
           && grid[row][col] == 0;
}
 
/* A utility function to print grid */
void printGrid(int grid[N][N])
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
            cout << grid[row][col] << " ";
        cout << endl;
    }
}
 





/* Takes a partially filled-in grid and attempts
to assign values to all 0 locations in
such a way to meet the requirements for
Sudoku solution (non-duplication across rows,
columns, and boxes) */
bool SolveSudoku(int grid[N][N]) {
    int row, col;

    // Check If A Solution Has Been Found
    if (!Find0Location(grid, row, col)) {
        return true;
    }

    // Guess Numbers Starting At 1 Increasing To 9
    for (int num = 1; num <= 9; num++) {
        // Determine If Our Guess Is Valid
        if (isSafe(grid, row, col, num)) {
            // Temporarily Input Our Safe Guess
            grid[row][col] = num;

            // If All Spaces Are Filled Then We have The Solution
            if (SolveSudoku(grid)) {
                return true;
            }

            // By This Point Then Our Guess Was Wrong
            grid[row][col] = 0;
        }
    }

    return false;
}

int main() {
    int grid[N][N] = {
        {3,0,6,5,0,8,4,0,0},
        {5,2,0,0,0,0,0,0,0},
        {0,8,7,0,0,0,0,3,1},
        {0,0,3,0,1,0,0,8,0},
        {9,0,0,8,6,3,0,0,5},
        {0,5,0,0,9,0,6,0,0},
        {1,3,0,0,0,0,2,5,0},
        {0,0,0,0,0,0,0,7,4},
        {0,0,5,2,0,6,3,0,0}
    };

    if (SolveSudoku(grid) == true) {
        printGrid(grid);
    }
    else {
        cout << "No solution exists";
    }
 
    return 0;
}
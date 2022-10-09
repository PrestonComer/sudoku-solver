// Solving Sudoku Using CPP And Backtracking
// #include <bits/stdc++.h>
#include <iostream>
#include <string>

// N Is The Size Of Sudoku Puzzle.
#define N 9

// Determines Where The First Blank Is In The Sudoku Puzzle
// From Top Left To Bottom Right
bool findBlankEntry(int puzzle[N][N], int& row, int& col) {
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (puzzle[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

// Determine If The Guess Is Already In The Current Row
bool inRow(int puzzle[N][N], int row, int guess) {
    for (int col = 0; col < N; col++) {
        if (puzzle[row][col] == guess) {
            return true;
        }
    }
    return false;
}

// Determine If The Guess Is Already In The Current Column
bool inCol(int puzzle[N][N], int col, int guess) {
    for (int row = 0; row < N; row++) {
        if (puzzle[row][col] == guess) {
            return true;
        }
    }
    return false;
}

// Determine If The Guess Is Already In The Current Box
bool inBox(int puzzle[N][N], int boxRow, int boxCol, int guess) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (puzzle[row + boxRow][col + boxCol] == guess) {
                return true;
            }
        }
    }
    return false;
}

// Determines If The Guess Is Valid
bool isSafe(int puzzle[N][N], int row, int col, int guess) {
    if (!inRow(puzzle, row, guess)) {
        return true;
    }
    if (!inCol(puzzle, row, guess)) {
        return true;
    }
    if (!inBox(puzzle, row - row % 3, col - col % 3, guess)) {
        return true;
    }
    if (!puzzle[row][col] == 0) {
        return true;
    }
    return false;
}

// Display Sudoku Puzzle
void displayPuzzle(int puzzle[N][N]) {
    for (int row = 0; row < N; row++) {
        if (row % 3 == 0) {
            for (int count = 0; count < 25; count++) {
                std::cout << "-";
            }
            std::cout << std::endl;
        }

        for (int col = 0; col < N; col++) {
            if (col % 3 == 0) {
                std::cout << "| ";
            }

            std::cout << puzzle[row][col];

            if (col != (N - 1)) {
                std::cout << " ";
            }
        }
        std::cout << " |" << std::endl;
    }
    for (int count = 0; count < 25; count++) {
        std::cout << "-";
    }
    std::cout << std::endl;
}

// Solve Given Partially Correct Sudoku Puzzle
bool findSolution(int puzzle[N][N]) {
    int row, col;

    // Check If A Solution Has Been Found
    if (!findBlankEntry(puzzle, row, col)) {
        return true;
    }

    // Make Guesses Starting At 1 Increasing To 9
    for (int guess = 1; guess <= 9; guess++) {
        // Determine If Our Guess Is Valid
        if (isSafe(puzzle, row, col, guess)) {
            // Temporarily Input Our Safe Guess
            puzzle[row][col] = guess;

            // If All Spaces Are Filled Then We have The Solution
            if (findSolution(puzzle)) {
                return true;
            }

            // By This Point Then Our Guess Was Wrong
            puzzle[row][col] = 0;
        }
    }

    return false;
}

int main() {
    int puzzle[N][N], rowNum = 0, pos, completePuzzleGiven = 1;
    std::string token, userInput = "", x;

    // Create a sudoku puzzle
    std::cout << "Please Enter Your Puzzle By Row Without Spaces In The Format #########" << std::endl;

    // get the puzzle row by row
    for (int row = 0; row < N; row++) {
        // get a row of the puzzle
        std::cout << "Input Puzzle Row " << row+1 << ": "; std::cin >> x;

        // the inputed row has to have N size
        if (x.length() != N) {
            std::cout << "Incorrect Input Size. Please Try Again" << std::endl;
            row--;
        } else {
            userInput.append(x + " ");
            std::cout << userInput << std::endl;
        }
    };

    // take the one space deliminated string and put it in the NxN array
    while ((pos = userInput.find(" ")) != std::string::npos) {
        token = userInput.substr(0, pos);

        for (int i = 0; i < token.length(); i++) {
            puzzle[rowNum][i] = std::stoi(std::string(1, token[i]));
            if (token[i] == '0') {
                completePuzzleGiven = 0;
            }
        }
        rowNum++;
        userInput.erase(0, pos + 1);
    }

    // display the given puzzle
    std::cout << "Starting Puzzle:" << std::endl;
    displayPuzzle(puzzle);
    std::cout << std::endl;

    // attempt to solve puzzle 
    // either display the solution, that the given puzzle was already completed, or
    // that there is no solution possible
    if (findSolution(puzzle) == true) {
        std::cout << "Puzzle Solution:" << std::endl;
        displayPuzzle(puzzle);
    } else if (completePuzzleGiven) {
        std::cout << "Given Puzzle Has No Blank Spaces";
    } else {
        std::cout << "No Solution Exists";
    }

    // keep the program open for user to view
    char pause; std::cin >> pause;
    return 0;
}
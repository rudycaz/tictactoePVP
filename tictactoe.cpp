#include <iostream>
#include <vector>
#include <iomanip>
#include <limits> // For std::numeric_limits

using namespace std;

// Function to print the Tic Tac Toe board
void printBoard(const vector<vector<char> >& board) {
    cout << "\n";
    for (int i = 0; i < 3; ++i) {
        cout << "  ";
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j < 2)
                cout << " | ";
        }
        if (i < 2)
            cout << "\n ---|---|---\n";
    }
    cout << "\n";
}

// Function to check if a player has won
bool checkWin(const vector<vector<char> >& board, char player) {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if (
            (board[i][0] == player && board[i][1] == player && board[i][2] == player) || // Row
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)    // Column
            )
            return true;
    }
    // Check diagonals
    if (
        (board[0][0] == player && board[1][1] == player && board[2][2] == player) || // Main diagonal
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)    // Anti-diagonal
        )
        return true;

    return false;
}

// Function to check if the game is a draw
bool checkDraw(const vector<vector<char> >& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == ' ')
                return false;
        }
    }
    return true;
}

// Function to play Tic Tac Toe
void playTicTacToe() {
    vector<vector<char> > board(3, vector<char>(3, ' ')); // Initialize an empty board
    char currentPlayer = 'X';
    bool gameActive = true;

    cout << "Welcome to Tic Tac Toe!\n";
    cout << "Players take turns entering row and column numbers (1-3).\n";

    while (gameActive) {
        printBoard(board);
        int row, col;

        // Input loop for valid move
        while (true) {
            cout << "Player " << currentPlayer << ", enter your move (row and column): ";
            cin >> row >> col;

            // Check for input failure (non-integer input)
            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input! Please enter numbers between 1 and 3.\n";
                continue;
            }

            // Adjust indices (user enters 1-3, but vector indices are 0-2)
            row -= 1;
            col -= 1;

            // Check if the input is within bounds and the cell is empty
            if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
                break; // Valid input
            } else {
                cout << "Invalid move! The cell is either occupied or out of bounds. Try again.\n";
            }
        }

        // Place the player's move on the board
        board[row][col] = currentPlayer;

        // Check if the current player has won
        if (checkWin(board, currentPlayer)) {
            printBoard(board);
            cout << "Player " << currentPlayer << " wins!\n";
            gameActive = false;
            continue;
        }

        // Check if the game is a draw
        if (checkDraw(board)) {
            printBoard(board);
            cout << "It's a draw!\n";
            gameActive = false;
            continue;
        }

        // Switch player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

int main() {
    playTicTacToe();
    return 0;
}
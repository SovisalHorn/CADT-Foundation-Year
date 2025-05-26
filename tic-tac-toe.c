#include <stdbool.h>
#include <stdio.h>

#define GAME_SIZE 5 // Game row and columns
#define WIN_COUNT 4 // Number of symbols needed to win
#define PLAYER_1_SYMBOL 'X'
#define PLAYER_2_SYMBOL 'O'
#define EMPTY_SYMBOL '.'
#define PLAYER_1_WON 1
#define PLAYER_2_WON 2
#define DRAW_GAME 0
#define ONGOING_GAME 3

// Global board
char board[5][5] = {
    {'.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.'}
};

// Function declarations
int checkGame();
int horizontalWin();
int verticalWin();
int diagonalWin();
bool isValidMove(int row, int col);
bool makeMove(int row, int col, bool player1);
void displayBoard();
bool isBoardFull();
void declareWinner(int results);

// Main function
int main() {
    printf("\nTic-Tac-Toe (5x5, 4 to win)\n");
    displayBoard();
    int row, col;
    bool isPlayer1 = true;
    int result;
    do{
        printf("\nPlayer %d's turn:\n", isPlayer1 ? 1 : 2);
        printf("Enter row (0-4): ");
        scanf("%d", &row);
        if(row > 4)  row = 4;
        printf("Enter col (0-4): ");
        scanf("%d", &col);
        if(col > 4) col = 4;
        
        if(isValidMove(row,col)) {
            makeMove(row, col, isPlayer1);
        }
        else {
            printf("Cannot use this row/col , select it agian");
            printf("\nPlayer %d's turn:\n", isPlayer1 ? 1 : 2);
            printf("Enter row (0-4): ");
            scanf("%d", &row);
            printf("Enter col (0-4): ");
            scanf("%d", &col);
        }

        displayBoard();
        result = checkGame();
        isPlayer1 = !isPlayer1; // Switch player
    } while(result == ONGOING_GAME);

    declareWinner(result);

    return 0;
}

int checkGame() {
    int verticalWinner = verticalWin();
    int horizontalWinner = horizontalWin();
    int diagonalWinner = diagonalWin();

    if (verticalWinner == PLAYER_1_WON || horizontalWinner == PLAYER_1_WON || diagonalWinner == PLAYER_1_WON) {
        return PLAYER_1_WON;
    }
    if (verticalWinner == PLAYER_2_WON || horizontalWinner == PLAYER_2_WON || diagonalWinner == PLAYER_2_WON) {
        return PLAYER_2_WON;
    }
    if (isBoardFull() == 1){
        return DRAW_GAME;
    }
    return ONGOING_GAME;
}

int verticalWin() {
    for (int col = 0; col < GAME_SIZE; col++) {
        int countX = 0;
        int countO = 0;
        for (int row = 0; row < GAME_SIZE; row++) {
            if (board[row][col] == PLAYER_1_SYMBOL) {
                countX++;
            } else if (board[row][col] == PLAYER_2_SYMBOL) {
                countO++;
            }
        }
        if (countX >= WIN_COUNT) return PLAYER_1_WON;
        else if (countO >= WIN_COUNT) return PLAYER_2_WON;
    }
    return ONGOING_GAME;
}

int horizontalWin() {
    for (int row = 0; row < GAME_SIZE; row++) {
        int countX = 0;
        int countO = 0;
        for (int col = 0; col < GAME_SIZE; col++) {
            if (board[row][col] == PLAYER_1_SYMBOL) {
                countX++;
            } else if (board[row][col] == PLAYER_2_SYMBOL) {
                countO++;
            }
        }
        if (countX >= WIN_COUNT) return PLAYER_1_WON;
        else if (countO >= WIN_COUNT) return PLAYER_2_WON;
    }
    return ONGOING_GAME;
}

int diagonalWin() {
    int countX[2] = {0};
    int countO[2] = {0};

    for (int i = 0; i < GAME_SIZE; i++) {
        // Main diagonal (top-left to bottom-right)
        if (board[i][i] != EMPTY_SYMBOL) {
            if (board[i][i] == PLAYER_1_SYMBOL) {
                countX[0]++;
            } else if (board[i][i] == PLAYER_2_SYMBOL) {
                countO[0]++;
            }
        }
        // Anti-diagonal (top-right to bottom-left)
        if (board[i][GAME_SIZE - i - 1] != EMPTY_SYMBOL) {
            if (board[i][GAME_SIZE - i - 1] == PLAYER_1_SYMBOL) {
                countX[1]++;
            } else if (board[i][GAME_SIZE - i - 1] == PLAYER_2_SYMBOL) {
                countO[1]++;
            }
        }
    }

    if (countX[0] >= WIN_COUNT || countX[1] >= WIN_COUNT) return PLAYER_1_WON;
    else if (countO[0] >= WIN_COUNT || countO[1] >= WIN_COUNT) return PLAYER_2_WON;
    return ONGOING_GAME;
}

void displayBoard() {
    printf("\n");
    for (int i = 0; i < GAME_SIZE; i++) {
        for (int j = 0; j < GAME_SIZE; j++) {
            printf("%c  ", board[i][j]);
        }
        printf("\n");
    }
}

bool isValidMove(int row, int col) {
    if (board[row][col] == EMPTY_SYMBOL) {
        return true;
    }
    return false;
}

bool makeMove(int row, int col, bool isPlayer1) {
    if (isValidMove(row, col)) {
        board[row][col] = isPlayer1 ? PLAYER_1_SYMBOL : PLAYER_2_SYMBOL;
        return true;
    }
    return false;
}

bool isBoardFull() {
    for (int i = 0; i < GAME_SIZE; i++) {
        for (int j = 0; j < GAME_SIZE; j++) {
            if (board[i][j] == EMPTY_SYMBOL) {
                return false;
            }
        }
    }
    return true;
}

void declareWinner(int results){
    if(results == PLAYER_1_WON){
        printf("Player 1 (%c) has won!\n", PLAYER_1_SYMBOL);
    }
    else if(results == PLAYER_2_WON){
        printf("Player 1 (%c) has won!\n", PLAYER_1_SYMBOL);
    }
    else{
        printf("It is a draw");
    }
}
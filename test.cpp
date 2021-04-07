#include <iostream>

int boardResult(int board[9]) {
    int sum;
    for (int i=0; i<3; i++) {
        // line
        sum = 0;
        for (int j=0; j<3; j++)
            sum += board[i*3 + j];
        if (abs(sum) == 3) { return (sum > 0)? 1 : -1; }
        // column
        sum = 0;
        for (int j=0; j<3; j++)
            sum += board[j*3 + i];
        if (abs(sum) == 3) { return (sum > 0)? 1 : -1; }
    }
    // principal diagonal
    sum = board[0] + board[4] + board[8];
    if (abs(sum) == 3) { return (sum > 0)? 1 : -1; }
    // secoundary diagonal
    sum = board[2] + board[4] + board[6];
    if (abs(sum) == 3) { return (sum > 0)? 1 : -1; }
    // none
    return 0;
}

void printBoard(int board[9]) {
    char c;
    for (int i=0; i<3; i++) {
        printf("| ");
        for (int j=0; j<3; j++) {
            switch (board[i*3 + j]) {
                case 0:
                    c = ' ';
                    break;
                case 1:
                    c = 'X';
                    break;
                case -1:
                    c = 'O';
                    break;
                default:
                    c = 48 + 5 + board[i*3 + j];
            }
            printf("%c | ", c);
        }
        printf("\n");
    }
}

int askPlayer(int board[9]) {
    int line, column, pos;
    do {
        printf("Enter your line column (0..2 0..2): ");
        scanf("%d %d", &line, &column);
        pos = (line * 3 + column);
    } while (line > 2 || line < 0 || column > 2 || column < 0 || board[pos] != 0);
    return pos;
}

int minimax(int board[9], int currPlayerTurn) {
    int winner = boardResult(board);
    if (winner != 0) return winner;
    //
    int move = -1;
    int bestScore = 0;
    int score, pos;
    //
    for (pos=0; pos < 9; pos++) {
        if (board[pos] == 0) {    // Empty espace
            board[pos] = currPlayerTurn;
            score = -minimax(board, -currPlayerTurn);
            if (score > bestScore) {
                bestScore = score;
                move = pos;
            }
            board[pos] = 0;     // Reset change to the board after testing
        }
    }
    return bestScore;
}

int askAi(int board[9]) {
    int currPlayerTurn = -1;    // -1 for IA's turn
    int move = -1;
    int bestScore = -2; // Losing is preferred than not moving
    int score, pos;

    for (pos=0; pos<9; pos++) {
        if (board[pos] == 0) {    // Empty espace
            board[pos] = currPlayerTurn;
            score = -minimax(board, currPlayerTurn);
            if (score > bestScore) {
                bestScore = score;
                move = pos;
            }
            board[pos] = 0;     // Reset change to the board after testing
        }
    }

    return move;
}

int main() {
    int board[9] = {0, 0, 0,
                    0, 0, 0,
                    0, 0, 0};

    int playerTurn;
    do {
        printf("Do you wanna play 1st or 2nd (1 or 2): ");
        scanf("%d", &playerTurn);
    } while (playerTurn < 1 || playerTurn > 2);
    playerTurn -= 1;

    printBoard(board);

    int winner = 0;
    for (int turn=0; turn<9 && winner == 0; turn++) {
        if (turn%2 == playerTurn) {
            // player always plays 1 = X
            board[askPlayer(board)] = 1;
        } else {
            // ia always plays -1 = O
            printf("IA's turn\n");
            board[askAi(board)] = -1;
        }
        printBoard(board);
        //
        winner = boardResult(board);
        // printf("winner: %d\n", winner);
        if (winner != 0) break;
    }

    switch (winner) {
        case 0:
            printf("Draw\n");
            break;
        case 1:
            printf("You won :)\n");
            break;
        case -1:
            printf("You lost :(\n");
            break;
    }

    return 0;
}

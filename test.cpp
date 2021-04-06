#include <iostream>

int board[9];

int boardResult() {
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

void printBoard() {
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

int askPlayer() {
    int line, column, pos;
    do {
        printf("Enter your line column (0..2 0..2): ");
        scanf("%d %d", &line, &column);
        pos = (line * 3 + column);
    } while (line > 2 || line < 0 || column > 2 || column < 0 || board[pos] != 0);
    return pos;
}

int minimax(int board[9], ) {

}

int askAi() {
    int line, column, pos;
    do {
        printf("Bot: ");
        scanf("%d %d", &line, &column);
        pos = (line * 3 + column);
    } while (line > 2 || line < 0 || column > 2 || column < 0 || board[pos] != 0);
    return pos;
}

int main() {
    int playerTurn;
    do {
        printf("Do you wanna play 1st or 2nd (1 or 2): ");
        scanf("%d", &playerTurn);
    } while (playerTurn < 1 || playerTurn > 2);
    playerTurn -= 1;

    printBoard();

    int winner = 0;
    for (int turn=0; turn<9 && winner == 0; turn++) {
        if (turn%2 == playerTurn) {
            // X = 1st      O = 2nd
            board[askPlayer()] = 1;
        } else {
            printf("IA's turn\n");
            board[askAi()] = -1;
        }
        printGrid();
        //
        winner = boardResult();
        printf("winner: %d\n", winner);
        if (winner != 0) { break; }
    }

    switch (winner) {
        case 0:
            printf("Draw\n");
            break;
        case 1:
            printf("You win :)\n");
            break;
        case -1:
            printf("You lose :(\n");
            break;
    }

    return 0;
}

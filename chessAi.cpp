#include <cstdio>

#define byte unsigned char

#define PAWN    1
#define ROOK    2
#define KNIGHT  4
#define BISHOP  8
#define QUEEN   16
#define KING    32
#define WHITE   64
#define BLACK   128

char pieceChar(byte *piece) {
    switch (*piece) {
        case PAWN   | WHITE: return 'p';
        case ROOK   | WHITE: return 'r';
        case KNIGHT | WHITE: return 'k';
        case BISHOP | WHITE: return 'b';
        case QUEEN  | WHITE: return 'q';
        case KING   | WHITE: return 'w';
        case PAWN   | BLACK: return 'P';
        case ROOK   | BLACK: return 'R';
        case KNIGHT | BLACK: return 'K';
        case BISHOP | BLACK: return 'B';
        case QUEEN  | BLACK: return 'Q';
        case KING   | BLACK: return 'W';
    }
    return '-';
}

void printBoard(byte* board) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            printf(" %c |", pieceChar(&board[i*8 + j]));
        }
        printf("\n");
    }
}

void printb(byte b) {
    for (int i=0; i<8; i++) {
        printf("%d", (b >= 128));
        b <<= 1;
    }
    printf("\n");
}

int main(int argc, char const *argv[]) {

    byte board[64];
    for (int i=0; i<64; i++) {
        board[i] = 0;
    }

    byte piecesLineUp[] = {ROOK, KNIGHT, BISHOP, KING, QUEEN, BISHOP, KNIGHT, ROOK};
    for (int i=0; i<8; i++) {
        board[i]        = piecesLineUp[i] | WHITE;
        board[64-8 +i]  = piecesLineUp[i] | BLACK;
        // PAWNs
        board[8 + i]    = PAWN | WHITE;
        board[64-16 +i] = PAWN | BLACK;
    }

    printBoard(board);

    return 0;
}

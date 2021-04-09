#include <cstdio>
#include <time.h>

#define byte unsigned char
#define ulint unsigned long int

#define PAWN    1
#define ROOK    2
#define KNIGHT  4
#define BISHOP  8
#define QUEEN   16
#define KING    32
#define WHITE   64
#define BLACK   128

#define PAWN_POINTS     1
#define ROOK_POINTS     5
#define KNIGHT_POINTS   3
#define BISHOP_POINTS   3
#define QUEEN_POINTS    9
#define KING_POINTS     99

ulint white_pawns   = 0;
ulint white_rooks   = 0;
ulint white_knights = 0;
ulint white_bishops = 0;
ulint white_queens  = 0;
ulint white_king    = 0;
ulint black_pawns   = 0;
ulint black_rooks   = 0;
ulint black_knights = 0;
ulint black_bishops = 0;
ulint black_queens  = 0;
ulint black_king    = 0;

char pieceChar(byte *piece) {
    switch (*piece) {
        case PAWN   | WHITE: return 'p';
        case ROOK   | WHITE: return 'r';
        case KNIGHT | WHITE: return 'n';
        case BISHOP | WHITE: return 'b';
        case QUEEN  | WHITE: return 'q';
        case KING   | WHITE: return 'k';
        case PAWN   | BLACK: return 'P';
        case ROOK   | BLACK: return 'R';
        case KNIGHT | BLACK: return 'N';
        case BISHOP | BLACK: return 'B';
        case QUEEN  | BLACK: return 'Q';
        case KING   | BLACK: return 'K';
    }
    return '-';
}


void printb(byte b) {
    for (int i=0; i<8; i++) {
        printf("%d", (b >= 128));
        b <<= 1;
    }
    printf("\n");
}

void printlb(ulint b) {
    char text[65] = "";
    ulint mask = 1;
    for (int i=0; i<64; i++) {
        text[63-i] = (b & mask)? '1' : '0';
        mask <<= 1;
    }
    printf("%s\n", text);
}

// if-less
void getPositionFromOneHot(ulint *piece, int positions[]) {
    int amount = 0;
    int curr;
    for (int i=0; i<64; i++) {
        curr = (1 & (*piece >> i));
        positions[amount] = (i * curr);
        amount += curr;
    }
}

int positions[16];
void printBoard() {
    char board[64];
    for (i=0; i<64; i++)
        board[i] = '-';

    int i;

        // for (i=0; i<8; i++) {
            //     printf("|");
            //     for (int j=0; j<8; j++) {
                //         printf(" %d |", i*8 + j);
                //     }
                //     printf("\n");
                // }
                // printf("\n");

    getPositionFromOneHot(&white_pawns, &positions[0]);
    getPositionFromOneHot(&black_pawns, &positions[8]);
    for (i=0; i<8; i++) {
        board[positions[i]] = 'p';
        board[positions[i+8]] = 'P';
    }
    //
    getPositionFromOneHot(&white_rooks,   &positions[0]);
    getPositionFromOneHot(&black_rooks,   &positions[2]);
    getPositionFromOneHot(&white_knights, &positions[4]);
    getPositionFromOneHot(&black_knights, &positions[6]);
    getPositionFromOneHot(&white_bishops, &positions[8]);
    getPositionFromOneHot(&black_bishops, &positions[10]);
    for (i=0; i<2; i++) {
        board[positions[i]]     = 'r';
        board[positions[i+2]]   = 'R';
        board[positions[i+4]]   = 'n';
        board[positions[i+6]]   = 'N';
        board[positions[i+8]]   = 'b';
        board[positions[i+10]]  = 'B';
    }
    //
    getPositionFromOneHot(&white_queens, &positions[0]);
    getPositionFromOneHot(&black_queens, &positions[1]);
    board[positions[0]]  = 'q';
    board[positions[1]]  = 'Q';
    getPositionFromOneHot(&white_king, &positions[0]);
    getPositionFromOneHot(&black_king, &positions[1]);
    board[positions[0]] = 'k';
    board[positions[1]] = 'K';
    // print
    for (i=7; i>=0; i--) {
        printf("|");
        for (int j=0; j<8; j++) {
            printf(" %c |", board[i*8 + j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printlbBoard(ulint b) {
    char text[65] = "";
    // text[65] = '\0';
    ulint mask = 1;
    for (int i=0; i<64; i++) {
        text[63-i] = (b & mask)? '1' : '0';
        mask <<= 1;
    }
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            printf("%c", text[i*8 + j]);
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[]) {
    ulint mask = 1;

    // pawns
    for (int i=8; i<16; i++) {
        white_pawns |= mask << i;
        black_pawns |= mask << (63 - i);
    }
    printf("pawns\n");
    printlb(white_pawns);
    printlb(black_pawns);

    // rooks
    mask = 1;
    white_rooks |= mask | (mask << 7);
    black_rooks |= (mask << 63) | (mask << 56);
    printf("rooks\n");
    printlb(white_rooks);
    printlb(black_rooks);

    // knights
    mask = 1;
    white_knights |= (mask << 1)  | (mask << 6);
    black_knights |= (mask << 62) | (mask << 57);
    printf("knights\n");
    printlb(white_knights);
    printlb(black_knights);

    // bishops
    mask = 1;
    white_bishops |= (mask << 2)  | (mask << 5);
    black_bishops |= (mask << 61) | (mask << 58);
    printf("bishops\n");
    printlb(white_bishops);
    printlb(black_bishops);

    // queens
    mask = 1;
    white_queens |= (mask << 4);
    black_queens |= (mask << 59);
    printf("queens\n");
    printlb(white_queens);
    printlb(black_queens);

    // kings
    mask = 1;
    white_king |= (mask << 3);
    black_king |= (mask << 60);
    printf("kings\n");
    printlb(white_king);
    printlb(black_king);

    printBoard();


    return 0;
}

#ifndef _CHESS_PIECE_
#define _CHESS_PIECE_

typedef struct Piece {
    int val;
    int pos;
    int id;
    int moved; // for pawn
    int side; // black or white
} Piece;

#endif
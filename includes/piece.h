#ifndef _CHESS_PIECE_
#define _CHESS_PIECE_

typedef struct Piece_move {
    int n_row;
    int n_col;
    int is_line;
} Piece_move;

typedef struct Piece {
    int val;
    int row;
    int col;
    int id;
    int side;
    Piece_move *moves;
} Piece;

#endif
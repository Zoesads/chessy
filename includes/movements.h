#ifndef _CHESS_MOVEMENTS_
#define _CHESS_MOVEMENTS_

#include <piece.h>
void GenerateMoves(Piece board[64], int moves[64], Piece piece);
int get_Index(char col, char row);

#endif
#ifndef _CHESS_MOVEMENTS_
#define _CHESS_MOVEMENTS_
#include <piece.h>

void GenerateMoves(int moves[64], Piece piece);
int get_Index(char col, char row);

#endif
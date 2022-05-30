#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#include <piece.h>
#include <printer.h>
#include <notation.h>
#include <movements.h>

void create_Board(Piece board[64], char FEN[], int length) {
    int _=-1, c=0;
    while (_ < length) {
        _++;
        if ((FEN[_]=='/'))
            continue;
        if (isdigit(FEN[_])) {
            int n = FEN[_]-'0';
            for (int i=0; i<n; i++) {
                Piece *p = &board[c+i];
                p-> pos = c+i;
                p->id = -1;
            }
            c+=n;
            continue;
        };
        Piece *p = &board[c];
        p->side = !isupper(FEN[_]);
        p->pos = c;
        int t = tolower(FEN[_]);
        switch (t) {
            case 'p':
                p->moved = 0;
                p->id = PAWN;
                break;
            case 'b':
                p->id = BISHOP;
                break;
            case 'n':
                p->id = KNIGHT;
                break;
            case 'r':
                p->id = ROOK;
                break;
            case 'q':
                p->id = QUEEN;
                break;
            case 'k':
                p->id = KING;
                break;
        }
        c++;
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    chessy_welcome();
    int moves[64];
    char FEN[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    Piece board[64];
    create_Board(board, FEN, strlen(FEN));
    chessy_gameboard(board, 0, -1);
    ComputeMoves(moves, board[4]);
    return 0;
}
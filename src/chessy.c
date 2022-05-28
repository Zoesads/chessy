#include <stdio.h>
#include <piece.h>
#include <printer.h>
#include <notation.h>
#include <ctype.h>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    chessy_welcome();
    Piece board[64];
    char FEN[] = "rnbkqbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBKQBNR";
    int _=-1, __=sizeof(FEN)/sizeof(char)-2, c=0;
    while (_ < __) {
        _++;
        if ((FEN[_]=='/'))
            continue;
        if (isdigit(FEN[_])) {
            int n = FEN[_]-'0';
            for (int i=0; i<n; i++) {
                Piece *p = &board[c+i];
                p->id = -1;
            }
            c+=n;
            continue;
        };
        Piece *p = &board[c];
        p->side = isupper(FEN[_]);
        p->id = -2;
        int t = tolower(FEN[_]);
        switch (t) {
            case 'p':
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
    chessy_gameboard(board, 0, -1);
    return 0;
}
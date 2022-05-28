#include <stdio.h>
#include <piece.h>
#include <printer.h>
#include <notation.h>
#include <ctype.h>

int main() {
    chessy_welcome();
    Piece board[8][8];
    char FEN[] = "rnbkqbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBKQBNR";
    int _=-1, __=sizeof(FEN)/sizeof(char)-2, c=0, r=0;
    while (_ < __) {
        _++;
        if ((FEN[_]=='/')||!((c+1)%8)){
            r++;
            c=0;
            continue;
        }
        if (isdigit(FEN[_])) {
            int n = FEN[_]-'0';
            for (int i=0; i<n; i++) {
                Piece p;
                p.id = -1;
                board[c+i][r] = p;
            }
            c=n-1;
            continue;
        };
        Piece p;
        p.side = isupper(FEN[_]);
        int t = tolower(FEN[_]);
        switch (t) {
            case 'p':
                p.id = PAWN;
                break;
            case 'b':
                p.id = BISHOP;
                break;
            case 'n':
                p.id = KNIGHT;
                break;
            case 'r':
                p.id = ROOK;
                break;
            case 'q':
                p.id = QUEEN;
                break;
            case 'k':
                p.id = KING;
                break;
        }
        board[r][c] = p;
    }
    chessy_gameboard(board, 0, -1, -1);
    return 0;
}
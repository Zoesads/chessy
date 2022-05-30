#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#include <piece.h>
#include <printer.h>
#include <notation.h>
#include <movements.h>

int turn = WHITE_SIDE;
int winner = -1;
int s64i = sizeof(int)<<6;
int moves[64];
int selc[64];
int mode = MODE_IDLE;
int pIdx =-1;
Piece board[64];
char FEN[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

void create_Board(Piece board[64], char FEN[], int length) {
    int _=-1, c=0;
    while (_ < length) {
        _++;
        if (FEN[_]=='/')
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
        p->side = !islower(FEN[_]);
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
void output_board() {chessy_gameboard(board, mode, moves, selc);}

int main() {

    memset(moves, 0, s64i);
    memset(selc, 0, s64i);
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    chessy_welcome();
    create_Board(board, FEN, strlen(FEN));
    output_board();

    while (winner==-1) {
        char inp[4];
        inp[3] = '\0';
        printf("%s@ChessyPlayer  >>  ", turn==WHITE_SIDE?"WHITE":"BLACK");
        scanf("%2s", inp);
        int n = strlen(inp);
        if (n>0) {
            int idx = n==2?get_Index(inp[0], inp[1]):-1;
            if (mode==MODE_SELC&&idx!=-1) {
                if (pIdx!=-1){
                    turn = !turn;
                    pIdx = -1;
                    mode = MODE_IDLE;
                    memset(moves, 0, s64i);
                    continue;
                }
                pIdx = idx;
                GenerateMoves(moves, board[idx]);
                memcpy(selc, moves, s64i);
                selc[idx] = 2;
                output_board();
                continue;
            }
            switch ((int)inp[0]) {
                case 's': { // select mode
                    if (mode != MODE_SELC) {
                        mode = MODE_SELC;
                        for (int i = 0; i < 64; i++)
                            selc[i] = (board[i].id>-1?2*(board[i].side!=turn):0);
                    } else {
                        mode = MODE_IDLE;
                        memset(selc, 0, s64i);
                        pIdx = -1;
                    }
                    output_board();
                    break;
                }
                case 'u': { // undo
                    pIdx = -1;
                    memset(moves, 0, s64i);
                    memset(selc, 0, s64i);
                    output_board();
                    break;
                }
                case 'q': { // quit game
                    winner = 69;
                    break;
                }

            }
        }
    }

    return 0;
}
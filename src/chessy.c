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
                p->side = -1;
                p->id = EMPTY;
            }
            c+=n;
            continue;
        };
        Piece *p = &board[c];
        p->side = !islower(FEN[_])?WHITE_SIDE:BLACK_SIDE;
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
        char inp[6];
        inp[5] = '\0';
        printf("csp@plr: ~/Chessy/%s $ ", turn==WHITE_SIDE?"WHITE":"BLACK");
        scanf("%5s", inp);
        int n = strlen(inp);
        if (n>0) {
            int idx[2] = {-1, -1};
            idx[0] = n==2?get_Index(inp[0], inp[1]):-1;
            idx[1] = (n==5&&inp[2] == ' ')?get_Index(inp[3], inp[4]):-1;

            if (pIdx == -1 && idx[0]!=-1 && board[idx[0]].side == turn) {
                pIdx = idx[0];
                mode = MODE_SELC;
                GenerateMoves(board, moves, board[pIdx]);
                if(idx[1]==-1) {
                    memcpy(selc, moves, s64i);
                    selc[idx[0]] = 2;
                    output_board();
                }
                else continue;
            }

            if (pIdx!=-1&&((idx[1]!=-1&&pIdx!=idx[1])||(idx[0]!=-1&&pIdx!=idx[0]))){
                int ridx = idx[idx[1]!=-1];
                if (moves[ridx] == 1) {
                    int pos = board[ridx].pos;
                    board[pIdx].pos = pos;
                    board[ridx] = board[pIdx];
                    board[pIdx].side = -1;
                    board[pIdx].id = EMPTY;
                    turn = !turn;
                    pIdx = -1;
                    mode = MODE_IDLE;
                    memset(moves, 0, s64i);
                    memset(selc, 0, s64i);
                    output_board();
                }
                continue;
            }

            switch ((int)inp[0]) {
                case 'u': {
                    pIdx = -1;
                    memset(moves, 0, s64i);
                    memset(selc, 0, s64i);
                    output_board();
                    break;
                }
                case 'q': {
                    winner = 69;
                    break;
                }

            }
        }
    }

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <piece.h>
#include <printer.h>
#include <notation.h>
#include <movements.h>
#ifdef _WIN32
    #include <windows.h>
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

int turn = WHITE_SIDE;
int done = 0;
int s64i = sizeof(int)<<6;
int moves[64];
int selc[64];
int mode = MODE_IDLE;
Piece board[64];
char FEN[] = "8/4P3/8/8/8/8/8/8";

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
                p->moved = 0;
                p->id = ROOK;
                break;
            case 'q':
                p->id = QUEEN;
                break;
            case 'k':
                p->moved = 0;
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
    chessy_welcome();
    create_Board(board, FEN, strlen(FEN));
    output_board();

    while (!done) {
        char inp[3];
        inp[2] = '\0';
        printf("%s: ", turn==WHITE_SIDE?"WHITE":"BLACK");
        scanf("%2s", inp);
        int n = strlen(inp);
        if (n==2) {
            int idx[2] = {get_Index(inp[0], inp[1]), -1};

            while (idx[0]==-1||board[idx[0]].side!=turn){
                scanf("%2s", inp);
                if (strlen(inp)==2)
                    idx[0] = get_Index(inp[0], inp[1]);
            }
            mode = MODE_SELC;
            GenerateMoves(board, moves, board[idx[0]]);
            memcpy(selc, moves, s64i);
            selc[idx[0]] = 2;
            output_board();
            printf("Move to: ");

            while (idx[1]==-1){
                scanf("%2s", inp);
                if (strlen(inp)==2)
                    idx[1] = get_Index(inp[0], inp[1]);
            }
            if (idx[0]!=idx[1]){
                int ridx = idx[idx[1]!=-1];
                if (moves[ridx] == 1) {
                    int pos = board[ridx].pos;
                    board[idx[0]].pos = pos;
                    board[ridx] = board[idx[0]];
                    board[idx[0]].side = -1;
                    board[idx[0]].id = EMPTY;
                    turn = !turn;
                    mode = MODE_IDLE;
                    memset(moves, 0, s64i);
                    memset(selc, 0, s64i);
                    output_board();
                    if (board[ridx].id==PAWN&&((turn!=WHITE_SIDE&&pos>-1&&pos<8)||(turn!=BLACK_SIDE&&pos>54&&pos<64))) {
                        printf("Promote pawn to: \n  [1] = Queen\n  [2] = Rook\n  [3] = Bishop\n  [4] = Knight\n>> ");
                        int c = -1;
                        while (c<1||c>4)
                            scanf("%i", &c);
                        switch (c) {
                            case 1:
                                board[ridx].id = QUEEN;
                                break;
                            case 2:
                                board[ridx].id = ROOK;
                                break;
                            case 3:
                                board[ridx].id = BISHOP;
                                break;
                            case 4:
                                board[ridx].id = KNIGHT;
                                break;
                        }
                        output_board();
                    }
                    continue;
                }
            }
            printf("Unable to perform this move\n");
            continue;
        }
        if (n==1){
            switch ((int)inp[0]) {
                case 'q': {
                    done = 1;
                    break;
                }
                case 'r': {
                    done = 1;
                    printf("%s resigned. %s has won. GG!\n", turn==WHITE_SIDE?"White":"Black", turn==BLACK_SIDE?"White":"Black");
                    break;
                }
            }
        }
    }

    return 0;
}
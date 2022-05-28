#include <stdio.h>
#include <ctype.h>
#include <colorize.h>
#include <notation.h>
#include <piece.h>

char pieces_symbol[6][2][4] = {
    // WHITE - BLACK
    {"♙", "♟"},
    {"♗", "♝"},
    {"♘", "♞"},
    {"♖", "♜"},
    {"♕", "♛"},
    {"♔", "♚"}
};

void chessy_welcome() {
    printf("  Welcome to Chessy!\n");
    printf(" - A terminal chess -\n");
}

void chessy_about() {
    printf("About Chessy:\n");
    printf(" > A terminal chess\n");
    printf(" > Author: Zoesads\n");
    printf(" > Written in C\n");
    printf(" > Source code: https://github.com/Zoesads/chessy\n");
}

void chessy_gameboard(Piece board[64], int turn, int pos) {
    if (pos>=0&&board[pos].side!=turn) return;
    printf("\n\t");
    int r=0, c=0;
    for (int i = 0; i < 64; i++) {
        Piece p = board[i];
        printf("%s%s%s ", ((r%2)!=(c%2))?clr_bg_black:clr_bg_white, ((p.id==EMPTY)?" ":pieces_symbol[p.id][p.side%1]), clr_style_rset);
        c++;
        if (!((i+1)%8)){
            r++;
            c = 0;
            printf("\n\t");
        }
    }
    printf("%s", clr_style_rset);
}
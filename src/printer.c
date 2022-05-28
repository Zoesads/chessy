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

void chessy_gameboard(Piece board[8][8], int turn, int p_row, int p_col) {
    if (p_row>=1&&p_col>=1&&board[p_row][p_col].side!=turn) return;
    for (int col = 0; col < 8; col++) {
        for (int row = 0; row < 8; row++) {
            Piece p = board[row][col];
            printf("%s%s%s ", ((row==0)?"\t":""), ((p.id==EMPTY)?((((row+1)%2)!=((col+1)%2))?"■":"□"):pieces_symbol[p.id%5][p.side%1]), clr_style_rset);
        }
        printf("\n");
    }
    printf("%s", clr_style_rset);
}
#include <string.h>
#include <stdio.h>
#include <piece.h>
#include <notation.h>

void index2rc(int z[2], int index) {
    z[0] = index%8;
    z[1] = (index - z[0]) >> 3;
}

int get_Index(char col, char row) {
    if (col < 'a' || col > 'h' || row < '1' || row > '8')
        return -1;
    return ((8 - (row - '0'))<<3) + (col - 'a');
}

void GenerateMoves(Piece board[64], int moves[64], Piece piece) {
    int pid = piece.id;
    memset(moves, 0, sizeof(int)<<6);
    switch (pid) {
        case EMPTY:
            printf("what\n");
            break;
        case KING:{
            int pp = piece.pos;
            int k[2];
            // forked from bishop's
            int t = 1;
            index2rc(k, pp);
            for (int i = -1; i < 2 && t; i++) {
                int x = k[0]+i;
                if (i==0||x<0||x>7) continue;
                int y[2] = {k[1]+i, k[1]-i};
                for (int i = 0; i < 2; i++){
                    if (0<=y[i]&&y[i]<8&&board[(y[i]<<3)+x].side!=piece.side){
                        moves[(y[i]<<3)+x] = 1;
                        continue;
                    }
                    t = 0;
                    break;
                }
            } 
            // forked from rook's
            int dis[] = {7-k[0], 7-k[1], k[0], k[1]};
            int offset[4] = {1, 8, -1, -8};
            for (int i = 0; i < 4; i++) {
                for (int g = 1; g <= dis[i]; g++){
                    if (board[pp+offset[i]].side!=piece.side) {
                        moves[pp+offset[i]] = 1;
                        continue;
                    }
                    break;
                }
            }
            break;
        }
        case KNIGHT:{
            // forked from bishop's
            int j = piece.pos;
            int k[2];
            index2rc(k, j);
            for (int i = 1; i < 3; i++) {
                int x = k[0]+i;
                if (x<0||x>7) continue;
                int h = !((i+1)%2);
                int y[2] = {k[1]+1 + h, k[1]-1 - h};
                for (int i = 0; i < 2; i++) {
                    if (0<=y[i]&&y[i]<8&&board[(y[i]<<3)+x].side!=piece.side){
                        moves[(y[i]<<3)+x] = 1;
                        continue;
                    }
                }
            }
            for (int i = -1; i > -3; i--) {
                int x = k[0]+i;
                if (x<0||x>7) continue;
                int h = !((i+1)%2);
                int y[2] = {k[1]+1 + h, k[1]-1 - h};
                for (int i = 0; i < 2; i++) {
                    if (0<=y[i]&&y[i]<8&&board[(y[i]<<3)+x].side!=piece.side){
                        moves[(y[i]<<3)+x] = 1;
                        continue;
                    }
                }
            }
            break;
        }
        case PAWN: {
            int m = 1 + (piece.moved==0);
            int k = piece.side==BLACK_SIDE?1:-1;
            piece.moved = 1;
            for (int i = 1; i <= m; i++) {
                int z = piece.pos+((i*k)<<3);
                if (z<0||z>63||board[z].side==piece.side) break;
                moves[z] = 1;
            }
            break;
        }
        case ROOK: case QUEEN: case BISHOP: {
            int pp = piece.pos;
            int k[2];
            index2rc(k, pp);
            if (pid==ROOK||pid==QUEEN) {
                // east - south - west - north //
                int dis[] = {7-k[0], 7-k[1], k[0], k[1]};
                int offset[] = {1, 8, -1, -8};
                for (int i = 0; i < 4; i++) {
                    for (int g = 1; g <= dis[i]; g++){
                        if (board[pp+offset[i]*g].side!=piece.side) {
                            moves[pp+offset[i]*g] = 1;
                            continue;
                        }
                        break;
                    }
                }
            }
            if (pid==BISHOP||pid==QUEEN) {
                // expand inside -> out
                int t = 1;
                for (int i = -1; i > -9 && t; i--) {
                    int x = k[0]+i;
                    if (x<0||x>7) continue;
                    int y[2] = {k[1]+i, k[1]-i};
                    for (int i = 0; i < 2; i++){
                        if (0<=y[i]&&y[i]<8&&board[(y[i]<<3)+x].side!=piece.side) {
                            moves[(y[i]<<3)+x] = 1;
                            continue;
                        }
                        t = 0;
                    }
                }
                t = 1;
                for (int i = 1; i < 8 && t; i++) {
                    int x = k[0]+i;
                    if (x<0||x>7) continue;
                    int y[2] = {k[1]+i, k[1]-i};
                    for (int i = 0; i < 2; i++){
                        if (0<=y[i]&&y[i]<8&&board[(y[i]<<3)+x].side!=piece.side) {
                            moves[(y[i]<<3)+x] = 1;
                            continue;
                        }
                        t = 0;
                    }
                }
            }
            break;
        }
    }
    // debugging
    // printf("\nID = %i\nMOVES = [\n\t", pid);
    // for (int i = 0; i < 64; i++) {
    //     printf("%i ", moves[i]);
    //     if (!((i+1)%8)) printf("\n\t");
    // }
    // printf("]\n");
}
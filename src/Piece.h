#ifndef _PIECE_H_
#define _PIECE_H_
#include "Chessboard.h"

class Piece {
public:
    int x, y;
    char colour;
    char name; //The symbol of the piece
    Piece(Piece *component);
    Piece(int x, int y, char name);
    void setPiece(int x, int y);
    virtual int checkValidMove(int targetX, int targetY, Chessboard *component) = 0;
    virtual ~Piece();
};

#endif
#ifndef _BISHOP_H_
#define _BISHOP_H_
#include "Piece.h"

class Bishop: public Piece {
public:
    Bishop(int row, int col, char name);
    int checkValidMove(int targetX, int targetY, Chessboard *component) override;
};

#endif

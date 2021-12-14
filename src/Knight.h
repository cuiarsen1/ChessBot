#ifndef _KNIGHT_H_
#define _KNIGHT_H_
#include "Piece.h"

class Knight: public Piece {
public:
    Knight(int row, int col, char name);
    int checkValidMove(int targetX, int targetY, Chessboard *component) override;
};

#endif

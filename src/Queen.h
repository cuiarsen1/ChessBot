#ifndef _QUEEN_H_
#define _QUEEN_H_
#include "Piece.h"

class Queen: public Piece {
public:
    Queen(int row, int col, char name);
    int checkValidMove(int targetX, int targetY, Chessboard *component) override;
};

#endif

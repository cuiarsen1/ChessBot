#ifndef _Pawn_H_
#define _Pawn_H_
#include "Piece.h"

class Pawn: public Piece {
public:
    Pawn(int row, int col, char name);
    int checkValidMove(int targetX, int targetY, Chessboard *component) override;
};

#endif

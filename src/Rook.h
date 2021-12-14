#ifndef _ROOK_H_
#define _ROOK_H_
#include "Piece.h"

class Rook: public Piece {
public:
    Rook(int x, int y, char name);
    int checkValidMove(int targetX, int targetY, Chessboard *component) override;
};

#endif

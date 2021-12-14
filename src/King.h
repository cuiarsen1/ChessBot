#ifndef _KING_H_
#define _KING_H_
#include "Piece.h"

class King: public Piece {
public:
    King(int row, int col, char name);
    int checkValidMove(int targetX, int targetY, Chessboard *component) override;
};

#endif

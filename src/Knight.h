#ifndef _KNIGHT_H_
#define _KNIGHT_H_
#include "Piece.h"

class Knight: public Piece {
    int val;
public:
    Knight(int row, int col, char name);
    //char pieceAt(int row, int col) override;
    int checkValidMove(int targetX, int targetY, Chessboard *component) override;
};

#endif

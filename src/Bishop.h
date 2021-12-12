#ifndef _BISHOP_H_
#define _BISHOP_H_
#include "Piece.h"

class Bishop: public Piece {
    int val;
public:
    Bishop(int row, int col, char name);
    //char pieceAt(int row, int col) override;
    //char moveTo(int row, int col);
    int checkValidMove(int targetX, int targetY, Chessboard *component) override;
};

#endif

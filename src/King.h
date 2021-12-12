#ifndef _KING_H_
#define _KING_H_
#include "Piece.h"

class King: public Piece {
    int val;
public:
    King(int row, int col, char name);
    //char pieceAt(int row, int col) override;
    int checkValidMove(int targetX, int targetY, Chessboard *component) override;
};

#endif

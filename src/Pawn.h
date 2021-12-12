#ifndef _Pawn_H_
#define _Pawn_H_
#include "Piece.h"

class Pawn: public Piece {
    int val;
public:
    Pawn(int row, int col, char name);
    //char pieceAt(int row, int col) override;
    int checkValidMove(int targetX, int targetY, Chessboard *component) override;
};

#endif

#ifndef _ROOK_H_
#define _ROOK_H_
#include "Piece.h"

class Rook: public Piece {
    int val;
public:
    Rook(int x, int y, char name);
    int checkValidMove(int targetX, int targetY, Chessboard *component) override;
    //char pieceAt(int row, int col) override;
    //int legalLocation(int targetX, int targetY) override;
};

#endif

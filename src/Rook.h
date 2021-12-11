#ifndef _ROOK_H_
#define _ROOK_H_
#include "Piece.h"

class Rook: public Piece {
    int x, y;
    int val;
    char colour;
public:
    Rook(int x, int y, char colour, Chessboard *component);
    char pieceAt(int row, int col) override;
    //int legalLocation(int targetX, int targetY) override;
};

#endif

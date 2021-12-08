#ifndef _ROOK_H_
#define _ROOK_H_
#include "Piece.h"

class Rook: public Piece {
    int x, y;
    int val;
public:
    Rook(int row, int col, Chessboard *component);
    char pieceAt(int row, int col) override;
};

#endif

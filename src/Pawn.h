#ifndef _Pawn_H_
#define _Pawn_H_
#include "Piece.h"

class Pawn: public Piece {
    int x, y;
    int val;
public:
    Pawn(int row, int col, Chessboard *component);
    char pieceAt(int row, int col) override;
};

#endif

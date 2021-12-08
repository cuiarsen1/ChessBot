#ifndef _BISHOP_H_
#define _BISHOP_H_
#include "Piece.h"

class Bishop: public Piece {
    int x, y;
    int val;
public:
    Bishop(int row, int col, Chessboard *component);
    char pieceAt(int row, int col) override;
};

#endif

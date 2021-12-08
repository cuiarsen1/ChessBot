#ifndef _QUEEN_H_
#define _QUEEN_H_
#include "Piece.h"

class Queen: public Piece {
    int x, y;
    int val;
public:
    Queen(int row, int col, Chessboard *component);
    char pieceAt(int row, int col) override;
};

#endif

#ifndef _EMPTY_H_
#define _EMPTY_H_
#include "Piece.h"

class Empty: public Piece {
    int x, y;
public:
    Empty(int row, int col, Chessboard *component);
    char pieceAt(int row, int col) override;
};

#endif
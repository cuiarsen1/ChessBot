#ifndef _KNIGHT_H_
#define _KNIGHT_H_
#include "Piece.h"

class Knight: public Piece {
    int x, y;
    int val;
    char colour;
public:
    Knight(int row, int col, char colour, Chessboard *component);
    char pieceAt(int row, int col) override;
};

#endif

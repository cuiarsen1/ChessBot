#ifndef _QUEEN_H_
#define _QUEEN_H_
#include "Piece.h"

class Queen: public Piece {
    int x, y;
    int val;
    char colour;
public:
    Queen(int row, int col, char colour, Chessboard *component);
    char pieceAt(int row, int col) override;
};

#endif

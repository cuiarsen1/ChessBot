#ifndef _KING_H_
#define _KING_H_
#include "Piece.h"

class King: public Piece {
    int x, y;
    bool checked;
    char colour;
public:
    King(int row, int col, char colour, Chessboard *component);
    char pieceAt(int row, int col) override;
};

#endif

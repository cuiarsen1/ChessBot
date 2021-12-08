#ifndef _KING_H_
#define _KING_H_
#include "Piece.h"

class King: public Piece {
    int x, y;
    bool checked;
public:
    King(int row, int col, Chessboard *component);
    char pieceAt(int row, int col) override;
};

#endif

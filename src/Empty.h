#ifndef _EMPTY_H_
#define _EMPTY_H_
#include "Piece.h"

class Empty: public Piece {
public:
    Empty(int row, int col);
    //char pieceAt(int row, int col) override;
};

#endif
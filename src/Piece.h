#ifndef _PIECE_H_
#define _PIECE_H_
#include "Chessboard.h"

class Piece: public Chessboard {
protected:
    Chessboard *component;
public:
    Piece(Chessboard *component);
    virtual ~Piece();
};

#endif
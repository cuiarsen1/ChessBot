#include "Chessboard.h"
#include "Piece.h"

Piece::Piece(Chessboard *component):
        component{component} {}
Piece::~Piece() {
    delete component;
};

#include "Chessboard.h"
#include "Queen.h"
Queen::Queen(int row, int col, Chessboard *component):
        Piece{component}, x{row}, y{col}, val{9} {}

//basically places a Queen onto the chessboard
char Queen::pieceAt(int row, int col) {
    char currentPiece = component->pieceAt(row, col);
        if (currentPiece == ' '){  
            return 'Q';
    }
    return currentPiece;
}
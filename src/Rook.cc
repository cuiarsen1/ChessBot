#include "Chessboard.h"
#include "Rook.h"
Rook::Rook(int row, int col, Chessboard *component):
        Piece{component}, x{row}, y{col}, val{5} {}

//basically places a knight onto the chessboard
char Rook::pieceAt(int row, int col) {
    char currentPiece = component->pieceAt(row, col);
        if (currentPiece == ' '){  
            return 'R';
    }
    return currentPiece;
}
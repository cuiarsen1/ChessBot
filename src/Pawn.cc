#include "Chessboard.h"
#include "Pawn.h"
Pawn::Pawn(int row, int col, Chessboard *component):
        Piece{component}, x{row}, y{col}, val{1} {}

//basically places a pawn onto the chessboard
char Pawn::pieceAt(int row, int col) {
    char currentPiece = component->pieceAt(row, col);
        if (currentPiece == ' '){  
            return 'P';
    }
    return currentPiece;
}
#include "Chessboard.h"
#include "King.h"
King::King(int row, int col, Chessboard *component):
        Piece{component}, x{row}, y{col}, checked{false} {}

//basically places a king onto the chessboard
char King::pieceAt(int row, int col) {
    char currentPiece = component->pieceAt(row, col);
        if (currentPiece == ' '){  
            return 'X';
    }
    return currentPiece;
}
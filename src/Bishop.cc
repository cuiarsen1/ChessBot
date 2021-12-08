#include "Chessboard.h"
#include "Bishop.h"
Bishop::Bishop(int row, int col, Chessboard *component):
        Piece{component}, x{row}, y{col}, val{3} {}

//basically places a bishop onto the chessboard
char Bishop::pieceAt(int row, int col) {
    char currentPiece = component->pieceAt(row, col);
        if (currentPiece == ' '){  
            return 'B';
    }
    return currentPiece;
}
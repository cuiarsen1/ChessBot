#include "Chessboard.h"
#include "Knight.h"
Knight::Knight(int row, int col, Chessboard *component):
        Piece{component}, x{row}, y{col}, val{3} {}

//basically places a knight onto the chessboard
char Knight::pieceAt(int row, int col) {
    char currentPiece = component->pieceAt(row, col);
    if (currentPiece == ' ' && x == row && y == col){  
            return 'K';
    }
    return currentPiece;
}
#include "Chessboard.h"
#include "Empty.h"
Empty::Empty(int row, int col):
        Piece(row, col, ' ') {}

/*
//basically places a king onto the chessboard
char Empty::pieceAt(int row, int col) {
    char currentPiece = component->pieceAt(row, col);
    if (x == row && y == col){ 
        return ' ';
    }
    return currentPiece;
}
*/
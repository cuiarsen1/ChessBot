#include "Chessboard.h"
#include "King.h"
King::King(int row, int col, char colour, Chessboard *component):
        Piece{component}, x{row}, y{col}, colour{colour}, checked{false} {}

//basically places a king onto the chessboard
char King::pieceAt(int row, int col) {
    char currentPiece = component->pieceAt(row, col);
    if (x == row && y == col){ 
        if (colour == 'w'){     //if piece is white
            return 'K';
        }
        else return 'k'; 
    }
    return currentPiece;
}
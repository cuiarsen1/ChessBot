#include "Chessboard.h"
#include "Pawn.h"
Pawn::Pawn(int row, int col, char colour, Chessboard *component):
        Piece{component}, x{row}, y{col}, colour{colour},val{1} {}

//basically places a pawn onto the chessboard
char Pawn::pieceAt(int row, int col) {
    char currentPiece = component->pieceAt(row, col);
    if (x == row && y == col){  
        if (colour == 'w'){     //if piece is white
            return 'P';
        }
        else return 'p'; 
    }
    return currentPiece;
}
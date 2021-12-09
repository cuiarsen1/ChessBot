#include "Chessboard.h"
#include "Queen.h"
Queen::Queen(int row, int col, char colour, Chessboard *component):
        Piece{component}, x{row}, y{col}, colour{colour}, val{9} {}

//basically places a Queen onto the chessboard
char Queen::pieceAt(int row, int col) {
    char currentPiece = component->pieceAt(row, col);
    if (x == row && y == col){  
        if (colour == 'w'){     //if piece is white
            return 'Q';
        }
        else return 'q'; 
    }
    return currentPiece;
}
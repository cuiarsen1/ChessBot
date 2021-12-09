#include "Chessboard.h"
#include "Bishop.h"
Bishop::Bishop(int row, int col, char colour, Chessboard *component):
        Piece{component}, x{row}, y{col},colour{colour}, val{3} {}

//basically places a bishop onto the chessboard
char Bishop::pieceAt(int row, int col) {
    char currentPiece = component->pieceAt(row, col);
    if (currentPiece == ' ' && x == row && y == col){  
        if (colour == 'w'){     //if piece is white
            return 'B';
        }
        else return 'b'; 
    }
    return currentPiece;
}
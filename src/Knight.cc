#include "Chessboard.h"
#include "Knight.h"
Knight::Knight(int row, int col,char colour, Chessboard *component):
        Piece{component}, x{row}, y{col},colour{colour}, val{3} {}

//basically places a knight onto the chessboard
char Knight::pieceAt(int row, int col) {
    char currentPiece = component->pieceAt(row, col);
    if (currentPiece == ' ' && x == row && y == col){  
        if (colour == 'w'){     //if piece is white
            return 'N';
        }
        else return 'n'; 
    }
    return currentPiece;
}
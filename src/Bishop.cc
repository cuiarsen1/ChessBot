#include "Chessboard.h"
#include "Bishop.h"
Bishop::Bishop(int row, int col, char colour, Chessboard *component):
        Piece{component}, x{row}, y{col},colour{colour}, val{3} {}
Bishop::Bishop(int row, int col):
     Piece{NULL},x{row}, y{col} {}

//basically places a bishop onto the chessboard
char Bishop::pieceAt(int row, int col) {
    char currentPiece = component->pieceAt(row, col);
    if (x == row && y == col){  
        if (colour == 'w'){     //if piece is white
            return 'B';
        }
        else return 'b'; 
    }
    return currentPiece;
}
char Bishop::moveTo(int row, int col){
    if (checkValidMove(x,y,row,col)){
        
    }
}
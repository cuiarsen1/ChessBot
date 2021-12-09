#include "Chessboard.h"
#include "Rook.h"
Rook::Rook(int row, int col, char colour, Chessboard *component):
        Piece{component}, x{row}, y{col},colour{colour}, val{5} {}

//basically places a knight onto the chessboard
char Rook::pieceAt(int row, int col) {
    char currentPiece = component->pieceAt(row, col);
    if (x == row && y == col){  
        if (colour == 'w'){     //if piece is white
            return 'R';
        }
        else return 'r'; 
    }
    return currentPiece;
}
#include "Chessboard.h"
#include "Knight.h"
Knight::Knight(int row, int col, char name):
        Piece(row, col, name), val{3} {
            if (isupper(name)) colour = 'w';
            else colour = 'b';
        }

//Legal locations include all eight L-move locations (+-1|2, +=1|2)
int Knight::checkValidMove(int targetX, int targetY, Chessboard *component){
    int diffX = abs(x - targetX), diffY = abs(y - targetY);
    //If target location does not follow L shape, it's invalid move
    if (!((diffX == 1 && diffY == 2) || (diffX == 2 && diffY == 1))) return 0;
    //Finally, the target location must be either empty or occupied with enemy piece
    Piece *targetPiece = component->location(targetX, targetY);
    if (targetPiece == NULL) return 1;
    if (colour == 'w'){
        //With a white knight, enemy pieces must be lowercase
        if (islower(targetPiece->name)) return 2;
        return 0;
    }
    else{
        //With a black knight, enemy pieces must be uppercase
        if (isupper(targetPiece->name)) return 2;
        return 0;
    }
}

/*
//basically places a knight onto the chessboard
char Knight::pieceAt(int row, int col) {
    char currentPiece = component->pieceAt(row, col);
    if (x == row && y == col){  
        if (colour == 'w'){     //if piece is white
            return 'N';
        }
        else return 'n'; 
    }
    return currentPiece;
}
*/
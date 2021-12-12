#include "Chessboard.h"
#include "Bishop.h"

Bishop::Bishop(int row, int col, char name):
        Piece(row, col, name), val{3} {
            if (isupper(name)) colour = 'w';
            else colour = 'b';
        }

/*
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
*/

//Legal locations only include those on the diagonal of current (x, y) location
int Bishop::checkValidMove(int targetX, int targetY, Chessboard *component){
     int diffX = abs(x - targetX), diffY = abs(y - targetY);
    //Ensure new move isn't to original location
    if (diffX == 0 && diffY == 0) return 0;
    //If new location not on current (x, y) location's diagonal, it's invalid
    if (diffX != diffY) return 0;
    //Next, check if the path to new location isn't blocked off
    if (x < targetX && y < targetY){
        for (int i = 1; i < diffX; i++){
            int tempX = x + i, tempY = y + i;
            Piece *tempP = component->location(tempX, tempY);
            if (tempP != NULL) return 0;
        }
    }
    else if (x < targetX && y > targetY){
        for (int i = 1; i < diffX; i++){
            int tempX = x + i, tempY = y - i;
            Piece *tempP = component->location(tempX, tempY);
            if (tempP != NULL) return 0;
        }
    }
    else if (x > targetX && y < targetY){
        for (int i = 1; i < diffX; i++){
            int tempX = x - i, tempY = y + i;
            Piece *tempP = component->location(tempX, tempY);
            if (tempP != NULL) return 0;
        }
    }
    else if (x > targetX && y < targetY){
        for (int i = 1; i < diffX; i++){
            int tempX = x - i, tempY = y - i;
            Piece *tempP = component->location(tempX, tempY);
            if (tempP != NULL) return 0;
        }
    }
    //Finally, the target piece must either be empty or
    //occupied with enemy piece
    Piece *targetPiece = component->location(targetX, targetY);
    if (targetPiece == NULL) return 1;
    if (colour == 'w'){
        //With a white bishop, the enemy pieces must be lowercase
        if (islower(targetPiece->name)) return 2;
        else return 0;
    }
    else{
        //With a black bishop, the enemy pieces must be uppercase
        if (isupper(targetPiece->name)) return 2;
        else return 0;
    }
}
/*char Bishop::moveTo(int row, int col){
    if (checkValidMove(x,y,row,col)){
        
    }
}*/
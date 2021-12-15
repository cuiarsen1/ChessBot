#include "Chessboard.h"
#include "King.h"

King::King(int row, int col, char name): Piece(row, col, name) {}

//Legal locations include all eight adjacent locations near current (x, y)
int King::checkValidMove(int targetX, int targetY, Chessboard *component){
    int diffX = abs(x - targetX), diffY = abs(y - targetY);
    //Ensure move location isn't same as original location
    if (diffX == 0 && diffY == 0) return 0;
    //Ensure distance is valid
    if (diffX > 1 || diffY > 1) return 0;
    //Finally, the target location must be either empty or occupied with enemy piece
    if (colour == 'w'){
        //With a white king, enemy pieces must be lowercase
        Piece *targetPiece = component->location(targetX, targetY);
        if (targetPiece == NULL) return 1;
        if (islower(targetPiece->name)) return 2;
        return 0;
    }
    else{
        //With a black king, enemy pieces must be uppercase
        Piece *targetPiece = component->location(targetX, targetY);
        if (targetPiece == NULL) return 1;
        if (isupper(targetPiece->name)) return 2;
        return 0;
    }
}

#include "Chessboard.h"
#include "King.h"
#include "Rook.h"
#include <iostream>
using namespace std;

King::King(int row, int col, char name): Piece(row, col, name) {}

//Legal locations include all eight adjacent locations near current (x, y)
int King::checkValidMove(int targetX, int targetY, Chessboard *component){
    int diffX = abs(x - targetX), diffY = abs(y - targetY);
    //Ensure move location isn't same as original location
    if (diffX == 0 && diffY == 0) return 0;
    //To begin, we handle the special case of castling
    //First, the move is strictly horizontal with 2 steps
    if (diffX == 0 && diffY == 2){
        //Since this condition already assumes diffY = 2
        //(which would've be a valid normal king move),
        //then any conditions from now on that isn't met can return 0 to show invalid
        //Setup mode banned castling
        if (!component->allowCastling) return 0;
        //If the piece has been moved, it's invalid
        if (moved) return 0;
        //If current king is in check, it's invalid
        if (component->check(colour)) return 0;
        //If x > targetX, then it's the left (distance 3) castle
        int colourRow = (colour == 'b') ? 0 : 7;
        if (x > targetX){
            Piece *tempRook = component->location(colourRow, 0);
            //If not a rook, the castle is invalid
            if (dynamic_cast<Rook*>(tempRook) == NULL) return 0;
            //If it has been moved, the castle is invalid
            if (tempRook->moved) return 0;
            //Next, check the middle three spaces are empty
            if (component->location(colourRow, 1) != NULL) return 0;
            if (component->location(colourRow, 2) != NULL) return 0;
            if (component->location(colourRow, 3) != NULL) return 0;
            //Finally, check the cross
            //Try moving the king one spot left
            setPiece(colourRow, 3);
            //If the cross is checked, it's invalid
            if (component->check(colour)) return 0;
            //Move the king back
            setPiece(colourRow, 4);
            return 3; //Otherwise, it's a valid castle
        }
        //Right (distance 2) castle
        else{
            Piece *tempRook = component->location(colourRow, 7);
            //If not a rook, the castle is invalid
            if (dynamic_cast<Rook*>(tempRook) == NULL) return 0;
            //If it has been moved, the castle is invalid
            if (tempRook->moved) return 0;
            //Next, check the middle three spaces are empty
            if (component->location(colourRow, 5) != NULL) return 0;
            if (component->location(colourRow, 6) != NULL) return 0;
            //Finally, check the cross
            //Try moving the king one spot right
            setPiece(colourRow, 5);
            //If the cross is checked, it's invalid
            if (component->check(colour)) return 0;
            //Move the king back
            setPiece(colourRow, 4);
            return 3; //Otherwise, it's a valid castle
        }
    }
    //Ensure distance is valid
    if (diffX > 1 || diffY > 1) return 0;
    //Finally, the target location must be either empty or occupied with enemy piece
    Piece *targetPiece = component->location(targetX, targetY);
    if (targetPiece == NULL) return 1;
    if (colour == 'w'){
        //With a white king, enemy pieces must be lowercase
        if (islower(targetPiece->name)) return 2;
        return 0;
    }
    else{
        //With a black king, enemy pieces must be uppercase
        if (isupper(targetPiece->name)) return 2;
        return 0;
    }
}

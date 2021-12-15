#include "Chessboard.h"
#include "Queen.h"
#include <iostream>
using namespace std;

Queen::Queen(int row, int col, char name): Piece(row, col, name) {}

//Legal locations include all horizontal/vertical/diagonal moves
int Queen::checkValidMove(int targetX, int targetY, Chessboard *component){
    int diffX = abs(x - targetX), diffY = abs(y - targetY);
    //Ensure new move isn't to original location
    if (diffX == 0 && diffY == 0) return 0;
    //If neither differences are zero, then it must be diagonal
    //Perform same check as Bishop
    if (diffX != 0 && diffY != 0){
        //If new location not on current (x, y) location's diagonal, it's invalid
        if (diffX != diffY) return 0;
        //Next, check if the path to new location isn't blocked off
        if (x < targetX && y < targetY){
            for (int i = 1; i < diffX; ++i){
                int tempX = x + i, tempY = y + i;
                if (component->location(tempX, tempY) != NULL) return 0;
            }
        }
        else if (x < targetX && y > targetY){
            for (int i = 1; i < diffX; ++i){
                int tempX = x + i, tempY = y - i;
                if (component->location(tempX, tempY) != NULL) return 0;
            }
        }
        else if (x > targetX && y < targetY){
            for (int i = 1; i < diffX; ++i){
                int tempX = x - i, tempY = y + i;
                if (component->location(tempX, tempY) != NULL) return 0;
            }
        }
        else if (x > targetX && y > targetY){
            for (int i = 1; i < diffX; ++i){
                int tempX = x - i, tempY = y - i;
                if (component->location(tempX, tempY) != NULL) return 0;
            }
        }
    }
    //Otherwise, it must be on horizontal or vertical
    //Perform same check as Rook
    else{
        //Check if the path to new location isn't blocked off
        if (diffX == 0){ //Move is horizontal
            for (int tempY = min(y, targetY) + 1; tempY < max(y, targetY); ++tempY){ //Example: (2, 3) to (2, 7) has 7-3-1=3 pieces on horizontal axis
                //If not empty, it's occupied, and thus the path is blocked
                if (component->location(x, tempY) != NULL) return 0;
            }
        }
        else if (diffY == 0){ //Move is vertical
            for (int tempX = min(x, targetX) + 1; tempX < max(x, targetX); ++tempX){ //Example: (3, 3) to (7, 3) has 7-3-1=3 pieces on horizontal axis
                //If not empty, it's occupied, and thus the path is blocked
                if (component->location(tempX, y) != NULL) return 0;
            }
        }
    }
    //Finally, the target piece must either be empty or
    //occupied with enemy piece
    Piece *targetPiece = component->location(targetX, targetY);
    if (targetPiece == NULL) return 1;
    if (colour == 'w'){
        //With a white queen, the enemy pieces must be lowercase
        if (islower(targetPiece->name)) return 2;
        return 0;
    }
    else{
        //With a black queen, the enemy pieces must be uppercase
        if (isupper(targetPiece->name)) return 2;
        return 0;
    }
}

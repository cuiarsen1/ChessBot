#include "Chessboard.h"
#include "Pawn.h"
#include <iostream>
using namespace std;

Pawn::Pawn(int row, int col, char name):
        Piece(row, col, name), val{1} {}

//Legal locations include one unit up (or two if row # valid) and diagonal ups
int Pawn::checkValidMove(int targetX, int targetY, Chessboard *component){
    //White pieces are bottom of 2D array;
    //Thus, white pawns must decrease in Y value, as it moves up
    if (colour == 'w'){
        int diffX = x - targetX, diffY = abs(y - targetY);
        if (diffX == 2){
            //If it moves two units up, it must be at initial state
            //Thus, the original row number must be 6 (in a [0, 7] index)
            //Furthermore, diffX must be 0
            return (x == 6 && diffY == 0);
        }
        else if (diffX == 1){
            //If it moves one unit up, it's either straight up or diagonal
            //If diffX = 0, then the new position must be unoccupied by any piece
            //If diffX = 1, then the new position must be occupied by enemy piece
            //NOTE: ,or en passant
            //Note: with the current pawn being white, then enemy piece is lowercase
            if (diffY == 0) return component->location(targetX, targetY) == NULL;
            else if (diffY == 1){
                Piece *targetPiece = component->location(targetX, targetY);
                if (targetPiece == NULL) return 0;
                if (islower(targetPiece->name)) return 2;
                //Check: en passant
                //Check: promotion
                return 0; //Otherwise, it's 0
            }
        }
        return 0; //Otherwise, the target is invalid
    }
    //Black pawns must move down, thus increasing in Y value
    else if (colour == 'b'){
        int diffX = targetX - x, diffY = abs(targetY - y);
        if (diffX == 2){
            //If it moves two units down, it must be at initial state
            //Thus, the original row number must be 1 (in a [0, 7] index)
            //Furthermore, diffX must be 0
            return (x == 1 && diffY == 0);
        }
        else if (diffX == 1){
            //If it moves one unit down, it's either straight down or diagonal
            //If diffX = 0, then the new position must be unoccupied by any piece
            //If diffX = 1, then the new position must be occupied by enemy piece
            //NOTE: ,or en passant
            //Note: with the current pawn being black, then enemy piece is uppercase
            if (diffY == 0) return component->location(targetX, targetY) == NULL;
            else if (diffY == 1){
                Piece *targetPiece = component->location(targetX, targetY);
                if (targetPiece == NULL) return 0;
                if (isupper(targetPiece->name)) return 2;
                //Check: en passant
                return 0; //Otherwise, the target is invalid
            }
        }
        return 0; //Otherwise, it's an invalid move
    }
    return 0; //Should not reach here
}

/*
//basically places a pawn onto the chessboard
char Pawn::pieceAt(int row, int col) {
    char currentPiece = component->pieceAt(row, col);
    if (x == row && y == col){  
        if (colour == 'w'){     //if piece is white
            return 'P';
        }
        else return 'p'; 
    }
    return currentPiece;
}
*/
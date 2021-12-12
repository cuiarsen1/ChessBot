#include <iostream>
#include "Chessboard.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include "Piece.h"
using namespace std;

void Chessboard::newPiece(int x, int y, char name){
    if (name == 'K') whitePieces.push_back(new King(x, y, name));
    else if (name == 'k') blackPieces.push_back(new King(x, y, name));
    else if (name == 'Q') whitePieces.push_back(new Queen(x, y, name));
    else if (name == 'q') blackPieces.push_back(new Queen(x, y, name));
    else if (name == 'R') whitePieces.push_back(new Rook(x, y, name));
    else if (name == 'r') blackPieces.push_back(new Rook(x, y, name));
    else if (name == 'B') whitePieces.push_back(new Bishop(x, y, name));
    else if (name == 'b') blackPieces.push_back(new Bishop(x, y, name));
    else if (name == 'N') whitePieces.push_back(new Knight(x, y, name));
    else if (name == 'n') blackPieces.push_back(new Knight(x, y, name));
    else if (name == 'P') whitePieces.push_back(new Pawn(x, y, name));
    else if (name == 'p') blackPieces.push_back(new Pawn(x, y, name));
}

Chessboard::Chessboard(){
    //Black is top, white is bottom
    //With 16 pieces of each colour, we will store them in each vector separately
    //Sorted by importance of each piece
    newPiece(-1, -1, 'k');
    newPiece(-1, -1, 'q');
    newPiece(-1, -1, 'r');
    newPiece(-1, -1, 'r');
    newPiece(-1, -1, 'b');
    newPiece(-1, -1, 'b'); 
    newPiece(-1, -1, 'k');
    newPiece(-1, -1, 'k');
    for (int i = 0; i < 8; i++) newPiece(-1, -1, 'p');
    newPiece(-1, -1, 'K');
    newPiece(-1, -1, 'Q');
    newPiece(-1, -1, 'R');
    newPiece(-1, -1, 'R');
    newPiece(-1, -1, 'B');
    newPiece(-1, -1, 'B'); 
    newPiece(-1, -1, 'K');
    newPiece(-1, -1, 'K');
    for (int i = 0; i < 8; i++) newPiece(-1, -1, 'P');
}

void Chessboard::init(){
    //If setup mode was never entered, set the pieces to corresponding locations
    blackPieces[0]->setPiece(0, 4);
    blackPieces[1]->setPiece(0, 3);
    blackPieces[2]->setPiece(0, 0);
    blackPieces[3]->setPiece(0, 7);
    blackPieces[4]->setPiece(0, 2);
    blackPieces[5]->setPiece(0, 5);
    blackPieces[6]->setPiece(0, 1);
    blackPieces[7]->setPiece(0, 6);
    for (int i = 8; i < 16; i++) blackPieces[i]->setPiece(1, i - 8);
    whitePieces[0]->setPiece(7, 4);
    whitePieces[1]->setPiece(7, 3);
    whitePieces[2]->setPiece(7, 0);
    whitePieces[3]->setPiece(7, 7);
    whitePieces[4]->setPiece(7, 2);
    whitePieces[5]->setPiece(7, 5);
    whitePieces[6]->setPiece(7, 1);
    whitePieces[7]->setPiece(7, 6);
    for (int i = 8; i < 16; i++) whitePieces[i]->setPiece(6, i - 8);
}

Piece *Chessboard::location(int x, int y){
    for (Piece *p: blackPieces){
        if (p->x == x && p->y == y) return p;
    }
    for (Piece *p: whitePieces){
        if (p->x == x && p->y == y) return p;
    }
    //Otherwise, the piece does not exist
    return NULL;
}

int Chessboard::move(int startX, int startY, int targetX, int targetY){
    Piece *start = location(startX, startY);
    if (start == NULL) return 0;
    int status = start->checkValidMove(targetX, targetY, this);
    if (status == 0) return 0;
    if (status == 1){
        //Move to unoccupied spot
        start->setPiece(targetX, targetY);
        return 1;
    }
    if (status == 2){
        //Capture piece at target spot
        Piece *oldTarget = location(targetX, targetY);
        oldTarget->setPiece(-1, -1);
        start->setPiece(targetX, targetY);
        return 2;
    }
    if (status == 3){
        //Promotion
    }
    return 0;
}

bool Chessboard::check(char colour){
    //Check if the king of the given colour's is threatened
    if (colour == 'w'){
        //First, get the location of white king
        int whiteKingX = -1, whiteKingY = -1;
        for (Piece *p: whitePieces){
            if (p->name == 'K'){
                whiteKingX = p->x;
                whiteKingY = p->y;
                break;
            }
        }
        //Run through all black pieces, to see if they can reach white king in one valid move
        for (Piece *p: blackPieces){
            if (p->checkValidMove(whiteKingX, whiteKingY, this) == 2){
                //The white king can be captured
                return true;
            }
        }
        //If none of the enemy pieces can reach king, then it's not in check
        return false;
    }
    else{
        //First, get the location of black king
        int blackKingX = -1, blackKingY = -1;
        for (Piece *p: blackPieces){
            if (p->name == 'k'){
                blackKingX = p->x;
                blackKingY = p->y;
                break;
            }
        }
        //Run through all white pieces to see if they can reach black king in one valid move
        for (Piece *p: whitePieces){
            if (p->checkValidMove(blackKingX, blackKingY, this) == 2){
                //The white king can be captured
                return true;
            }
        }
        //If none of the enemy pieces can reach king, then it's not in check
        return false;
    }
}

Chessboard::~Chessboard() {}
/*Chessboard::Chessboard(){
    board[0][0] = new Square(0, 0,'R','B'); //B for Black, R for Rook
    board[0][1] = new Square(0, 1,'K','B');
    board[0][2] = new Square(0, 2,'B','B');
    board[0][3] = new Square(0, 3,'Q','B');
    board[0][4] = new Square(0, 4,'X','B'); //X for king for now 
    board[0][5] = new Square(0, 5,'B','B');
    board[0][6] = new Square(0, 6,'K','B');
    board[0][7] = new Square(0, 7,'R','B');
    for (int i = 0; i < 8; i++){
      board[1][i] = new Square(1, i,'P','B');
    }
    board[7][0] = new Square(0, 0,'R','W'); //W for White, R for Rook
    board[7][1] = new Square(0, 1,'K','W');
    board[7][2] = new Square(0, 2,'B','W');
    board[7][3] = new Square(0, 3,'Q','W');
    board[7][4] = new Square(0, 4,'X','W'); //X for king for now 
    board[7][5] = new Square(0, 5,'B','W');
    board[7][6] = new Square(0, 6,'K','W');
    board[7][7] = new Square(0, 7,'R','W');
    for (int i = 0; i < 8; i++){
      board[6][i] = new Square(6, i,'P','W');
    }
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            //if (!isOccupied()){
              //Square* blank = new Square(i, j);
              //std::cout<<"w";
              board[i][j] = new Square(i, j);
              
              //delete blank;
            //}
        }
    }
}

Chessboard::~Chessboard() {
    for (int i = 0; i < 8; ++i) {
     for (int j = 0; j < 8; j++)
        delete board[i][j];
    }
}

bool Chessboard::isOccupied(int x, int y){
    //std::cout<<"x";
    char piece = board[x][y]->getPiece();
    std::cout<<piece;
    if (piece == 'P' || piece == 'R' || piece == 'K' || piece == 'B' || piece == 'Q' || piece == 'X'){
        return true;
    }
    return false;
}

void Chessboard::printChessboard(){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (isOccupied(i,j)){
                std::cout<<board[i][j]->getPiece();
            }
            else{
                std::cout<<' ';
            }
        }
        std::cout << std::endl;
    }
}*/



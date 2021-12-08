#include <iostream>
#include "Chessboard.h"

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



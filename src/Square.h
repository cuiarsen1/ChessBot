#ifndef __SQUARE_H__
#define __SQUARE_H__
#include <iostream>
#include "Chessboard.h"
class Square: public Chessboard{
      //char pieceAt(int row, int col) override;
};
    /*int posx, posy;
    char piece;   //change this to Piece* instead of char once Piece class is created
    char player;
    public:
      Square(int x, int y);
      Square(int x, int y, char p, char player);
      void move(int x, int y);
      char getPiece();
};*/

#endif

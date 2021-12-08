#ifndef __CHESSBOARD_H__
#define __CHESSBOARD_H__
#include <string>

class Chessboard {
   public:
   virtual ~Chessboard();
   virtual char pieceAt(int row, int col) = 0;
};
/*
 Square* board[8][8];
 public:
  Chessboard();
  ~Chessboard();
  void printChessboard();
  bool isOccupied(int x, int y);
};
*/
#endif
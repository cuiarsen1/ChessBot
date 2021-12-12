#ifndef __CHESSBOARD_H__
#define __CHESSBOARD_H__
#include <string>
#include <vector>

class Piece;

class Chessboard {
   std::vector<Piece*> blackPieces;
   std::vector<Piece*> whitePieces;
public:
   void newPiece(int x, int y, char name);
   void init(); //Sets position of the pieces
   void removePiece(int x, int y);
   Piece *location(int x, int y);
   int move(int startX, int startY, int targetX, int targetY);
   bool verify();
   bool check(char colour);
   bool checkmate(char colour);
   ~Chessboard();
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
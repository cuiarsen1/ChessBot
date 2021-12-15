#ifndef __CHESSBOARD_H__
#define __CHESSBOARD_H__
#include <string>
#include <vector>
#include "Subject.h"

class Piece;
class TextObserver;

class Chessboard: public Subject {
public:
   std::vector<Piece*> blackPieces;
   std::vector<Piece*> whitePieces;
   void newPiece(int x, int y, char name);
   void init(); //Sets position of the pieces
   void reset(); //Used to clean all the pieces from the board after every match
   void removePiece(int x, int y);
   void promote(int x, int y, char name); //Promote pawn at given position
   Piece *location(int x, int y);
   int move(int startX, int startY, int targetX, int targetY);
   bool verify();
   bool check(char colour);
   bool checkmate(char colour);
   bool stalemate(char colour);
   ~Chessboard();
};
#endif

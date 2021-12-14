#ifndef _COMPUTER_H_
#define _COMPUTER_H_
#include "Player.h"
#include "Chessboard.h"

class Computer: public Player {
public:
    int level;
    Computer(char colour, int level); //Constructor
    bool turn(Chessboard *component) override;
private:
   void level1(Chessboard *component);
   void level2(Chessboard *component);
   void level3(Chessboard *component);
};

#endif

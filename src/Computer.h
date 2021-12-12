#ifndef _COMPUTER_H_
#define _COMPUTER_H_
#include "Player.h"

class Computer: public Player {
public:
    int level;
    Computer(char colour, int level); //Constructor
    bool turn(Chessboard *component) override;
};

#endif
#ifndef _HUMAN_H_
#define _HUMAN_H_
#include "Player.h"

class Human: public Player {
public:
    Human(char colour); //Constructor
    bool turn(Chessboard *component) override;
};

#endif
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Chessboard.h"

class Player {
public:
    char colour;
    Player(char colour); //Constructor
    //Make the move given the current state of chessboard
    virtual bool turn(Chessboard *component) = 0;
    virtual ~Player();
};

#endif

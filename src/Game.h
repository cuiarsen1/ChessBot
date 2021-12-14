#ifndef _GAME_H_
#define _GAME_H_
#include "TextObserver.h"
#include "Chessboard.h"
#include "Player.h"

//Class represents all parts that a game would contain
//Essential parts include a Chessboard and two players
class Game {
    Chessboard *component;
    TextObserver *TO; //Text Observer
    Player *playerB;
    Player *playerW;
    bool gameOver; //To see if the game ended with a result
    bool custom; //To keep track of whether or not setup mode was used
    char move; //Tracks which side goes next
public:
    double whiteScore; //Tracking score
    double blackScore;
    Game(); //Constructor
    void interact(); //To read user input
    void setup(); //For setup mode
    void inGame(); //For all moves made in-game
    void restart(); //For new match
    ~Game(); //Destructor
};

#endif

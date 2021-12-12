#include "Computer.h"
#include "Player.h"
#include "Chessboard.h"
#include "Piece.h"
using namespace std;

Computer::Computer(char colour, int level): Player(colour), level{level} {}

bool Computer::turn(Chessboard *component){
    return true;
}
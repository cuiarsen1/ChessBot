#include "Piece.h"
using namespace std;

Piece::Piece(int x, int y, char name):
        x{x}, y{y}, colour{isupper(name) ? 'w' : 'b'}, name{name} {}
        
Piece::~Piece() {}

//Update current piece's location
void Piece::setPiece(int x, int y){
    this->x = x;
    this->y = y;
}
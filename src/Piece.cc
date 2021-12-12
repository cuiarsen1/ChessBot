#include "Piece.h"
#include <vector>
using namespace std;

Piece::Piece(int x, int y, char name):
        x{x}, y{y}, colour{isupper(name) ? 'w' : 'b'}, name{name} {}
        
Piece::~Piece() {}

//Update current piece's location
void Piece::setPiece(int x, int y){
    this->x = x;
    this->y = y;
}

vector<pair<int, int>> Piece::findMoves(Chessboard *component){
    //Find all the possible moves (to unoccupied spots)
    //Loop through every spot on the chessboard, and call checkValidMove
    vector<pair<int, int>> moves;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (checkValidMove(i, j, component) == 1){
                moves.emplace_back(i, j);
            }
        }
    }
    return moves;
}

vector<pair<int, int>> Piece::findCaptures(Chessboard *component){
    //Find all possible captures
    //Loop through all spots on the chessboard, and call checkValidMove
    vector<pair<int, int>> captures;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (checkValidMove(i, j, component) == 2){
                captures.emplace_back(i, j);
            }
        }
    }
    return captures;
}
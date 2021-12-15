#include "Piece.h"
#include <vector>
using namespace std;

Piece::Piece(int x, int y, char name):
        x{x}, y{y}, name{name}, moved{false}, enPassant{false} {
            colour = isupper(name) ? 'w' : 'b';
            char temp = tolower(name);
            if (temp == 'k') value = 10000;
            else if (temp == 'q') value = 9;
            else if (temp == 'r') value = 5;
            else if (temp == 'n') value = 3;
            else if (temp == 'b') value = 3;
            else value = 1;
        }
        
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

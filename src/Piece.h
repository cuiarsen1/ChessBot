#ifndef _PIECE_H_
#define _PIECE_H_
#include "Chessboard.h"
#include <vector>

class Piece {
public:
    int x, y;
    char colour;
    char name; //The symbol of the piece
    Piece(int x, int y, char name);
    void setPiece(int x, int y);
    std::vector<std::pair<int, int>> findMoves(Chessboard *component);
    std::vector<std::pair<int, int>> findCaptures(Chessboard *component);
    virtual int checkValidMove(int targetX, int targetY, Chessboard *component) = 0;
    virtual ~Piece();
};

#endif

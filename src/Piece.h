#ifndef _PIECE_H_
#define _PIECE_H_
#include "Chessboard.h"
#include <vector>

class Piece {
public:
    int x, y;
    char colour;
    char name; //The symbol of the piece
    int value; //The piece's worth
    //To check if a piece has been moved;
    //This is used for pawn's first move, castling and en passant
    bool moved;
    bool enPassant; //For tracking if enPassant can be performed on this Pawn (by enemy)
    Piece(int x, int y, char name);
    void setPiece(int x, int y);
    std::vector<std::pair<int, int>> findMoves(Chessboard *component);
    std::vector<std::pair<int, int>> findCaptures(Chessboard *component);
    virtual int checkValidMove(int targetX, int targetY, Chessboard *component) = 0;
    virtual ~Piece();
};

#endif

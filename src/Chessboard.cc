#include <iostream>
#include "Chessboard.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include "Piece.h"
using namespace std;

Chessboard::Chessboard(): allowCastling{true}, allowEnPassant{true} {}

void Chessboard::newPiece(int x, int y, char name){
    if (name == 'K') whitePieces.push_back(new King(x, y, name));
    else if (name == 'k') blackPieces.push_back(new King(x, y, name));
    else if (name == 'Q') whitePieces.push_back(new Queen(x, y, name));
    else if (name == 'q') blackPieces.push_back(new Queen(x, y, name));
    else if (name == 'R') whitePieces.push_back(new Rook(x, y, name));
    else if (name == 'r') blackPieces.push_back(new Rook(x, y, name));
    else if (name == 'B') whitePieces.push_back(new Bishop(x, y, name));
    else if (name == 'b') blackPieces.push_back(new Bishop(x, y, name));
    else if (name == 'N') whitePieces.push_back(new Knight(x, y, name));
    else if (name == 'n') blackPieces.push_back(new Knight(x, y, name));
    else if (name == 'P') whitePieces.push_back(new Pawn(x, y, name));
    else if (name == 'p') blackPieces.push_back(new Pawn(x, y, name));
}

void Chessboard::removePiece(int x, int y){
    int index = 0;
    for (Piece *p: blackPieces){
        if (p->x == x && p->y == y){
            blackPieces.erase(blackPieces.begin() + index);
            delete p;
        }
        ++index;
    }
    index = 0;
    for (Piece *p: whitePieces){
        if (p->x == x && p->y == y){
            whitePieces.erase(whitePieces.begin() + index);
            delete p;
        }
        ++index;
    }
    //If the piece is not found, no action is taken
}

void Chessboard::init(){
    //If setup mode was never entered, set the pieces to corresponding locations
    //Black is top, white is bottom
    //With 16 pieces of each colour, we will store them in each vector separately
    //Sorted by importance of each piece
    newPiece(0, 4, 'k');
    newPiece(0, 3, 'q');
    newPiece(0, 0, 'r');
    newPiece(0, 7, 'r');
    newPiece(0, 2, 'b');
    newPiece(0, 5, 'b');
    newPiece(0, 1, 'n');
    newPiece(0, 6, 'n');
    for (int i = 8; i < 16; ++i) newPiece(1, i - 8, 'p');
    newPiece(7, 4, 'K');
    newPiece(7, 3, 'Q');
    newPiece(7, 0, 'R');
    newPiece(7, 7, 'R');
    newPiece(7, 2, 'B');
    newPiece(7, 5, 'B');
    newPiece(7, 1, 'N');
    newPiece(7, 6, 'N');
    for (int i = 8; i < 16; ++i) newPiece(6, i - 8, 'P');
}

void Chessboard::reset(){
    //Delete every piece on the board
    //Acts as destructor without wiping the Chessboard itself
    for (Piece *p: blackPieces) delete p;
    blackPieces.clear();
    for (Piece *p: whitePieces) delete p;
    whitePieces.clear();
    //Also reset the custom allow castle and en passant booleans
    allowCastling = true;
    allowEnPassant = true;
}

Piece *Chessboard::location(int x, int y){
    for (Piece *p: blackPieces){
        if (p->x == x && p->y == y) return p;
    }
    for (Piece *p: whitePieces){
        if (p->x == x && p->y == y) return p;
    }
    //Otherwise, the piece does not exist
    return NULL;
}

void Chessboard::promote(int x, int y, char name){
    //Since this function is only called after a pawn has been moved,
    //Then (x, y) is guaranteed to be a pawn
    //First, delete the original pawn at (x, y)
    removePiece(x, y);
    //Next, initialize a new piece with the given name
    newPiece(x, y, name);
}

int Chessboard::move(int startX, int startY, int targetX, int targetY){
    Piece *start = location(startX, startY);
    if (start == NULL) return 0;
    int status = start->checkValidMove(targetX, targetY, this);
    if (status == 0) return 0;
    if (status == 1){
        //Move to unoccupied spot
        start->setPiece(targetX, targetY);
        //Make sure new move doesn't get our king into check
        if (check(start->colour)){
            //If it does, revert the move and return 0 to show invalid
            start->setPiece(startX, startY);
            return 0;
        }
        //Otherwise, successful; mark the bool of the piece to show it has moved
        start->moved = true;
        //SPECIAL CASE: If the piece is a pawn, check promotion
        if (dynamic_cast<Pawn*>(start) != NULL){
            //The piece is a pawn; check column
            if (start->colour == 'w' && start->x == 0) return 3;
            if (start->colour == 'b' && start->x == 7) return 3;
            //Otherwise, the pawn has not reached the opposite side of the board
        }
        return 1; //Otherwise, it's a normal pawn move
    }
    if (status == 2){
        //Capture piece at target spot
        //Note that normally, we would call removePiece(targetX, targetY)
        //However, the capture might result in a check, thus making the move invalid
        //Thus, we first move the oldTarget off the chessboard to test for check
        //If it does result in a check, revert the changes
        //If not, then call removePiece(oldTarget)
        Piece *oldTarget = location(targetX, targetY);
        oldTarget->setPiece(-1, -1); //Move old target off the chessboard
        start->setPiece(targetX, targetY);
        //Make sure new move doesn't get our king into check
        if (check(start->colour)){
            //Revert changes
            start->setPiece(startX, startY);
            oldTarget->setPiece(targetX, targetY);
            return 0;
        }
        else{
            //Valid capture; delete old target
            //Stored at the temporary (-1, -1) position
            removePiece(-1, -1);
            //Since piece has moved, update the boolean
            start->moved = true;
            //SPECIAL CASE: If the piece is a pawn, check promotion
            if (dynamic_cast<Pawn*>(start) != NULL){
                //The piece is a pawn; check column
                if (start->colour == 'w' && start->x == 0) return 3;
                if (start->colour == 'b' && start->x == 7) return 3;
                //Otherwise, the pawn has not reached the opposite side of the board
            }
            return 2;
        }
    }
    if (status == 3){
        //Castling; if the king is checked after castle, it's invalid
        //Ppdate the location of the king and rook completes the castle
        start->setPiece(targetX, targetY); //King
        Piece *tempRook = location(targetX, (targetY < startY) ? 0 : 7);
        tempRook->setPiece(targetX, (targetY < startY) ? 3 : 5);
        if (check(start->colour)){
            //Invalid move, as it gets the king into check
            //Revert changes
            tempRook->setPiece(targetX, (targetY < startY) ? 0 : 7);
            start->setPiece(targetX, 4);
            return 0;
        }
        return 4; //3 is occupied by promotion
    }
    if (status == 4){
        //en passant; still need to check that move doesn't get check
        Piece *oldTarget = location(startX, targetY); //NOTE startX for en passant
        oldTarget->setPiece(-1, -1); //Move old target off the chessboard
        start->setPiece(targetX, targetY);
        //Make sure new move doesn't get our king into check
        if (check(start->colour)){
            //Revert changes
            start->setPiece(startX, startY);
            oldTarget->setPiece(startX, targetY);
            return 0;
        }
        else{
            //Valid en passant; delete old target
            //Stored at the temporary (-1, -1) position
            removePiece(-1, -1);
            //Since piece has moved, update the boolean
            start->moved = true;
            //We know it's impossible for en passant to lead directly to promotion,
            //thus no need to check for promotion case
            return 5; //4 is occupied by castling
        }
    }
    return 0;
}

bool Chessboard::verify(){
    //First, check if there's only one king of each colour
    bool WKing = false, BKing = false;
    for (Piece *p: whitePieces){
        if (p->name == 'K'){
            //if there's already a white king, and a second one is found
            //Then two white kings exist, thus invalid
            if (WKing) return false;
            WKing = true; //Otherwise, mark the boolean since a white king exists
            //Next, ensure the king is not in check
            if (check('w')) return false;
        }
        else if (p->name == 'P'){
            //Check if all white pawns are not on top/bottom row
            if (p->x == 7 || p->x == 0) return false;
        }
    }
    for (Piece *p: blackPieces){
        if (p->name == 'k'){
            if (BKing) return false;
            BKing = true;
            if (check('b')) return false;
        }
        else if (p->name == 'p'){
            if (p->x == 0 || p->x == 7) return false;
        }
    }
    //Finally, with all pawns in valid positions and the king not in check,
    //We verify that a king does exist, since there must be exactly one king of each
    return (WKing && BKing);
}

bool Chessboard::check(char colour){
    //Check if the king of the given colour's is threatened
    if (colour == 'w'){
        //First, get the location of white king
        int whiteKingX, whiteKingY;
        for (Piece *p: whitePieces){
            if (p->name == 'K'){
                whiteKingX = p->x;
                whiteKingY = p->y;
                break;
            }
        }
        //Run through all black pieces, to see if they can reach white king in one valid move
        for (Piece *p: blackPieces){
            if (p->checkValidMove(whiteKingX, whiteKingY, this) == 2){
                //The white king can be captured
                return true;
            }
        }
        //If none of the enemy pieces can reach king, then it's not in check
        return false;
    }
    else{
        //First, get the location of black king
        int blackKingX, blackKingY;
        for (Piece *p: blackPieces){
            if (p->name == 'k'){
                blackKingX = p->x;
                blackKingY = p->y;
                break;
            }
        }
        //Run through all white pieces to see if they can reach black king in one valid move
        for (Piece *p: whitePieces){
            if (p->checkValidMove(blackKingX, blackKingY, this) == 2){
                //The white king can be captured
                return true;
            }
        }
        //If none of the enemy pieces can reach king, then it's not in check
        return false;
    }
}

bool Chessboard::checkmate(char colour){
    //In order for checkmate to hold, the king must first be in check
    if (!check(colour)) return false;
    if (colour == 'w'){
        for (Piece *p: whitePieces){
            int px = p->x, py = p->y; //Stores original position of the piece
            //Check if the white piece has no place to move
            //If there are still moves possible that gets king out of check, then it's not checkmate
            vector<pair<int, int>> pMoves = p->findMoves(this);
            for (auto i: pMoves){
                //Try making this move
                p->setPiece(i.first, i.second);
                //If it's not in check
                if (!check(colour)){
                    //Move back the piece
                    p->setPiece(px, py);
                    return false;
                }
                //Move back the piece
                p->setPiece(px, py);
            }
            //Next, check if the white piece has no enemy piece to capture
            //If there are still captures possible that gets king out of check, then it's not checkmate
            vector<pair<int, int>> pCaptures = p->findCaptures(this);
            for (auto i: pCaptures){
                //Try making this capture
                Piece *captured = location(i.first, i.second);
                captured->setPiece(-1, -1); //Move out of the board
                p->setPiece(i.first, i.second); //Move white piece to captured spot
                //If it's not in check
                if (!check(colour)){
                    //Move back the piece
                    p->setPiece(px, py);
                    captured->setPiece(i.first, i.second);
                    return false;
                }
                //Move back the piece
                p->setPiece(px, py);
                captured->setPiece(i.first, i.second);
            }
        }
        //If no moves can save king, it's checkmate
        return true;
    }
    else{
        for (Piece *p: blackPieces){
            int px = p->x, py = p->y; //Stores original position of the piece
            //Check if the black piece has no place to move
            //If there are still moves possible that gets king out of check, then it's not checkmate
            vector<pair<int, int>> pMoves = p->findMoves(this);
            for (auto i: pMoves){
                //Try making this move
                p->setPiece(i.first, i.second);
                //If it's not in check
                if (!check(colour)){
                    //Move back the piece
                    p->setPiece(px, py);
                    return false;
                }
                //Move back the piece
                p->setPiece(px, py);
            }
            //Next, check if the black piece has no enemy piece to capture
            //If there are still captures possible that gets king out of check, then it's not checkmate
            vector<pair<int, int>> pCaptures = p->findCaptures(this);
            for (auto i: pCaptures){
                //Try making this capture
                Piece *captured = location(i.first, i.second);
                captured->setPiece(-1, -1); //Move out of the board
                p->setPiece(i.first, i.second); //Move black piece to captured spot
                //If it's not in check
                if (!check(colour)){
                    //Move back the piece
                    p->setPiece(px, py);
                    captured->setPiece(i.first, i.second);
                    return false;
                }
                //Move back the piece
                p->setPiece(px, py);
                captured->setPiece(i.first, i.second);
            }
        }
        //If no moves can save king, it's checkmate
        return true;
    }
}

bool Chessboard::stalemate(char colour){
    //In order for the game to be stalemate,
    //The colour in turn should not be in check, and every move/capture gets in check
    //Condition 1: The king must not be in check
    if (check(colour)) return false;
    //Condition 2: For every possible move, it gets the king into check
    if (colour == 'b'){
        for (Piece *p: blackPieces){
            int px = p->x, py = p->y; //Stores original position of the piece
            vector<pair<int, int>> pMoves = p->findMoves(this);
            for (auto i: pMoves){
                //Try making this move
                p->setPiece(i.first, i.second);
                //If it's not in check
                if (!check('b')){
                    //Move back the piece
                    p->setPiece(px, py);
                    return false;
                }
                //Move back the piece
                p->setPiece(px, py);
            }
            //Next, check if every capture move gets black king into check
            vector<pair<int, int>> pCaptures = p->findCaptures(this);
            for (auto i: pCaptures){
                //Try making this capture
                Piece *captured = location(i.first, i.second);
                captured->setPiece(-1, -1); //Move out of the board
                p->setPiece(i.first, i.second); //Move black piece to captured spot
                //If it's not in check
                if (!check('b')){
                    //Move back the piece
                    p->setPiece(px, py);
                    captured->setPiece(i.first, i.second);
                    return false;
                }
                //Move back the piece
                p->setPiece(px, py);
                captured->setPiece(i.first, i.second);
            }
        }
    }
    else{
        //It is white's move
        for (Piece *p: whitePieces){
            int px = p->x, py = p->y; //Stores original position of the piece
            vector<pair<int, int>> pMoves = p->findMoves(this);
            for (auto i: pMoves){
                //Try making this move
                p->setPiece(i.first, i.second);
                //If it's not in check
                if (!check('w')){
                    //Move back the piece
                    p->setPiece(px, py);
                    return false;
                }
                //Move back the piece
                p->setPiece(px, py);
            }
            //Next, check if every capture move gets white king into check
            vector<pair<int, int>> pCaptures = p->findCaptures(this);
            for (auto i: pCaptures){
                //Try making this capture
                Piece *captured = location(i.first, i.second);
                captured->setPiece(-1, -1); //Move out of the board
                p->setPiece(i.first, i.second); //Move white piece to captured spot
                //If it's not in check
                if (!check('w')){
                    //Move back the piece
                    p->setPiece(px, py);
                    captured->setPiece(i.first, i.second);
                    return false;
                }
                //Move back the piece
                p->setPiece(px, py);
                captured->setPiece(i.first, i.second);
            }
        }
    }
    //Otherwise, it's in a stalemate
    return true;
}

Chessboard::~Chessboard() {
    //Clear all pieces used
    for (Piece *p: blackPieces) delete p;
    blackPieces.clear();
    for (Piece *p: whitePieces) delete p;
    whitePieces.clear();
}

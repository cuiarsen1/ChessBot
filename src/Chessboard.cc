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
        index++;
    }
    index = 0;
    for (Piece *p: whitePieces){
        if (p->x == x && p->y == y){
            whitePieces.erase(whitePieces.begin() + index);
            delete p;
        }
        index++;
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
    for (int i = 8; i < 16; i++) newPiece(1, i - 8, 'p');
    newPiece(7, 4, 'K');
    newPiece(7, 3, 'Q');
    newPiece(7, 0, 'R');
    newPiece(7, 7, 'R');
    newPiece(7, 2, 'B');
    newPiece(7, 5, 'B');
    newPiece(7, 1, 'N');
    newPiece(7, 6, 'N');
    for (int i = 8; i < 16; i++) newPiece(6, i - 8, 'P');
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
        return 1;
    }
    if (status == 2){
        //Capture piece at target spot
        //Note that normally, we would call removePiece(targetX, targetY)
        //However, the capture might result in a check, thus making the move invalid
        //Thus, we first move the oldTarget off the chessboard to test for check
        //If it does result in a check, revert the changes
        //If not, then call removePiece(oldTarget)
        Piece *oldTarget = location(targetX, targetY);
        oldTarget->setPiece(8, 8); //Move old target off the chessboard
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
            //Stored at the temporary (8, 8) position
            removePiece(8, 8);
            return 2;
        }
    }
    if (status == 3){
        //Promotion
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
        int whiteKingX = -1, whiteKingY = -1;
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
        int blackKingX = -1, blackKingY = -1;
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
    for (Piece *p: whitePieces) delete p;
}
/*Chessboard::Chessboard(){
    board[0][0] = new Square(0, 0,'R','B'); //B for Black, R for Rook
    board[0][1] = new Square(0, 1,'K','B');
    board[0][2] = new Square(0, 2,'B','B');
    board[0][3] = new Square(0, 3,'Q','B');
    board[0][4] = new Square(0, 4,'X','B'); //X for king for now 
    board[0][5] = new Square(0, 5,'B','B');
    board[0][6] = new Square(0, 6,'K','B');
    board[0][7] = new Square(0, 7,'R','B');
    for (int i = 0; i < 8; i++){
      board[1][i] = new Square(1, i,'P','B');
    }
    board[7][0] = new Square(0, 0,'R','W'); //W for White, R for Rook
    board[7][1] = new Square(0, 1,'K','W');
    board[7][2] = new Square(0, 2,'B','W');
    board[7][3] = new Square(0, 3,'Q','W');
    board[7][4] = new Square(0, 4,'X','W'); //X for king for now 
    board[7][5] = new Square(0, 5,'B','W');
    board[7][6] = new Square(0, 6,'K','W');
    board[7][7] = new Square(0, 7,'R','W');
    for (int i = 0; i < 8; i++){
      board[6][i] = new Square(6, i,'P','W');
    }
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            //if (!isOccupied()){
              //Square* blank = new Square(i, j);
              //std::cout<<"w";
              board[i][j] = new Square(i, j);
              
              //delete blank;
            //}
        }
    }
}

Chessboard::~Chessboard() {
    for (int i = 0; i < 8; ++i) {
     for (int j = 0; j < 8; j++)
        delete board[i][j];
    }
}

bool Chessboard::isOccupied(int x, int y){
    //std::cout<<"x";
    char piece = board[x][y]->getPiece();
    std::cout<<piece;
    if (piece == 'P' || piece == 'R' || piece == 'K' || piece == 'B' || piece == 'Q' || piece == 'X'){
        return true;
    }
    return false;
}

void Chessboard::printChessboard(){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (isOccupied(i,j)){
                std::cout<<board[i][j]->getPiece();
            }
            else{
                std::cout<<' ';
            }
        }
        std::cout << std::endl;
    }
}*/



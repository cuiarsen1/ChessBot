#include <iostream>
#include "Chessboard.h"
#include "Square.h"
#include "studio.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Queen.h"
#include "King.h"
#include "Empty.h"

using namespace std;

bool verify(Studio &s) {
    bool valid = true;
    bool wking = false;
    bool bking = false;

    for (int i = 1; i <= 8; i += 1) {
        for (int j = 1; j <= 8; j += 1) {
            if (s.picture()->pieceAt(i, j) == 'K') {
                if (wking == false) {
                    wking = true;
                } else {
                    valid = false;
                    return valid;
                }
                // verify king not in check
            } else if (s.picture()->pieceAt(i, j) == 'k') {
                if (bking == false) {
                    bking = true;
                } else {
                    valid = false;
                    return valid;
                }
                // verify king not in check
            } else if (i == 1 || i == 8) {
                if (s.picture()->pieceAt(i, j) == 'P' || s.picture()->pieceAt(i, j) == 'p') {
                    valid = false;
                    return valid;
                }
            }
        }
    }

    if (wking && bking) {
        return valid;
    }

    return false;
}

int main() {
    
    Chessboard *board = new Square;
    
    Studio s{board};
    
    string command;
    bool done = false;

    cin >> command;
    while (cin >> command) {
        if (command == "setup"){
            done = false;
            while (!done){
                cin >> command;
                if (command == "+"){
                    char piece;
                    char pos1;
                    int pos2;
                    cin >> piece >> pos1 >> pos2;
                    if (piece == 'R'){
                        s.picture() = new Rook(pos2, pos1-'a'+1,'w', s.picture());
                    }
                    else if (piece == 'r'){
                        s.picture() = new Rook(pos2, pos1-'a'+1,'b', s.picture());
                    }
                    else if (piece == 'N'){
                        s.picture() = new Knight(pos2, pos1-'a'+1,'w', s.picture());
                    }
                    else if (piece == 'n'){
                        s.picture() = new Knight(pos2, pos1-'a'+1,'b', s.picture());
                    }
                    else if (piece == 'B'){
                        s.picture() = new Bishop(pos2, pos1-'a'+1,'w', s.picture());
                    }
                    else if (piece == 'b'){
                        s.picture() = new Bishop(pos2, pos1-'a'+1,'b', s.picture());
                    }
                    else if (piece == 'Q'){
                        s.picture() = new Queen(pos2, pos1-'a'+1,'w', s.picture());
                    }
                    else if (piece == 'q'){
                        s.picture() = new Queen(pos2, pos1-'a'+1,'b', s.picture());
                    }
                    else if (piece == 'K'){
                        s.picture() = new King(pos2, pos1-'a'+1,'w', s.picture());
                    }
                    else if (piece == 'k'){
                        s.picture() = new King(pos2, pos1-'a'+1,'b', s.picture());
                    }
                    else if (piece == 'P'){
                        s.picture() = new Pawn(pos2, pos1-'a'+1,'w', s.picture());
                    }
                    else if (piece == 'p'){
                        s.picture() = new Pawn(pos2, pos1-'a'+1,'b', s.picture());
                    }
                }
                else if (command == "-"){
                    char pos1;
                    int pos2;
                    cin >> pos1 >> pos2;
                    s.picture() = new Empty(pos2, pos1-'a'+1,s.picture());   //questionable
                }
                else if (command == "="){
                    char colour;
                    if (colour == 'w'){         //white's turn 
                        //to be implemented
                    }
                    else if (colour == 'b'){         //black's turn 
                        //to be implemented
                    }
                }
                else if (command == "done"){
                    if (verify(s) == true) {
                        done = true;
                        cout << "setup mode is complete" << endl;
                    } else {
                        cout << "setup mode is invalid" << endl;
                    }
                }
                else if (command == "render"){
                    s.render();
                }
            }
        }
        /*else if (command == "move"){
            char pos1, endPos1;
            int pos2, endPos2;
            std::cin >> pos1 >> pos2 >> endPos1 >> endPos2;
            char piece = s.picture()->pieceAt(pos2, pos1-'a'+1);
            if (piece == 'R'){
                s.picture() = new Rook(pos2, pos1-'a','w', s.picture());
            }
            else if (piece == 'r'){
                s.picture() = new Rook(pos2, pos1-'a','b', s.picture());
            }
            else if (piece == 'N'){
                s.picture() = new Knight(pos2, pos1-'a','w', s.picture());
            }
            else if (piece == 'n'){
                s.picture() = new Knight(pos2, pos1-'a','b', s.picture());
            }
            else if (piece == 'B'){
                s.picture() = new Bishop(pos2, pos1-'a','w', s.picture());
            }
            else if (piece == 'b'){
                Bishop* b = new Bishop(pos2, pos1-'a','b', s.picture());
                if (b->checkValidMove(pos2, pos1-'a', pos2, pos1-'a')){
                    s.picture() = new Bishop(pos2, pos1-'a','b', s.picture());
                    s.picture() = new Empty(pos2, pos1-'a', s.picture());
                }  
            }
            else if (piece == 'Q'){
                s.picture() = new Queen(pos2, pos1-'a','w', s.picture());
            }
            else if (piece == 'q'){
                s.picture() = new Queen(pos2, pos1-'a','b', s.picture());
            }
            else if (piece == 'K'){
                s.picture() = new King(pos2, pos1-'a','w', s.picture());
            }
            else if (piece == 'k'){
                s.picture() = new King(pos2, pos1-'a','b', s.picture());
            }
            else if (piece == 'P'){
                s.picture() = new Pawn(pos2, pos1-'a','w', s.picture());
            }
            else if (piece == 'p'){
                s.picture() = new Pawn(pos2, pos1-'a','b', s.picture());
            }
        }*/
    }
}






    /*
        if (command == "render" ) {
            s.render();
        }
        else if (command == "Rook") {
            int row, col;
            std::cin >> row >> col;
            s.picture() = new Rook(row, col, s.picture());
        }
        else if (command == "Knight") {
            int row, col;
            std::cin >> row >> col;
            s.picture() = new Knight(row, col, s.picture());
        }
        else if (command == "Bishop") {
            int row, col;
            std::cin >> row >> col;
            s.picture() = new Bishop(row, col, s.picture());
        }
        else if (command == "Queen") {
            int row, col;
            std::cin >> row >> col;
            s.picture() = new Queen(row, col, s.picture());
        }
        else if (command == "King") {
            int row, col;
            std::cin >> row >> col;
            s.picture() = new King(row, col, s.picture());
        }
        else if (command == "Pawn") {
            int row, col;
            std::cin >> row >> col;
            s.picture() = new Pawn(row, col, s.picture());
        }
    }


   // Chessboard* c = new Chessboard();
   // c->printChessboard();

}*/
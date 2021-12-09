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

using namespace std;

int main(){
    Chessboard *board = new Square;

    Studio s{board};

    std::string command;

    bool done = false;

    while (std::cin >> command) {
        if (command == "setup"){
            done = false;
            while (!done){
                std::cin >> command;
                if (command == "+"){
                    char piece;
                    char pos1;
                    int pos2;
                    std::cin >> piece >> pos1 >> pos2;
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
                         s.picture() = new Bishop(pos2, pos1-'a','b', s.picture());
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
                }
                else if (command == "-"){
                    char pos1;
                    int pos2;
                    std::cin >> pos1 >> pos2;
                    s.picture() = new Square;   //questionable
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
                    //if (verify()){    // need a function to verify every requirement is satisfied
                        done = true; 
                        cout << "setup mode is complete" << endl;
                    /*}                 
                    else {
                        cout << "setup mode is invalid" << endl;
                    }   */

                }
                else if (command == "render"){
                    s.render();
                }
            }
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
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

int main() {
    Chessboard *board = new Square;
    
    Studio s{board};
    
    string command;
    bool done = false;
    bool custom = false;

    char turn = 'w';

    while (cin >> command) {
        if (command == "setup"){
            done = false;
            custom = true;
            while (!done){
                cin >> command;
                if (command == "+"){
                    char piece;
                    char pos1;
                    int pos2;
                    cin >> piece >> pos1 >> pos2;
                    //First check if the target location already has a piece
                    s.picture()->removePiece(8-pos2, pos1-'a');
                    s.picture()->newPiece(8-pos2, pos1-'a', piece);
                    s.render();
                }
                else if (command == "-"){
                    char pos1;
                    int pos2;
                    cin >> pos1 >> pos2;
                    s.picture()->removePiece(8-pos2, pos1-'a');
                    s.render();
                }
                else if (command == "="){
                    char colour;
                    cin >> colour;
                    if (colour == 'w'){     //white's turn
                        cout << "White's Turn" << endl;
                        turn = 'w';
                    }
                    else if (colour == 'b'){    //black's turn
                        cout << "Black's Turn" << endl;
                        turn = 'b';
                    }
                }
                else if (command == "done"){
                    if (s.picture()->verify()) {
                        done = true;
                        cout << "setup mode is complete" << endl;
                    } else {
                        cout << "setup mode is invalid" << endl;
                    }
                }
            }
        } else if (command == "game"){
            if (!custom){
                //Use default board
                s.picture()->init();
            }
            //Otherwise, use the board from setup mode
            string playerW, playerB;
            cin >> playerW >> playerB;

            bool gameOver = false;

            bool whiteWin = false;
            bool blackWin = false;
            double pointsW = 0;
            double pointsB = 0;

            bool humanW = true;
            bool humanB = true;
            bool validW = false;
            bool validB = false;

            while (!validW || !validB) {
                if (playerW == "computer1" || playerW == "computer2" || playerW == "computer3" || playerW == "computer4") {
                    humanW = false;
                    validW = true;
                } else if (playerW == "human") {
                    humanW = true;
                    validW = true;
                }

                if (playerB == "computer1" || playerB == "computer2" || playerB == "computer3" || playerB == "computer4") {
                    humanB = false;
                    validB = true;
                } else if (playerB == "human") {
                    humanB = true;
                    validB = true;
                }

                if (validW && validB) {
                    break;
                } else {
                    cout << "Invalid game setup, try again" << endl;
                    validW = false;
                    validB = false;
                    cin >> command;
                    if (command == "game") {
                        cin >> playerW >> playerB;
                    } else if (cin.eof()) {
                        // Print scores
                    }
                }
            }
            whiteWin = false;
            blackWin = false;

            while (!gameOver) {

                if (turn == 'w' && !humanW) {
                    // Call correct AI function (1-4) move white piece
                    // If checkmate, gameOver = true, whiteWin = true
                    // If there is no possible move to be made, gameOver = true. If in check, blackWin = true
                    turn = 'b';
                } else if (turn == 'b' && !humanB) {
                    // Call correct AI function (1-4) move black piece
                    // If checkmate, gameOver = true, blackWin = true
                    // If there is no possible move to be made, gameOver = true. If in check, whiteWin = true
                    turn = 'w';
                } else if (turn == 'w' && humanW) {
                    bool validTurn = false;

                    while (!validTurn) {
                        cin >> command;
                        if (command == "move") {
                            char pos1, endPos1;
                            int pos2, endPos2;
                            cin >> pos1 >> pos2 >> endPos1 >> endPos2;
                            int result = s.picture()->move(8-pos2, pos1-'a', 8-endPos2, endPos1-'a');
                            cout << "DEBUG RESULT " << result << endl;
                            cout << "DEBUG check move success " << s.picture()->location(8-endPos2, endPos1-'a')->name << endl;
                            if (result != 0) validTurn = true;

                            //Check
                            if (s.picture()->check('b')){
                                cout << "DEBUG check black\n";
                            }
                            if (s.picture()->check('w')){
                                cout << "DEBUG check white\n";
                            }
                            if (s.picture()->checkmate('b')){
                                cout << "DEBUG checkmate black\n";
                            }
                            if (s.picture()->checkmate('w')){
                                cout << "DEBUG checkmate white\n";
                            }
                        } else if (command == "resign") {
                            blackWin = true;
                            validTurn = true;
                            gameOver = true;
                        } else if (command == "render") {
                            s.render();
                        }
                    }
                    cout << "TURN OVER\n";

                    // If checkmate, gameOver = true, whiteWin = true
                    // If there is no possible move to be made, gameOver = true. If in check, blackWin = true
                } else if (turn == 'b' && humanB) {
                    bool validTurn = false;

                    while (!validTurn) {
                        cin >> command;
                        if (command == "move") {
                            char pos1, endPos1;
                            int pos2, endPos2;
                            cin >> pos1 >> pos2 >> endPos1 >> endPos2;
                            int result = s.picture()->move(8-pos2, pos1-'a', 8-endPos2, endPos1-'a');
                            if (result != 0) validTurn = true;

                            //Check
                            if (s.picture()->check('b')){
                                cout << "DEBUG check black\n";
                            }
                            if (s.picture()->check('w')){
                                cout << "DEBUG check white\n";
                            }
                            if (s.picture()->checkmate('b')){
                                cout << "DEBUG checkmate black\n";
                            }
                            if (s.picture()->checkmate('w')){
                                cout << "DEBUG checkmate white\n";
                            }
                        } else if (command == "resign") {
                            whiteWin = true;
                            validTurn = true;
                            gameOver = true;
                        }
                    }
                    cout << "TURN OVER\n";

                    // If checkmate, gameOver = true, blackWin = true
                    // If there is no possible move to be made, gameOver = true. If in check, whiteWin = true
                }
            }
            
            if (whiteWin) {
                pointsW += 1;
            } else if (blackWin) {
                pointsB += 1;
            } else if (!blackWin && !whiteWin) {
                pointsW += 0.5;
                pointsB += 0.5;
            }
        }
         else if (cin.eof()) {
            // Print scores
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
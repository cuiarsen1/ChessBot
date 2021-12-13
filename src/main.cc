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
#include "Player.h"
#include "Human.h"
#include "Computer.h"
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
            if (!custom) s.picture()->init(); //Use default board
            //Otherwise, use the board from setup mode
            string playerWText, playerBText;
            cin >> playerWText >> playerBText;
            Player *playerW, *playerB;
            //Ensure both white and black players are valid
            if ((playerWText != "human" && playerWText != "computer1" &&
            playerWText != "computer2" && playerWText != "computer3" &&
            playerWText != "computer4") || (playerBText != "human" &&
            playerBText != "computer1" && playerBText != "computer2" &&
            playerBText != "computer3" && playerBText != "computer4")){
                cout << "Invalid players!\n";
                continue;
            }
            if (playerWText == "computer1") playerW = new Computer('w', 1);
            else if (playerWText == "computer2") playerW = new Computer('w', 2);
            else if (playerWText == "computer3") playerW = new Computer('w', 3);
            else if (playerWText == "computer4") playerW = new Computer('w', 4);
            else playerW = new Human('w');
            if (playerBText == "computer1") playerB = new Computer('b', 1);
            else if (playerBText == "computer2") playerB = new Computer('b', 2);
            else if (playerBText == "computer3") playerB = new Computer('b', 3);
            else if (playerBText == "computer4") playerB = new Computer('b', 4);
            else playerB = new Human('b');

            bool gameOver = false;

            bool whiteWin = false;
            bool blackWin = false;
            bool stalemate = false;
            double pointsW = 0;
            double pointsB = 0;

            while (!gameOver) {
                s.render();
                //Before each turn, check the current state of the chessboard
                cout << "CHECK\n";
                if (s.picture()->stalemate(turn)){
                    cout << "Stalemate!\n";
                    stalemate = true;
                    gameOver = true;
                    continue;
                }
                if (s.picture()->checkmate(turn)){
                    cout << (turn == 'b' ? "Black" : "White") << " is in checkmate!\n";
                    whiteWin = true;
                    gameOver = true;
                    continue;
                }
                else if (s.picture()->check(turn)){
                    cout << (turn == 'b' ? "Black" : "White") << " is in check!\n";
                }
                if (turn == 'w') {
                    bool result = playerW->turn(s.picture());
                    if (!result){ //Resign
                        cout << "DEBUG resigned or EOF\n";
                        gameOver = true;
                        blackWin = true;
                        continue;
                    }
                    else{
                        cout << "DEBUG move registered\n";
                    }
                    turn = 'b';
                }
                else {
                    bool result = playerB->turn(s.picture());
                    if (!result){ //Resign
                        cout << "DEBUG resigned or EOF\n";
                        gameOver = true;
                        whiteWin = true;
                        continue;
                    }
                    else{
                        cout << "DEBUG move registered\n";
                    }
                    turn = 'w';
                }
                //DEBUG
                s.render();
            }
            
            cout << "DEBUG game finished\n";
            if (whiteWin) {
                pointsW += 1;
            } else if (blackWin) {
                pointsB += 1;
            } else if (stalemate) {
                pointsW += 0.5;
                pointsB += 0.5;
            }
            cout << "DEBUG score: W " << pointsW << " B " << pointsB << endl;
        }
        else{
            cout << "Invalid menu command!\n";
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
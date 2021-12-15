#include "Human.h"
#include "Player.h"
#include "Chessboard.h"
#include "Piece.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

Human::Human(char colour): Player(colour) {}

bool Human::turn(Chessboard *component){
    //All the valid turns include: move __ __ and resign
    //For the sake of testing, render is also valid
    //Returns true if a move was made, false if resigned
    string turnLine;
    while (getline(cin, turnLine)){
        istringstream iss(turnLine);
        string cmd;
        iss >> cmd;
        if (cmd == "move"){
            string pos1, pos2;
            iss >> pos1 >> pos2;
            if (pos1.length() != 2 || pos2.length() != 2){
                cout << "Invalid position!\n";
                continue;
            }
            int startX = char(pos1[1]) - '0';
            int startY = char(pos1[0]) - 'a';
            //Next, check validity of startY
            if (!(startY >= 0 && startY <= 7)){
                cout << "Invalid column letter!\n";
                continue;
            }
            //Finally, check validity of startX
            //It's also a position, then 1 <= startX <= 8 for the input
            if (!(startX >= 1 && startX <= 8)){
                cout << "Invalid row letter!\n";
                continue;
            }
            int targetX = char(pos2[1]) - '0';
            int targetY = char(pos2[0]) - 'a';
            //Next, check validity of targetY
            if (!(targetY >= 0 && targetY <= 7)){
                cout << "Invalid column letter!\n";
                continue;
            }
            //Finally, check validity of targetX
            //It's also a position, then 1 <= targetX <= 8 for the input
            if (!(targetX >= 1 && targetX <= 8)){
                cout << "Invalid row letter!\n";
                continue;
            }
            //Next, adjust the values so it matches the chessboard indices
            startX = 8 - startX;
            targetX = 8 - targetX;
            //Before calling move, ensure the starting piece is of the Human's colour
            Piece *p = component->location(startX, startY);
            if (p == NULL){
                cout << "Invalid start location!\n";
                continue;
            }
            if (p->colour != colour){
                cout << "Invalid piece colour!\n";
                continue;
            }
            //Run the move to see the result
            int result = component->move(startX, startY, targetX, targetY);
            //If non-zero move, the move was successful
            if (result != 0){
                cout << ((colour == 'b') ? "Black" : "White") << " played ";
                cout << pos1 << " to " << pos2 << endl;
                if (result == 3){
                    //Promotion
                    bool donePromote = false;
                    string promotePiece;
                    while (!donePromote){
                        cout << "Which piece to promote to? ";
                        string promoteLine;
                        getline(cin, promoteLine);
                        istringstream iss(promoteLine);
                        iss >> promotePiece;
                        if (promotePiece == "queen"){
                            component->promote(targetX, targetY, ((colour == 'b') ? 'q' : 'Q'));
                            donePromote = true;
                        }
                        else if (promotePiece == "knight"){
                            component->promote(targetX, targetY, ((colour == 'b') ? 'n' : 'N'));
                            donePromote = true;
                        }
                        else if (promotePiece == "rook"){
                            component->promote(targetX, targetY, ((colour == 'b') ? 'r' : 'R'));
                            donePromote = true;
                        }
                        else if (promotePiece == "bishop"){
                            component->promote(targetX, targetY, ((colour == 'b') ? 'b' : 'B'));
                            donePromote = true;
                        }
                        else{
                            cout << "Invalid promoted piece!\n";
                        }
                    }
                    //Successful promotion
                    cout << "Promoted to " << promotePiece << endl;
                }
                return true;
            }
            else{
                cout << "Invalid move!\n";
                continue;
            }
        }
        else if (cmd == "resign"){
            return false; //Quit the game
        }
        else{
            cout << "Invalid in-game command!\n";
        }
    }
    return false; //Should not reach here
}

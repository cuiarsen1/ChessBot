#include "Human.h"
#include "Player.h"
#include "Chessboard.h"
#include "Piece.h"
#include <iostream>
#include <string>
using namespace std;

Human::Human(char colour): Player(colour) {}

bool Human::turn(Chessboard *component){
    //All the valid turns include: move __ __ and resign
    //For the sake of testing, render is also valid
    //Returns true if a move was made, false if resigned
    string cmd;
    while (cin >> cmd){
        if (cmd == "move"){
            char startYLetter, targetYLetter;
            int startXNumber, targetXNumber;
            cin >> startYLetter >> startXNumber >> targetYLetter >> targetXNumber;
            //Next, adjust the values so it matches the chessboard indices
            int startX = 8 - startXNumber;
            int startY = startYLetter - 'a';
            int targetX = 8 - targetXNumber;
            int targetY = targetYLetter - 'a';
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
                cout << (colour == 'b' ? "Black" : "White") << " played ";
                cout << startYLetter << startXNumber << " to " << targetYLetter << targetXNumber << endl;
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

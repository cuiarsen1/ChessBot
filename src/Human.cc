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
            int startX, targetX;
            cin >> startYLetter >> startX >> targetYLetter >> targetX;
            //Next, adjust the values so it matches the chessboard indices
            startX = 8 - startX;
            targetX = 8 - targetX;
            int startY = startYLetter - 'a';
            int targetY = targetYLetter - 'a';
            cout << "DEBUG human move " << startX << " " << startY << " " << targetX << " " << targetY << endl;
            //Before calling move, ensure the starting piece is of the Human's colour
            Piece *p = component->location(startX, startY);
            if (p == NULL){
                cout << "Invalid start location! Try again.\n";
                continue;
            }
            if (p->colour != colour){
                cout << "Invalid piece colour! Try again.\n";
                continue;
            }
            //Run the move to see the result
            int result = component->move(startX, startY, targetX, targetY);
            if (result != 0) return true; //If non-zero move, the move was successful
            else{
                cout << "Invalid move! Try again.\n";
                continue;
            }
        }
        else if (cmd == "resign"){
            return false; //Quit the game
        }
        else{
            cout << "Invalid command! Try again.\n";
        }
    }
    return false; //Should not reach here
}
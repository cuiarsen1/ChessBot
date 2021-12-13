#include "Computer.h"
#include "Player.h"
#include "Chessboard.h"
#include "Piece.h"
#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

Computer::Computer(char colour, int level): Player(colour), level{level} {}

bool Computer::turn(Chessboard *component){
    srand(time(NULL)); //Random seed
    if (level == 1) level1(component);
    return true; //As the computer never resigns, the move would always be valid
    //In addition, the cases of no move available are handled by the initial checks in game
}

void Computer::level1(Chessboard *component){
    //Strategy: for each piece of that color, find all possible moves & captures,
    //store them in two vectors (first storing starting location, second the target)
    //Then choose a random move to execute
    vector<pair<int, int>> start;
    vector<pair<int, int>> target;
    if (colour == 'b'){
        for (Piece *p: component->blackPieces){
            vector<pair<int, int>> pMoves = p->findMoves(component);
            for (auto i: pMoves){
                //Store into the starts and targets
                start.emplace_back(p->x, p->y);
                target.emplace_back(i.first, i.second);
            }
            vector<pair<int, int>> pCaptures = p->findCaptures(component);
            for (auto i: pCaptures){
                start.emplace_back(p->x, p->y);
                target.emplace_back(i.first, i.second);
            }
        }
    }else{
        for (Piece *p: component->whitePieces){
            vector<pair<int, int>> pMoves = p->findMoves(component);
            for (auto i: pMoves){
                //Store into the starts and targets
                start.emplace_back(p->x, p->y);
                target.emplace_back(i.first, i.second);
            }
            vector<pair<int, int>> pCaptures = p->findCaptures(component);
            for (auto i: pCaptures){
                start.emplace_back(p->x, p->y);
                target.emplace_back(i.first, i.second);
            }
        }
    }
    //Next, generate a random index for the computer's decision
    int index = rand() % int(target.size());
    cout << "DEBUG " << index << " chosen from " << target.size() << endl;
    //Make the move
    int startX = start[index].first;
    int startY = start[index].second;
    int targetX = target[index].first;
    int targetY = target[index].second;
    component->move(startX, startY, targetX, targetY);
    //Output the move
    cout << (colour == 'b' ? "Black" : "White") << " played ";
    cout << char('a'+startY) << 8-startX << " to " << char('a'+targetY) << 8-targetX << endl;
}
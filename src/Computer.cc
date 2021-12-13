#include "Computer.h"
#include "Player.h"
#include "Chessboard.h"
#include "Piece.h"
#include <iostream>
#include <vector>
using namespace std;

Computer::Computer(char colour, int level): Player(colour), level{level} {}

bool Computer::turn(Chessboard *component){
    
    if (level == 1) level1(component);
    else if (level == 2) level2(component);
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

void Computer::level2(Chessboard *component){
    //Strategy: have two target vectors instead
    //The first contains prioritized targets, namely capture and check
    //The second contains normal moves, in case there does not exist any prioritized targets
    vector<pair<int, int>> VIPStart;
    vector<pair<int, int>> VIPTarget;
    vector<pair<int, int>> LOWStart;
    vector<pair<int, int>> LOWTarget;
    if (colour == 'b'){
        for (Piece *p: component->blackPieces){
            int px = p->x, py = p->y;
            vector<pair<int, int>> pMoves = p->findMoves(component);
            for (auto i: pMoves){
                //Divide the cases so that moves that lead to check are prioritized
                //Try making the move
                p->setPiece(i.first, i.second);
                //If in check
                if (component->check('w')){
                    //Put in prioritized vector
                    VIPStart.emplace_back(px, py);
                    VIPTarget.emplace_back(i.first, i.second);
                    //Put the piece back
                    p->setPiece(px, py);
                }
                else{
                    //Otherwise, it's a non-prioritized move
                    LOWStart.emplace_back(px, py);
                    LOWTarget.emplace_back(i.first, i.second);
                    //Put the piece back
                    p->setPiece(px, py);
                }
            }
            //Since the rest are captures, they are already prioritized
            //Thus no need to divide into check capture or normal capture
            vector<pair<int, int>> pCaptures = p->findCaptures(component);
            for (auto i: pCaptures){
                VIPStart.emplace_back(p->x, p->y);
                VIPTarget.emplace_back(i.first, i.second);
            }
        }
    }
    else{
        for (Piece *p: component->whitePieces){
            int px = p->x, py = p->y;
            vector<pair<int, int>> pMoves = p->findMoves(component);
            for (auto i: pMoves){
                //Divide the cases so that moves that lead to check are prioritized
                //Try making the move
                p->setPiece(i.first, i.second);
                //If in check
                if (component->check('b')){
                    //Put in prioritized vector
                    VIPStart.emplace_back(px, py);
                    VIPTarget.emplace_back(i.first, i.second);
                    //Put the piece back
                    p->setPiece(px, py);
                }
                else{
                    //Otherwise, it's a non-prioritized move
                    LOWStart.emplace_back(px, py);
                    LOWTarget.emplace_back(i.first, i.second);
                    //Put the piece back
                    p->setPiece(px, py);
                }
            }
            //Since the rest are captures, they are already prioritized
            //Thus no need to divide into check capture or normal capture
            vector<pair<int, int>> pCaptures = p->findCaptures(component);
            for (auto i: pCaptures){
                VIPStart.emplace_back(p->x, p->y);
                VIPTarget.emplace_back(i.first, i.second);
            }
        }
    }
    if (!VIPTarget.size()){
        //There are no captures/checks available at the moment
        //Thus, choose from the non-prioritized moves
        //Next, generate a random index for the computer's decision
        int index = rand() % int(LOWTarget.size());
        //Make the move
        int startX = LOWStart[index].first;
        int startY = LOWStart[index].second;
        int targetX = LOWTarget[index].first;
        int targetY = LOWTarget[index].second;
        component->move(startX, startY, targetX, targetY);
        //Output the move
        cout << (colour == 'b' ? "Black" : "White") << " played ";
        cout << char('a'+startY) << 8-startX << " to " << char('a'+targetY) << 8-targetX << endl;
    }
    else{
        //Otherwise, only choose from the prioritized moves/captures
        //Next, generate a random index for the computer's decision
        int index = rand() % int(VIPTarget.size());
        //Make the move
        int startX = VIPStart[index].first;
        int startY = VIPStart[index].second;
        int targetX = VIPTarget[index].first;
        int targetY = VIPTarget[index].second;
        component->move(startX, startY, targetX, targetY);
        //Output the move
        cout << (colour == 'b' ? "Black" : "White") << " played ";
        cout << char('a'+startY) << 8-startX << " to " << char('a'+targetY) << 8-targetX << endl;
    }
}
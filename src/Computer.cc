#include "Computer.h"
#include "Player.h"
#include "Chessboard.h"
#include "Piece.h"
#include <iostream>
#include <vector>
#include <set>
#include <limits.h>
using namespace std;

vector<char> validPromotions{'q', 'n', 'r', 'b'};

Computer::Computer(char colour, int level): Player(colour), level{level} {}

bool Computer::turn(Chessboard *component){
    if (level == 1) level1(component);
    else if (level == 2) level2(component);
    else if (level == 3) level3(component);
    else if (level == 4) level4(component);
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
    int status = component->move(startX, startY, targetX, targetY);
    //Output the move
    cout << ((colour == 'b') ? "Black" : "White") << " played ";
    cout << char('a'+startY) << 8-startX << " to " << char('a'+targetY) << 8-targetX << endl;
    //Check promotion
    if (status == 3){
        //Choose a random piece for promotion
        char tempPromotion = validPromotions[rand() % 4];
        cout << "Promoted to ";
        if (tempPromotion == 'q') cout << "queen\n";
        else if (tempPromotion == 'n') cout << "knight\n";
        else if (tempPromotion == 'r') cout << "rook\n";
        else cout << "bishop\n";
        //Set it to correct colour
        if (colour == 'w') tempPromotion = toupper(tempPromotion);
        component->promote(targetX, targetY, tempPromotion);
    }
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
        int status = component->move(startX, startY, targetX, targetY);
        //Output the move
        cout << ((colour == 'b') ? "Black" : "White") << " played ";
        cout << char('a'+startY) << 8-startX << " to " << char('a'+targetY) << 8-targetX << endl;
        //Check promotion
        if (status == 3){
            //Always choose queen for promotion
            char tempPromotion = 'q';
            //Set it to correct colour
            if (colour == 'w') tempPromotion = toupper(tempPromotion);
            component->promote(targetX, targetY, tempPromotion);
            cout << "Promoted to queen\n";
        }
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
        int status = component->move(startX, startY, targetX, targetY);
        //Output the move
        cout << ((colour == 'b') ? "Black" : "White") << " played ";
        cout << char('a'+startY) << 8-startX << " to " << char('a'+targetY) << 8-targetX << endl;
        //Check promotion
        if (status == 3){
            //Always choose queen for promotion
            char tempPromotion = 'q';
            //Set it to correct colour
            if (colour == 'w') tempPromotion = toupper(tempPromotion);
            component->promote(targetX, targetY, tempPromotion);
            cout << "Promoted to queen\n";
        }
    }
}

void Computer::level3(Chessboard *component){
    //Strategy: avoid captures, perform checks, capture enemy pieces are preferences
    //Level 2 already does preference over checks and captures
    //Thus, level 3 should find a way to avoid captures
    //Method to find avoiding captures:
    //Follow the level 2 format
    //We already know checks and captures are preferred, thus no need to check for avoiding capture
    //Only check avoiding capture for plain moves
    //Try the move first, then loop through all enemy pieces to try to capture that new location
    //If any enemy piece can capture it, it's not prioritized
    //At the end of the loop, it would be prioritized, as it avoids being captured
    //Essentially, this removes all the plain moves from level 2 that immediately gets captured
    //Furthermore, to increase the difficulty of level 3 more, the captures will get processed as well
    //After trying each capture, also check if own piece may be captured (traded)
    //If not at all, it stays a prioritized move
    //Otherwise, if the value of the captured enemy piece > value of own sacrified piece,
    //Then it's a prioritized move
    //Else, it's not a proiritized move, as level 3 also prioritized avoiding (unnecessary) captures
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
                    //Run through all enemy pieces to see if this piece is reachable
                    bool targetable = false;
                    for (Piece *enemy: component->whitePieces){
                        int status = enemy->checkValidMove(i.first, i.second, component);
                        if (status != 0){
                            //Reachable; not ideal move
                            targetable = true;
                            break;
                        }
                    }
                    if (targetable){
                        //Low priority move
                        LOWStart.emplace_back(px, py);
                        LOWTarget.emplace_back(i.first, i.second);
                    }
                    else{
                        //High priority move
                        VIPStart.emplace_back(px, py);
                        VIPTarget.emplace_back(i.first, i.second);
                    }
                    //Put the piece back
                    p->setPiece(px, py);
                }
            }
            //Captures next
            //Run similar check as move above
            vector<pair<int, int>> pCaptures = p->findCaptures(component);
            for (auto i: pCaptures){
                //Try the capture
                Piece *captured = component->location(i.first, i.second);
                captured->setPiece(-1, -1);
                p->setPiece(i.first, i.second);
                bool targetable = false;
                //Run through all enemy pieces if the piece can be captured
                for (Piece *enemy: component->whitePieces){
                    int status = enemy->checkValidMove(i.first, i.second, component);
                    if (status != 0){
                        //Capturable; compare the point values
                        if (p->value < captured->value){
                            //The piece captured has a greater score than own piece used
                            //Not enough for a trade; not prioritized capture
                            targetable = true;
                            break;
                        }
                    }
                }
                if (targetable){
                    //Not priority
                    LOWStart.emplace_back(px, py);
                    LOWTarget.emplace_back(i.first, i.second);
                }
                else{
                    VIPStart.emplace_back(px, py);
                    VIPTarget.emplace_back(i.first, i.second);
                }
                //Put the pieces back
                p->setPiece(px, py);
                captured->setPiece(i.first, i.second);
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
                    //Run through all enemy pieces to see if this piece is reachable
                    bool targetable = false;
                    for (Piece *enemy: component->blackPieces){
                        int status = enemy->checkValidMove(i.first, i.second, component);
                        if (status != 0){
                            //Reachable; not ideal move
                            targetable = true;
                            break;
                        }
                    }
                    if (targetable){
                        //Low priority move
                        LOWStart.emplace_back(px, py);
                        LOWTarget.emplace_back(i.first, i.second);
                    }
                    else{
                        //High priority move
                        VIPStart.emplace_back(px, py);
                        VIPTarget.emplace_back(i.first, i.second);
                    }
                    //Put the piece back
                    p->setPiece(px, py);
                }
            }
            //Captures next
            //Run similar check as move above
            vector<pair<int, int>> pCaptures = p->findCaptures(component);
            for (auto i: pCaptures){
                //Try the capture
                Piece *captured = component->location(i.first, i.second);
                captured->setPiece(-1, -1);
                p->setPiece(i.first, i.second);
                bool targetable = false;
                //Run through all enemy pieces if the piece can be captured
                for (Piece *enemy: component->blackPieces){
                    int status = enemy->checkValidMove(i.first, i.second, component);
                    if (status != 0){
                        //Capturable; compare the point values
                        if (p->value < captured->value){
                            //The piece captured has a greater score than own piece used
                            //Not enough for a trade; not prioritized capture
                            targetable = true;
                            break;
                        }
                    }
                }
                if (targetable){
                    //Not priority
                    LOWStart.emplace_back(px, py);
                    LOWTarget.emplace_back(i.first, i.second);
                }
                else{
                    VIPStart.emplace_back(px, py);
                    VIPTarget.emplace_back(i.first, i.second);
                }
                //Put the pieces back
                p->setPiece(px, py);
                captured->setPiece(i.first, i.second);
            }
        }
    }
    if (VIPTarget.size() != 0){
        //Only choose from the prioritized moves/captures
        //Next, generate a random index for the computer's decision
        int index = rand() % int(VIPTarget.size());
        //Make the move
        int startX = VIPStart[index].first;
        int startY = VIPStart[index].second;
        int targetX = VIPTarget[index].first;
        int targetY = VIPTarget[index].second;
        int status = component->move(startX, startY, targetX, targetY);
        //Output the move
        cout << ((colour == 'b') ? "Black" : "White") << " played ";
        cout << char('a'+startY) << 8-startX << " to " << char('a'+targetY) << 8-targetX << endl;
        //Check promotion
        if (status == 3){
            //Always choose queen for promotion
            char tempPromotion = 'q';
            //Set it to correct colour
            if (colour == 'w') tempPromotion = toupper(tempPromotion);
            component->promote(targetX, targetY, tempPromotion);
            cout << "Promoted to queen\n";
        }
    }
    else{
        //There are no prioritized moves available at the moment
        //Thus, choose from the non-prioritized moves
        //Next, generate a random index for the computer's decision
        int index = rand() % int(LOWTarget.size());
        //Make the move
        int startX = LOWStart[index].first;
        int startY = LOWStart[index].second;
        int targetX = LOWTarget[index].first;
        int targetY = LOWTarget[index].second;
        int status = component->move(startX, startY, targetX, targetY);
        //Output the move
        cout << ((colour == 'b') ? "Black" : "White") << " played ";
        cout << char('a'+startY) << 8-startX << " to " << char('a'+targetY) << 8-targetX << endl;
        //Check promotion
        if (status == 3){
            //Always choose queen for promotion
            char tempPromotion = 'q';
            //Set it to correct colour
            if (colour == 'w') tempPromotion = toupper(tempPromotion);
            component->promote(targetX, targetY, tempPromotion);
            cout << "Promoted to queen\n";
        }
    }
}

//Level 4: GLOBAL DEFENSIVE
//Strategy: consider the concept of a safe move/capture
//After performing the play, check the state of the chessboard
//Total the sum of all own targetable pieces, and divide by
//the total number of enemy moves available (pMoves + pCaptures) so that it
//represents the expected value of the points own player loses in next opponent turn
//Pawn 1, Knight 3, Bishop 3, Rook 5, Queen 9, King 10000 (theoretical)
//Check is given a value of 4, as a safe player usually wouldn't sacrifice queen/rook for a check
//NOTE: if capture, subtract the value of the piece taken out
//Have a third vector of integers (other than start and target) for move score
//Loop through the vector and find the minimum score (safest)
//Finally, choose a random move from all moves with score <= ceil(minimum score)
void Computer::level4(Chessboard *component){
    vector<pair<int, int>> start;
    vector<pair<int, int>> target;
    vector<int> score;
    if (colour == 'b'){
        //Loop through all moves
        for (Piece *p: component->blackPieces){
            int px = p->x, py = p->y;
            vector<pair<int, int>> pMoves = p->findMoves(component);
            for (auto i: pMoves){
                //Perform the move onto the unoccupied spot
                p->setPiece(i.first, i.second);
                //Next, calculate score
                int tempScore = 0;
                for (Piece *enemy: component->whitePieces){
                    //Only consider captures
                    for (auto j: enemy->findCaptures(component)){
                        //Add the score of the piece being captured
                        tempScore += component->location(j.first, j.second)->value;
                    }
                }
                //Since this is from our non-attack decision, there is nothing to subtract
                //However, a check is possible (value 4)
                if (component->check('w')) tempScore -= 4;
                //Put the piece back
                p->setPiece(px, py);
                //Finally, add to the total moves
                start.emplace_back(px, py);
                target.emplace_back(i.first, i.second);
                score.push_back(tempScore);
                
            }
            //Next, the captures
            vector<pair<int, int>> pCaptures = p->findCaptures(component);
            for (auto i: pCaptures){
                //Try the capture
                Piece *captured = component->location(i.first, i.second);
                captured->setPiece(-1, -1);
                p->setPiece(i.first, i.second);
                //Calculate score
                int tempScore = 0;
                for (Piece *enemy: component->whitePieces){
                    if (enemy == captured) continue; //Skip the supposedly eaten piece
                    //Only consider captures
                    for (auto j: enemy->findCaptures(component)){
                        //Add the score of the piece being captured
                        tempScore += component->location(j.first, j.second)->value;
                    }
                }
                //Since this is an attack, we subtract the difference between captured and p
                tempScore -= (captured->value - p->value);
                //A check is possible (value 4)
                if (component->check('w')) tempScore -= 4;
                //Put the pieces back
                p->setPiece(px, py);
                captured->setPiece(i.first, i.second);
                //Finally, add to the total moves
                start.emplace_back(px, py);
                target.emplace_back(i.first, i.second);
                score.push_back(tempScore);
            }
        }
    }
    else{
        //Loop through all moves
        for (Piece *p: component->whitePieces){
            int px = p->x, py = p->y;
            vector<pair<int, int>> pMoves = p->findMoves(component);
            for (auto i: pMoves){
                //Perform the move onto the unoccupied spot
                p->setPiece(i.first, i.second);
                //Next, calculate score
                int tempScore = 0;
                for (Piece *enemy: component->blackPieces){
                    //Only consider captures
                    for (auto j: enemy->findCaptures(component)){
                        //Add the score of the piece being captured
                        tempScore += component->location(j.first, j.second)->value;
                    }
                }
                //Since this is from our non-attack decision, there is nothing to subtract
                //However, a check is possible (value 4)
                if (component->check('w')) tempScore -= 4;
                //Put the piece back
                p->setPiece(px, py);
                //Finally, add to the total moves
                start.emplace_back(px, py);
                target.emplace_back(i.first, i.second);
                score.push_back(tempScore);
            }
            //Next, the captures
            vector<pair<int, int>> pCaptures = p->findCaptures(component);
            for (auto i: pCaptures){
                //Try the capture
                Piece *captured = component->location(i.first, i.second);
                captured->setPiece(-1, -1);
                p->setPiece(i.first, i.second);
                //Calculate score
                int tempScore = 0;
                for (Piece *enemy: component->blackPieces){
                    if (enemy == captured) continue; //Skip the supposedly eaten piece
                    //Only consider captures
                    for (auto j: enemy->findCaptures(component)){
                        //Add the score of the piece being captured
                        tempScore += component->location(j.first, j.second)->value;
                    }
                }
                //Since this is an attack, we subtract the difference between captured and p
                tempScore -= (captured->value - p->value);
                //A check is possible (value 4)
                if (component->check('w')) tempScore -= 4;
                //Put the pieces back
                p->setPiece(px, py);
                captured->setPiece(i.first, i.second);
                //Finally, add to the total moves
                start.emplace_back(px, py);
                target.emplace_back(i.first, i.second);
                score.push_back(tempScore);
            }
        }
    }
    //Find minimum value from scores vector
    int minScore = INT_MAX;
    for (int s: score) minScore = min(minScore, s);
    //Finally, have a vector track indices of all moves with score less than ceil(minScore)
    vector<int> minIndices;
    for (int i = 0; i < int(target.size()); ++i){
        if (score[i] == minScore) minIndices.push_back(i);
    }
    //Choose random index of minIndices's length
    int index = rand() % int(minIndices.size());
    //Make the move
    int startX = start[minIndices[index]].first;
    int startY = start[minIndices[index]].second;
    int targetX = target[minIndices[index]].first;
    int targetY = target[minIndices[index]].second;
    int status = component->move(startX, startY, targetX, targetY);
    //Output the move
    cout << ((colour == 'b') ? "Black" : "White") << " played ";
    cout << char('a'+startY) << 8-startX << " to " << char('a'+targetY) << 8-targetX << endl;
    //Check promotion
    if (status == 3){
        //Always choose queen for promotion
        char tempPromotion = 'q';
        //Set it to correct colour
        if (colour == 'w') tempPromotion = toupper(tempPromotion);
        component->promote(targetX, targetY, tempPromotion);
        cout << "Promoted to queen\n";
    }
}
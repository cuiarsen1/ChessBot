#include "Computer.h"
#include "Player.h"
#include "Chessboard.h"
#include "Piece.h"
#include <iostream>
#include <vector>
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
    cout << (colour == 'b' ? "Black" : "White") << " played ";
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
        cout << (colour == 'b' ? "Black" : "White") << " played ";
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
        cout << (colour == 'b' ? "Black" : "White") << " played ";
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
    //Pawn 1, Knight 3, Bishop 3, Rook 5, Queen 9, King 10000 (theoretical)
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
                //Try making the move
                p->setPiece(i.first, i.second);
                //If in check
                if (component->check('w')){
                    //Check; put in prioritized vector
                    VIPStart.emplace_back(px, py);
                    VIPTarget.emplace_back(i.first, i.second);
                    //Put the piece back
                    p->setPiece(px, py);
                }
                else{
                    //Otherwise, it's a non-prioritized move
                    //LEVEL3: avoid capture
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

void Computer::level4(Chessboard *component){
    //Strategy: prioritize "safe" moves/captures/checks
    //Get all captures & moves similar to level 2
    //For each element, loop through all enemy pieces and try capturing the piece
    //Note: before trying the capture, setPiece the piece to (targetx, targety) first
    //If move = 2 (capture), then the move isn't safe
    //If move = 0, then it's considered a safe move
    //To prioritize the priority (lol), we will have three vectors this time
    //High (safe checks/captures)
    //mid (safe moves + unsafe checks)
    //low (unsafe moves/captures)
    vector<pair<int, int>> HighStart;
    vector<pair<int, int>> HighTarget;
    vector<pair<int, int>> MidStart;
    vector<pair<int, int>> MidTarget;
    vector<pair<int, int>> LowStart;
    vector<pair<int, int>> LowTarget;
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
                    //The move is a check
                    //Next, loop through all enemy pieces while the move is already made
                    bool safe = true;
                    for (Piece *q: component->whitePieces){
                        //Get the outcome of theoretical move by opponent piece to
                        //take out the original moved piece
                        //Note that this can only be 0 or 2, as we know there's a piece
                        //at (i.first, i.second)
                        int tempMove = q->checkValidMove(i.first, i.second, component);
                        if (tempMove == 2){
                            safe = false;
                            break;
                        }
                    }
                    if (safe){
                        //Safe check; high
                        HighStart.emplace_back(px, py);
                        HighTarget.emplace_back(i.first, i.second);
                    }
                    else{
                        //Unsafe check; mid
                        MidStart.emplace_back(px, py);
                        MidTarget.emplace_back(i.first, i.second);
                    }
                    //Put the piece back
                    p->setPiece(px, py);
                }
                else{
                    //Otherwise, it's a non-prioritized move
                    bool safe = true;
                    for (Piece *q: component->whitePieces){
                        int tempMove = q->checkValidMove(i.first, i.second, component);
                        if (tempMove == 2){
                            safe = false;
                            break;
                        }
                    }
                    if (safe){
                        //Safe move; mid
                        MidStart.emplace_back(px, py);
                        MidTarget.emplace_back(i.first, i.second);
                    }
                    else{
                        //Unsafe move; low
                        LowStart.emplace_back(px, py);
                        LowTarget.emplace_back(i.first, i.second);
                    }
                    //Put the piece back
                    p->setPiece(px, py);
                }
            }
            //The rest are captures
            vector<pair<int, int>> pCaptures = p->findCaptures(component);
            for (auto i: pCaptures){
                bool safe = true;
                for (Piece *q: component->whitePieces){
                    int tempMove = q->checkValidMove(i.first, i.second, component);
                    if (tempMove == 2){
                        safe = false;
                        break;
                    }
                }
                if (safe){
                    //Safe capture; high
                    HighStart.emplace_back(px, py);
                    HighTarget.emplace_back(i.first, i.second);
                }
                else{
                    //Unsafe capture; low
                    LowStart.emplace_back(px, py);
                    LowTarget.emplace_back(i.first, i.second);
                }
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
                    //The move is a check
                    //Next, loop through all enemy pieces while the move is already made
                    bool safe = true;
                    for (Piece *q: component->blackPieces){
                        //Get the outcome of theoretical move by opponent piece to
                        //take out the original moved piece
                        //Note that this can only be 0 or 2, as we know there's a piece
                        //at (i.first, i.second)
                        int tempMove = q->checkValidMove(i.first, i.second, component);
                        if (tempMove == 2){
                            safe = false;
                            break;
                        }
                    }
                    if (safe){
                        //Safe check; high
                        HighStart.emplace_back(px, py);
                        HighTarget.emplace_back(i.first, i.second);
                    }
                    else{
                        //Unsafe check; mid
                        MidStart.emplace_back(px, py);
                        MidTarget.emplace_back(i.first, i.second);
                    }
                    //Put the piece back
                    p->setPiece(px, py);
                }
                else{
                    //Otherwise, it's a non-prioritized move
                    bool safe = true;
                    for (Piece *q: component->blackPieces){
                        int tempMove = q->checkValidMove(i.first, i.second, component);
                        if (tempMove == 2){
                            safe = false;
                            break;
                        }
                    }
                    if (safe){
                        //Safe move; mid
                        MidStart.emplace_back(px, py);
                        MidTarget.emplace_back(i.first, i.second);
                    }
                    else{
                        //Unsafe move; low
                        LowStart.emplace_back(px, py);
                        LowTarget.emplace_back(i.first, i.second);
                    }
                    //Put the piece back
                    p->setPiece(px, py);
                }
            }
            //The rest are captures
            vector<pair<int, int>> pCaptures = p->findCaptures(component);
            for (auto i: pCaptures){
                //Try the capture first
                Piece *oldTarget = component->location(i.first, i.second);
                oldTarget->setPiece(-1, -1);
                p->setPiece(i.first, i.second);
                bool safe = true;
                for (Piece *q: component->blackPieces){
                    int tempMove = q->checkValidMove(i.first, i.second, component);
                    if (tempMove == 2){
                        safe = false;
                        break;
                    }
                }
                if (safe){
                    //Safe capture; high
                    HighStart.emplace_back(px, py);
                    HighTarget.emplace_back(i.first, i.second);
                }
                else{
                    //Unsafe capture; low
                    LowStart.emplace_back(px, py);
                    LowTarget.emplace_back(i.first, i.second);
                }
                //Move the pieces back
                p->setPiece(px, py);
                oldTarget->setPiece(i.first, i.second);
            }
        }
    }
    if (HighTarget.size() != 0){
        //High priority exists; choose from here
        int index = rand() % int(HighTarget.size());
        //Make the move
        int startX = HighStart[index].first;
        int startY = HighStart[index].second;
        int targetX = HighTarget[index].first;
        int targetY = HighTarget[index].second;
        component->move(startX, startY, targetX, targetY);
        //Output the move
        cout << (colour == 'b' ? "Black" : "White") << " played ";
        cout << char('a'+startY) << 8-startX << " to " << char('a'+targetY) << 8-targetX << endl;
    }
    else if (MidTarget.size() != 0){
        //Mid priority exists; choose from here
        int index = rand() % int(MidTarget.size());
        //Make the move
        int startX = MidStart[index].first;
        int startY = MidStart[index].second;
        int targetX = MidTarget[index].first;
        int targetY = MidTarget[index].second;
        component->move(startX, startY, targetX, targetY);
        //Output the move
        cout << (colour == 'b' ? "Black" : "White") << " played ";
        cout << char('a'+startY) << 8-startX << " to " << char('a'+targetY) << 8-targetX << endl;
    }
    else{
        //Only low priority exists
        int index = rand() % int(LowTarget.size());
        //Make the move
        int startX = LowStart[index].first;
        int startY = LowStart[index].second;
        int targetX = LowTarget[index].first;
        int targetY = LowTarget[index].second;
        component->move(startX, startY, targetX, targetY);
        //Output the move
        cout << (colour == 'b' ? "Black" : "White") << " played ";
        cout << char('a'+startY) << 8-startX << " to " << char('a'+targetY) << 8-targetX << endl;
    }
}

//Level 5: GLOBAL DEFENSIVE
//Strategy: consider the concept of a safe move/capture (NO CHECK PRIORITY)
//After performing the play, check the state of the chessboard
//Have a score variable track the sum of all own targetable pieces
//Pawn 1, Knight 3, Bishop 3, Rook 5, Queen 9, King 10000 (theoretical)
//NOTE: if capture, subtract the value of the piece taken out
//Have a third vector (other than start and target) for move score
//Loop through the vector and find the minimum score (safest)
//Finally, choose a random move from all moves with score = minimum score
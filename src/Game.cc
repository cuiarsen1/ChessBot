#include <iostream>
#include <sstream>
#include <string>
#include "Game.h"
#include "Square.h"
#include "Human.h"
#include "Computer.h"
#include "Piece.h"
using namespace std;

//Vectors for testing
vector<string> validPlayers{"human", "computer1", "computer2", "computer3", "computer4"};
vector<char> validPieces{'K', 'k', 'Q', 'q', 'R', 'r', 'B', 'b', 'N', 'n', 'P', 'p'};

//Some notes to the structure of Game (for myself):
//Chessboard does NOT have to be recreated before/after every match
//This is because we can just delete all pieces in the two vectors instead
//Call Chessboard->reset() to achieve this
//However, the players do need to be recreated
//Ensure both players are deleted when a match concludes
//And is only reinitialized with user input (game HUMAN COMPUTER2)

//For the constructor, with the Chessboard not clearing after every match
//We must initialize it when the Game runs, thus new Chessboard() is called
//Furthermore, the observers should start up with the chessboard as well
Game::Game(): component{new Square}, TO{new TextObserver(component)}, 
        GO{new GraphicalObserver(component)}, playerB{NULL}, playerW{NULL}, 
        gameOver{false}, custom{false}, move{'w'},
        whiteScore{0}, blackScore{0} {}

void Game::interact(){
    //Read from user input until EOF
    //NOTE: to avoid cases such as "game human", where some input is missing,
    //but with "game" expecting one more input, then it reads takes the command on the next
    //line as the second parameter, I will use istringstream to handle user inputs.
    string interactLine;
    while (getline(cin, interactLine)){
        istringstream iss(interactLine);
        string interactCommand;
        iss >> interactCommand;
        if (interactCommand == "setup"){
            custom = true;
            setup();
        }
        else if (interactCommand == "game"){
            //First get the players in the game
            string whiteText, blackText;
            iss >> whiteText >> blackText;
            //First, make sure black given inputs are valid players
            //So cases such as "game human ai1" does not create a human player then throw error
            bool whiteValid = false, blackValid = false;
            for (string i: validPlayers){
                if (whiteText == i) whiteValid = true;
                if (blackText == i) blackValid = true;
            }
            //If any one of the players is invalid, the input is invalid
            if (!whiteValid || !blackValid){
                cout << "Invalid players!\n";
                continue;
            }
            //Otherwise, it is valid
            //Create the players
            if (whiteText == "computer1") playerW = new Computer('w', 1);
            else if (whiteText == "computer2") playerW = new Computer('w', 2);
            else if (whiteText == "computer3") playerW = new Computer('w', 3);
            else if (whiteText == "computer4") playerW = new Computer('w', 4);
            else playerW = new Human('w');
            if (blackText == "computer1") playerB = new Computer('b', 1);
            else if (blackText == "computer2") playerB = new Computer('b', 2);
            else if (blackText == "computer3") playerB = new Computer('b', 3);
            else if (blackText == "computer4") playerB = new Computer('b', 4);
            else playerB = new Human('b');
            //If setup mode wasn't used, use the default chessboard
            if (!custom) component->init();
            inGame();
        }
        else{
            cout << "Invalid command!\n";
        }
    }
}

void Game::setup(){
    string setupLine;
    while (getline(cin, setupLine)){
        istringstream iss(setupLine);
        string setupCommand;
        iss >> setupCommand;
        if (setupCommand == "+"){
            //Add piece
            char pieceChar;
            string pos;
            iss >> pieceChar >> pos;
            //First, check validity of the pieceChar
            bool pieceValid = false;
            for (char i: validPieces){
                if (i == pieceChar) pieceValid = true;
            }
            if (!pieceValid){
                cout << "Invalid piece to add!\n";
                continue;
            }
            if (pos.length() != 2){
                cout << "Invalid position!\n";
                continue;
            }
            //Next, check validity of posY
            int posX = char(pos[1]) - '0';
            int posY = char(pos[0]) - 'a';
            if (!(posY >= 0 && posY <= 7)){
                cout << "Invalid column letter!\n";
                continue;
            }
            //Finally, check validity of posX
            //It's also a position, then 1 <= posX <= 8 for the input
            if (!(posX >= 1 && posX <= 8)){
                cout << "Invalid row letter!\n";
                continue;
            }
            //After the input is verified, we add the piece
            //By definition, adding a piece to an existing piece's location would
            //replace the old piece
            //Thus, we remove the original piece of the given location first
            component->removePiece(8 - posX, posY);
            //Next, add the piece
            component->newPiece(8 - posX, posY, pieceChar);
            //Since a change has been registered, we render the observers
            component->renderObservers();
        }
        else if (setupCommand == "-"){
            //Remove piece
            string pos;
            iss >> pos;
            if (pos.length() != 2){
                cout << "Invalid position!\n";
                continue;
            }
            int posX = char(pos[1]) - '0';
            int posY = char(pos[0]) - 'a';
            //Next, check validity of posY
            if (!(posY >= 0 && posY <= 7)){
                cout << "Invalid column letter!\n";
                continue;
            }
            //Finally, check validity of posX
            //It's also a position, then 1 <= posX <= 8 for the input
            if (!(posX >= 1 && posX <= 8)){
                cout << "Invalid row letter!\n";
                continue;
            }
            //After the input is verified, we remove the piece
            component->removePiece(8 - posX, posY);
            //Since a change has been registered, we render the observers
            component->renderObservers();
        }
        else if (setupCommand == "="){
            //Set which side goes first
            char colourChar; //Default value space to avoid errors
            iss >> colourChar;
            //Input colour must be one of white and black
            if (colourChar != 'w' && colourChar != 'b'){
                cout << "Invalid color!\n";
                continue;
            }
            //If the input colour is valid, update the move bool
            move = colourChar;
            //Since the board is unaffected, the observers do not need to be notified
            //However, we should let the user know that the colour is updated
            cout << ((move == 'b') ? "Black" : "White") << " starts!\n";
        }
        else if (setupCommand == "c"){
            //Toggle castling allowed
            component->allowCastling = !component->allowCastling;
            cout << "Castling " << (component->allowCastling ? "allowed!\n" : "not allowed!\n");
        }
        else if (setupCommand == "e"){
            //Toggle en passant allowed
            component->allowEnPassant = !component->allowEnPassant;
            cout << "En passant " << (component->allowEnPassant ? "allowed!\n" : "not allowed!\n");
        }
        else if (setupCommand == "done"){
            //Exit setup mode
            //Before exiting, verify the chessboard is in a valid setup
            if (component->verify()){
                //Successful
                cout << "Setup mode is complete!\n";
                return;
            }
            //Otherwise, it's not a valid setup
            cout << "Setup is invalid!\n";
            continue;
        }
        else{
            cout << "Invalid setup command!\n";
        }
    }
}

void Game::inGame(){
    //Unlike setup, which would only exit when the user calls "done",
    //inGame exits when the game ends with one side winning, or a stalemate only
    //In other words, whether or not the function exits does not depend on user input
    string gameLine;
    while (!gameOver){
        //Render the board before every move, so the player knows the state
        component->renderObservers();
        cout << ((move == 'b') ? "Black" : "White") << "'s turn!\n";
        //If current side is in stalemate
        if (component->stalemate(move)){
            gameOver = true;
            cout << "Stalemate!\n";
            blackScore += 0.5;
            whiteScore += 0.5;
            break;
        }
        //Perform call to see if current side is in checkmate
        if (component->checkmate(move)){
            gameOver = true;
            cout << "Checkmate! " << ((move == 'b') ? "White" : "Black") << " wins!\n";
            if (move == 'b') ++whiteScore;
            else ++blackScore;
            break;
        }
        //If current side is in check
        else if (component->check(move)){
            cout << ((move == 'b') ? "Black" : "White") << " is in check!\n";
        }
        if (move == 'b'){
            //We first clear all available black en passants from last black round,
            //as the opponent has missed the time to perform en passant
            for (Piece *p: component->blackPieces) p->enPassant = false;
            bool result = playerB->turn(component);
            if (!result){
                //Resignation
                cout << "Black resigns!\n";
                ++whiteScore;
                gameOver = true;
                break;
            }
            //Otherwise, it was a valid move; switch sides for next move
            else move = 'w';
        }
        else{
            //We first clear all available black en passants from last white round,
            //as the opponent has missed the time to perform en passant
            for (Piece *p: component->whitePieces) p->enPassant = false;
            bool result = playerW->turn(component);
            if (!result){
                //Resignation
                cout << "White resigns!\n";
                ++blackScore;
                gameOver = true;
                break;
            }
            //Otherwise, it was a valid move; switch sides for next move
            else move = 'b';
        }
    }
    restart(); //Clear all memory used for current match
}

void Game::restart(){
    //To restart, first reset the chessboard
    component->reset();
    //Next, delete the two players
    delete playerB;
    playerB = NULL;
    delete playerW;
    playerW = NULL;
    //Reset the booleans "gameOver" and "custom"
    gameOver = false;
    custom = false;
    //By default, white starts first
    move = 'w';
}

void Game::score(){
    cout << "Final score:\n";
    cout << "White: " << whiteScore << endl;
    cout << "Black: " << blackScore << endl;
}

Game::~Game(){
    //Delete the observers, chessboard and the two players
    delete TO;
    delete GO;
    delete component;
    if (playerB != NULL) delete playerB;
    if (playerW != NULL) delete playerW;
}

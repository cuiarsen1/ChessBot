#include "GraphicalObserver.h"
#include "Xwindow.h"
#include "Chessboard.h"
#include "Piece.h"
#include <string>
GraphicalObserver::GraphicalObserver(Chessboard *component):
        component{component}, w{400, 400}
        { component->attach(this);}


void GraphicalObserver::render(){
    
    //draw chessboard
    int x = 0; int y = 0; int width = 50; int height = 50;
    bool switchColour = false;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (!switchColour){
                w.fillRectangle(x, y, width, height, Xwindow::White);
                switchColour = true;
            }
            else{
                w.fillRectangle(x, y, width, height, Xwindow::Red);
                switchColour = false;
            }
            x += width;
        }
        x=0;
        y+=height;
        switchColour = !switchColour;
    }

    int offsetX = width/2-2; int offsetY = height/2-3;
    x = 0; y = height;
    for (int i = 0; i < 8; i++){
      for (int j = 0; j < 8; j++){
        Piece* temp = component->location(i, j);      
        if (temp == NULL){
           x += width;
           continue;
        }
        w.drawString(x+offsetX, y-offsetY, std::string(1, temp->name));
        x += width;
      }
      x=0;
      y+=height;
    }
   
}

GraphicalObserver::~GraphicalObserver(){
    component->detach(this);
}



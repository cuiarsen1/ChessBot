#ifndef __GRAPHICALOBSERVER_H__
#define __GRAPHICALOBSERVER_H__
#include "Observer.h"
#include "Xwindow.h"

class Chessboard;

class GraphicalObserver: public Observer {
    Chessboard *component; //The TextObserver observes the chessboard
    Xwindow w;
public:
    GraphicalObserver(Chessboard *component);
    void render() override;
    ~GraphicalObserver();
};

#endif
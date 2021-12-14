#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include "Observer.h"

class Subject {
    //Realistically, this vector would always only have two elements,
    //Namely Text and Graphics observers
    //However, we will keep the notation of vector of observers
    std::vector<Observer*> observers;
public:
    Subject(); //Constructor
    void attach(Observer *o); //Used when the Chessboard is initialized
    void detach(Observer *o); //Used when the Chessboard is deleted
    void renderObservers(); //In our case, render both text and graphics
    virtual ~Subject() = 0;
};

#endif

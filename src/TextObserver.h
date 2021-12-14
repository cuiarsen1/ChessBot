#ifndef _TEXTOBSERVER_H
#define _TEXTOBSERVER_H
#include <iostream>
#include "Observer.h"

class Chessboard;

class TextObserver: public Observer {
  int rows = 8, cols = 8;
  std::ostream &out = std::cout;

  Chessboard *component; //The TextObserver observes the chessboard

 public:
  TextObserver(Chessboard *component);
  void render() override; //Notify function
  ~TextObserver();
};

#endif

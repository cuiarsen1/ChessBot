#ifndef STUDIO_H
#define STUDIO_H
#include <iostream>
class Chessboard;

class Studio {
  int rows = 8, cols = 8;
  std::ostream &out = std::cout;

  Chessboard *thePicture;

 public:
  explicit Studio(Chessboard *picture): thePicture{picture} {}

  Chessboard *&picture() { return thePicture; }
  void render();
  ~Studio();
};

#endif


#include "studio.h"
#include "Chessboard.h"


void Studio::render() {
  out << '+';
  char c;
  for (int j = 0; j < cols; ++j) {
    c = 'a' + j;
    out << c;
  }
  out << '+' << std::endl;
  for (int i = 0; i < rows; ++i) {
    out << i+1;
    for (int j = 0; j < cols; ++j) {
      out << picture()->pieceAt(i, j);
    }
    out << i+1 << std::endl;
  }
  out << '+';
  for (int j = 0; j < cols; ++j) {
    c = 'a' + j;
    out << c;
  } 
  out << '+' << std::endl;
}


Studio::~Studio() { delete thePicture; }


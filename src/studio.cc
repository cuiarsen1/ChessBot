#include "studio.h"
#include "Chessboard.h"


void Studio::render() {
  out << '+';
  for (int j = 0; j < cols; ++j) out << j;
  out << '+' << std::endl;
  for (int i = 0; i < rows; ++i) {
    out << i;
    for (int j = 0; j < cols; ++j) {
      out << picture()->pieceAt(i, j);
    }
    out << i << std::endl;
  }
  out << '+';
  for (int j = 0; j < cols; ++j) out << j;
  out << '+' << std::endl;
}


Studio::~Studio() { delete thePicture; }


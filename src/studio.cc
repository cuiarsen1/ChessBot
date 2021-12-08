#include "studio.h"
#include "Chessboard.h"


void Studio::render() {
  out << '+';
  for (int j = 0; j < cols; ++j) out << '-';
  out << '+' << std::endl;
  for (int i = 0; i < rows; ++i) {
    out << '|';
    for (int j = 0; j < cols; ++j) {
      out << picture()->pieceAt(i, j);
    }
    out << '|' << std::endl;
  }
  out << '+';
  for (int j = 0; j < cols; ++j) out << '-';
  out << '+' << std::endl;
  ++ticks;
}


Studio::~Studio() { delete thePicture; }


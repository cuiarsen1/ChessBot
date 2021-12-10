#include "studio.h"
#include "Chessboard.h"

void Studio::render() {
  out << '+';
  char c;
  for (int j = 1; j <= cols; ++j) {
    c = 'a' + j - 1;
    out << c;
  }
  out << std::endl;
  for (int i = 1; i <= rows; ++i) {
    out << i;
    for (int j = 1; j <= cols; ++j) {
      out << picture()->pieceAt(i, j);
    }

    out << std::endl;
  }

  out << std::endl;
}

Studio::~Studio() { delete thePicture; }


#include "studio.h"
#include "Chessboard.h"
#include "Piece.h"

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
      Piece *temp = picture()->location(i, j);
      if (temp == NULL) out << ' ';
      else out << temp->name;
    }

    out << std::endl;
  }

  out << std::endl;
}

Studio::~Studio() { delete thePicture; }


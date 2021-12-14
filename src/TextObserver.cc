#include "TextObserver.h"
#include "Chessboard.h"
#include "Piece.h"

TextObserver::TextObserver(Chessboard *component): component{component} {
  //Hook the observer onto the given chessboard
  component->attach(this);
}

//Render acts as the notify function in the Decorator pattern
//As every time a move is made, the TextObserver should print out the current state of the board
void TextObserver::render() {
  out << '+';
  char c;
  for (int j = 1; j <= cols; ++j) {
    c = 'a' + j - 1;
    out << c;
  }
  out << std::endl;
  for (int i = 0; i < rows; ++i) {
    out << 8 - i;
    for (int j = 0; j < cols; ++j) {
      Piece *temp = component->location(i, j);
      if (temp == NULL) out << ' ';
      else out << temp->name;
    }
    out << std::endl;
  }
}

TextObserver::~TextObserver() {
  //Remove the observer from the chessboard
  component->detach(this);
}

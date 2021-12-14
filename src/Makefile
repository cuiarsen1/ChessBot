CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD 
EXEC = cs246final
OBJECTS = main.o Game.o Chessboard.o Square.o Piece.o Pawn.o Knight.o Bishop.o Rook.o Queen.o King.o Player.o Human.o Computer.o Observer.o Subject.o TextObserver.o GraphicalObserver.o Xwindow.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXcXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}


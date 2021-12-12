CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD 
EXEC = cs246final
OBJECTS = main.o Chessboard.o Square.o Piece.o Pawn.o Knight.o Bishop.o Rook.o Queen.o King.o studio.o Empty.o Player.o Human.o Computer.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXcXFLAGS} ${OBJECTS} -o ${EXEC} 

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}


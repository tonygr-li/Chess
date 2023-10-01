CXX=g++
CXXFLAGS=-std=c++17 -Wall -g -MMD
EXEC=chess
SRC_DIRS=. game board observer output_stream piece square player graphics command
SRC_FILES=$(wildcard $(addsuffix /*.cc, $(SRC_DIRS)))
OBJECTS=$(SRC_FILES:.cc=.o)
DEPENDS=$(SRC_FILES:.cc=.d)

VALGRIND=valgrind
VALGRIND_FLAGS=--leak-check=full 

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}

run: ${EXEC}
	${VALGRIND} ${VALGRIND_FLAGS} ./$(EXEC)

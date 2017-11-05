## Makefile
## Author: Alexander Corley

DEBUG=
#DEBUG=-DDEBUG
CXX=c++
CXXFLAGS=-std=c++11 -pedantic -Wall -Werror -g $(DEBUG)
SOURCE=$(wildcard *.cpp)
OBJECTS=$(SOURCE:.cpp=.o)
EXE=AC3


EXE: $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE)

clean:
	rm -f $(OBJECTS) $(EXE)

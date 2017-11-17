## Makefile
## Author: Alexander Corley

DEBUG=
#DEBUG=-DDEBUG
CXX=g++
CXXFLAGS=-std=c++11 -pedantic -Wall -Werror -g $(DEBUG) -MMD
SOURCE=$(wildcard *.cpp)
OBJECTS=$(SOURCE:%.cpp=%.o)
EXE=solver

DEPS=$(OBJECTS:%.o=%.d)


rebuild: clean all

clean:
	rm -f $(OBJECTS) $(EXE) $(DEPS)

EXE: $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE)


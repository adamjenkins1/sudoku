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

EXE: $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE)

include $(DEPS)

clean:
	rm -f $(OBJECTS) $(EXE) $(DEPS)

CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++11

all:
	$(CXX) main.cpp $(CXXFLAGS)

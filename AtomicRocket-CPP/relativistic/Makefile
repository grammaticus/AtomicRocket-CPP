CXX = g++
CXXFLAGS = -Wall -g
INPUTS = main.cpp ship.cpp Terra.cpp
relativistic: main.cpp ship.cpp Terra.cpp
	$(CXX) $(INPUTS) -o relativistic.o $(CXXFLAGS)

.PHONY: clean

clean:
	rm relativistic

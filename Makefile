CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall

SRC = main.cpp vector.cpp writer.cpp voronoi.cpp
OBJ = $(SRC:.cpp=.o)
EXE = main

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) $(EXE)

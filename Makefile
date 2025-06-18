CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall

SRC = test_power_voronoi.cpp vector.cpp writer.cpp voronoi.cpp power_voronoi.cpp
OBJ = $(SRC:.cpp=.o)
EXE = test_power_voronoi

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) $(EXE)

CXX = g++
CC = gcc
CXXFLAGS = -std=c++11 -O2 -Wall
CFLAGS = -O2 -Wall

CPP_SRC = test_power_voronoi.cpp vector.cpp writer.cpp voronoi.cpp power_voronoi.cpp
C_SRC = lbfgs.c
OBJ = $(CPP_SRC:.cpp=.o) $(C_SRC:.c=.o)
EXE = test_power_voronoi

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(EXE)
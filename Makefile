CXX = g++
CC = gcc
CXXFLAGS = -std=c++11 -O2 -Wall
CFLAGS = -O2 -Wall

# Source files - removing optimal_transport.cpp since it doesn't exist
CPP_SRC = vector.cpp writer.cpp voronoi.cpp power_voronoi.cpp
C_SRC = lbfgs.c

# Power Voronoi target
POWER_OBJ = test_power_voronoi.o $(CPP_SRC:.cpp=.o) $(C_SRC:.c=.o)
POWER_EXE = test_power_voronoi

# SDOT target (without optimal_transport since it doesn't exist)
SDOT_OBJ = test_SDOT.o $(CPP_SRC:.cpp=.o) $(C_SRC:.c=.o)
SDOT_EXE = test_sdot

FLUIDS_OBJ = fluids.o $(CPP_SRC:.cpp=.o) $(C_SRC:.c=.o)
FLUIDS_EXE = fluids

all: $(POWER_EXE) $(SDOT_EXE) $(FLUIDS_EXE)

$(POWER_EXE): $(POWER_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(SDOT_EXE): $(SDOT_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(FLUIDS_EXE): $(FLUIDS_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(POWER_EXE) $(SDOT_EXE) $(FLUIDS_EXE)
	rm -f *.svg




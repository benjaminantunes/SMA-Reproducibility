CC = g++
SRC = src/RandomGenerator.cpp src/Grid.cpp src/Human.cpp src/Simulation.cpp
CFLAGS = -Wall -Wextra -O3 -Iinclude -std=gnu++11
LDFLAGS =

EXE = Tp1_multi_agent

OBJ=$(addprefix build/,$(SRC:.cpp=.o))
DEP=$(addprefix build/,$(SRC:.cpp=.d))

all: $(OBJ)
	$(CC) Tp1_multi_agent.cpp -o $(EXE) $^ $(CFLAGS)

build/%.o: %.cpp
	@mkdir -p build $(dir $@)
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm -rf build core *.o

run: all
	@./Tp1_multi_agent

-include $(DEP)

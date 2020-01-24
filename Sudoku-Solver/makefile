CC = g++

CFLAGS = -std=c++17 -I. -Ofast

DEPS = Backtracking.h

OBJ = main.o



EXE = solver


%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


test: $(EXE)
	./$(EXE)

CC = g++

CFLAGS = -std=c++17 -I. -Ofast

DEPS = helper.h

OBJ = main.o



EXE = calculator


%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


test: $(EXE)
	./$(EXE)

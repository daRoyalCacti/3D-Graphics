CC = g++

IDIR = dependencies
_DEPS = $(wildcard $(IDIR)/*.h)
DEPS = $(patsubst %,%,$(_DEPS))

SOURCE_DIR = source
ODIR = compiler_objects
_OBJ = $(wildcard $(SOURCE_DIR)/*.cpp)
OBJ =  $(patsubst $(SOURCE_DIR)/%.cpp,$(ODIR)/%.o,$(_OBJ)) $(ODIR)/main.o

CFLAGS = -std=c++17 -I$(IDIR) -lOpenCL -Ofast -fopenmp
WFLAGS =  -Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual

EXE=Generate




$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(WFLAGS)

$(ODIR)/%.o: $(SOURCE_DIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(WFLAGS)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(WFLAGS)


.PHONY: test clean

test: $(EXE)
	./$(EXE)

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~

wipe:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~ $(EXE)

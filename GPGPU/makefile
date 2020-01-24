CC = g++

IDIR = dependencies
_DEPS = openCl.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

ODIR = compiler_objects
_OBJ = main.o openCl.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


CFLAGS = -std=c++17 -I$(IDIR) -lOpenCL -Ofast -fopenmp
WFLAGS =  -Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual

EXE=Generate




$(ODIR)/%.o: %.cpp $(DEPS)
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

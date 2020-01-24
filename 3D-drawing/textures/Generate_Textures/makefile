CC = g++

IDIR = dependencies
_DEPS = writing.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

ODIR = compiler_objects
_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

LIBPNG_Path = /usr/include/libpng16/

CFLAGS = -std=c++17 -I$(IDIR) -I$(LIBPNG_Path) -lpng -Ofast -fopenmp

EXE=Generate




$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: test clean

test: $(EXE)
	./$(EXE)

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~

wipe:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~ $(EXE)

CC = g++

IDIR = dependencies
IDIR_GPU = ../GPGPU/dependencies
_DEPS = $(wildcard $(IDIR)/*.h)
_DEPS_GPU = $(wildcard $(IDIR_GPU)/*.h)
DEPS = $(patsubst %,%,$(_DEPS)) $(patsubst %,%,$(_DEPS_GPU))

SOURCE_DIR = source
SOURCE_DIR_GPU = ../GPGPU/source
ODIR = compiler_objects
_OBJ = $(wildcard $(SOURCE_DIR)/*.cpp)
_OBJ_GPU = $(wildcard $(SOURCE_DIR_GPU)/*.cpp)
OBJ =  $(patsubst $(SOURCE_DIR)/%.cpp,$(ODIR)/%.o,$(_OBJ)) $(patsubst $(SOURCE_DIR_GPU)/%.cpp,$(ODIR)/%.o,$(_OBJ_GPU)) $(ODIR)/main.o

CFLAGS = -std=c++17 -I$(IDIR) -I$(IDIR_GPU) -Ofast -fopenmp -lOpenCL
WFLAGS =  -Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual -Wmissing-include-dirs -Wunknown-pragmas -Wduplicated-cond -Wfloat-equal -Wshadow -Wunsafe-loop-optimizations -Wpacked -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wmissing-noreturn -Wsuggest-attribute=malloc -Wsuggest-attribute=format -Wmissing-format-attribute -Wsuggest-attribute=cold

EXE=Generate.exe



$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(WFLAGS)

$(ODIR)/%.o: $(SOURCE_DIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(WFLAGS)

$(ODIR)/%.o: $(SOURCE_DIR_GPU)/%.cpp $(DEPS)
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
	./delete_meshes.sh

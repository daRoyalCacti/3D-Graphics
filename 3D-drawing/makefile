CC = g++

##header files
	##directories which contain headers
IDIR_VK = deps_vk
IDIR_GEN = deps_general
	##grabbing all header files in the directories above
DEPS = $(wildcard $(IDIR_VK)/*.h) $(wildcard $(IDIR_GEN)/*.h)

##cpp files
	##.o output locations
ODIR = compiler_objects
	##directories which contain cpp files
SOURCE_DIR_VK = src_vk
SOURCE_DIR_GEN = src_general
	##grabbing all cpp files in the directories above
_OBJ = $(wildcard $(SOURCE_DIR_VK)/*.cpp)
_OBJ2 = $(wildcard $(SOURCE_DIR_GEN)/*.cpp)
	##turning the cpp files to obj files
OBJ_DEBUG = $(patsubst $(SOURCE_DIR_VK)/%.cpp,$(ODIR)/DEBUG/%.o,$(_OBJ)) $(patsubst $(SOURCE_DIR_GEN)/%.cpp,$(ODIR)/DEBUG/%.o,$(_OBJ2)) $(ODIR)/DEBUG/main.o
OBJ_RELEASE = $(patsubst $(SOURCE_DIR_VK)/%.cpp,$(ODIR)/RELEASE/%.o,$(_OBJ)) $(patsubst $(SOURCE_DIR_GEN)/%.cpp,$(ODIR)/RELEASE/%.o,$(_OBJ2)) $(ODIR)/RELEASE/main.o

##libraries that are not at /usr/include/
VULKAN_SDK_PATH = /home/george/Documents/Projects/Libraries/Vulkan-1.1.130.0/x86_64

##flags
	##vulkan compile flags
VKFLAGS = -lvulkan
	##warning flags
WFLAGS =  -Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual -Wmissing-include-dirs -Wunknown-pragmas -Wduplicated-cond -Wfloat-equal -Wshadow -Wunsafe-loop-optimizations -Wpacked -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wmissing-noreturn -Wsuggest-attribute=malloc -Wsuggest-attribute=format -Wmissing-format-attribute -Wsuggest-attribute=cold
	##rejected warning flags that might be used in the future
##-Winline
##-Wcast-qual
##-Wpointer-arith
##-Wsign-conversion
##-Wold-style-cast
	##compile flags
CFLAGS = -std=c++17 -I$(VULKAN_SDK_PATH)/include -I$(IDIR_VK) -I$(IDIR_GEN) -fopenmp -pthread -MMD $(WFLAGS)
	##linking flags
LDFLAGS = -L$(VULKAN_SDK_PATH)/lib `pkg-config --static --libs glfw3` $(VKFLAGS)

	##debug mode compiler flags
DEBUG_OPTIONS =
##-g
	##release mode compiler flags
RELEASE_OPTIONS = -Ofast -D NODEBUG -fkeep-inline-functions -fkeep-static-functions -fmerge-all-constants -fmodulo-sched

##build targets
EXE_DEBUG = BUILD_DEBUG.exe
EXE_RELEASE = BUILD_RELEASE.exe


##debug compiling
	##creating .o's
		##same dir as makefile -- main.cpp
$(ODIR)/DEBUG/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUG_OPTIONS)

		##rest of stated directories
$(ODIR)/DEBUG/%.o: $(SOURCE_DIR_VK)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUG_OPTIONS)

$(ODIR)/DEBUG/%.o: $(SOURCE_DIR_GEN)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUG_OPTIONS)

	##linking
$(EXE_DEBUG): $(OBJ_DEBUG)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)


##release compiling
##creating .o's
##same dir as makefile -- main.cpp
$(ODIR)/RELEASE/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(RELEASE_OPTIONS)

		##rest of stated directories
$(ODIR)/RELEASE/%.o: $(SOURCE_DIR_VK)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(RELEASE_OPTIONS)

$(ODIR)/RELEASE/%.o: $(SOURCE_DIR_GEN)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(RELEASE_OPTIONS)

	##linking
$(EXE_RELEASE): $(OBJ_RELEASE)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)


.PHONY: test clean

debug: $(EXE_DEBUG)
	@echo "DONE"

release: $(EXE_RELEASE)
	@echo "DONE"

all: $(EXE_RELEASE)	$(EXE_DEBUG)
	@echo "DONE"

test_debug: $(EXE_DEBUG)
	@echo "COMPILING COMPLETE"
	LD_LIBRARY_PATH=$(VULKAN_SDK_PATH)/lib VK_LAYER_PATH=$(VULKAN_SDK_PATH)/etc/vulkan/explicit_layer.d ./$(EXE_DEBUG)

test_release: $(EXE_RELEASE)
	./$(EXE_RELEASE)

clean_debug:
	rm -f $(ODIR)/DEBUG/*.o *~ $(INCDIR)/*~
	rm -f $(ODIR)/DEBUG/*.d *~ $(INCDIR)/*~

clean_release:
	rm -f $(ODIR)/RELEASE/*.o *~ $(INCDIR)/*~
	rm -f $(ODIR)/RELEASE/*.d *~ $(INCDIR)/*~

clean:
	rm -f $(ODIR)/DEBUG/*.o *~ $(INCDIR)/*~ $(ODIR)/DEBUG/*.o *~
	rm -f $(ODIR)/RELEASE/*.o *~ $(INCDIR)/*~ $(ODIR)/DEBUG/*.o *~
	rm -f $(ODIR)/DEBUG/*.d *~ $(INCDIR)/*~ $(ODIR)/DEBUG/*.d *~
	rm -f $(ODIR)/RELEASE/*.d *~ $(INCDIR)/*~ $(ODIR)/DEBUG/*.d *~

##as if the program had never been compiled
wipe:
	rm -f $(ODIR)/DEBUG/*.o *~ $(INCDIR)/*~ $(EXE_DEBUG)
	rm -f $(ODIR)/RELEASE/*.o *~ $(INCDIR)/*~ $(EXE_RELEASE)
	rm -f $(ODIR)/DEBUG/*.d *~ $(INCDIR)/*~ $(ODIR)/DEBUG/*.d *~
	rm -f $(ODIR)/RELEASE/*.d *~ $(INCDIR)/*~ $(ODIR)/DEBUG/*.d *~
	./delete_screenshots.sh

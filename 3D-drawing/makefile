CC = g++

IDIR = deps_vk
IDIR2 = deps_general
_DEPS = $(wildcard $(IDIR)/*.h)
_DEPS2 = $(wildcard $(IDIR2)/*.h)
##DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS)) $(patsubst %,$(IDIR2)/%,$(_DEPS2))
DEPS = $(patsubst %,%,$(_DEPS)) $(patsubst %,%,$(_DEPS2))

##_DEPS = data.h global.h Pixels.h player_camera.h window_inputs.h
##_DEPS2 = Buffer.h callbacks.h decriptorSetLayout.h graphicsPipeline.h moving_simple_mesh.h staging_buffer.h static_simple_mesh.h Texture.h ubos.h vertex.h vulkan_help.h vulkan_instance.h

ODIR = compiler_objects
SOURCE_DIR = src_vk
SOURCE_DIR2 = src_general
_OBJ = $(wildcard $(SOURCE_DIR)/*.cpp)
_OBJ2 = $(wildcard $(SOURCE_DIR2)/*.cpp)
OBJ_DEBUG = $(patsubst $(SOURCE_DIR)/%.cpp,$(ODIR)/DEBUG/%.o,$(_OBJ)) $(patsubst $(SOURCE_DIR2)/%.cpp,$(ODIR)/DEBUG/%.o,$(_OBJ2)) $(ODIR)/DEBUG/main.o
OBJ_RELEASE = $(patsubst $(SOURCE_DIR)/%.cpp,$(ODIR)/RELEASE/%.o,$(_OBJ))


VULKAN_SDK_PATH = /home/george/Documents/Projects/Libraries/Vulkan-1.1.130.0/x86_64
STB_INCLUDE_PATH  = /home/george/Documents/Projects/Libraries/stb-master
GLFW_INCLUDE_PATH = /usr/include/GLFW/
GLM_PATH = /usr/include/glm/


DEBUG_OPTIONS = -g
RELEASE_OPTIONS = -Ofast -D NODEBUG

VKFLAGS = -lvulkan
##GLFLAGS = -lGL
CFLAGS = -std=c++17 -I$(VULKAN_SDK_PATH)/include -I$(STB_INCLUDE_PATH) -I$(IDIR) -I$(IDIR2) -I$(GLFW_INCLUDE_PATH) -I$(GLM_PATH) -fopenmp -pthread -MMD
LDFLAGS = -L$(VULKAN_SDK_PATH)/lib `pkg-config --static --libs glfw3` $(VKFLAGS) ##$(GLFLAGS)
WFLAGS =  -Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual

EXE_DEBUG = BUILD_DEBUG
EXE_RELEASE = BUILD_RELEASE


##debug compiling
$(ODIR)/DEBUG/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUG_OPTIONS) $(WFLAGS)

$(ODIR)/DEBUG/%.o: $(SOURCE_DIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUG_OPTIONS) $(WFLAGS)

$(ODIR)/DEBUG/%.o: $(SOURCE_DIR2)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUG_OPTIONS) $(WFLAGS)

$(EXE_DEBUG): $(OBJ_DEBUG)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(WFLAGS)


##release compiling
$(ODIR)/RELEASE/%.o: $(SOURCE_DIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(RELEASE_OPTIONS) $(WFLAGS)

$(EXE_RELEASE): $(OBJ_RELEASE)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(WFLAGS)

##-include $(_OBJ:.o=.d)


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
	LD_LIBRARY_PATH=$(VULKAN_SDK_PATH)/lib VK_LAYER_PATH=$(VULKAN_SDK_PATH)/etc/vulkan/explicit_layer.d ./$(EXE_RELEASE)

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

wipe:
	rm -f $(ODIR)/DEBUG/*.o *~ $(INCDIR)/*~ $(EXE_DEBUG)
	rm -f $(ODIR)/RELEASE/*.o *~ $(INCDIR)/*~ $(EXE_RELEASE)
	rm -f $(ODIR)/DEBUG/*.d *~ $(INCDIR)/*~ $(ODIR)/DEBUG/*.d *~
	rm -f $(ODIR)/RELEASE/*.d *~ $(INCDIR)/*~ $(ODIR)/DEBUG/*.d *~

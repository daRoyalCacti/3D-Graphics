CC = g++

IDIR = dependencies
_DEPS = global.h data.h vulkan_help.h vulkan_instance.h static_simple_mesh.h vertex.h ubos.h staging_buffer.h window_inputs.h player_camera.h Buffer.h decriptorSetLayout.h graphicsPipeline.h Pixels.h Texture.h moving_simple_mesh.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

ODIR = compiler_objects
_OBJ = vulkan_help.o data.o vulkan_instance.o main.o static_simple_mesh.o ubos.o staging_buffer.o window_inputs.o
OBJ_DEBUG = $(patsubst %,$(ODIR)/DEBUG/%,$(_OBJ))
OBJ_RELEASE = $(patsubst %,$(ODIR)/RELEASE/%,$(_OBJ))

VULKAN_SDK_PATH = /home/george/Documents/Projects/Libraries/Vulkan-1.1.130.0/x86_64
STB_INCLUDE_PATH  = /home/george/Documents/Projects/Libraries/stb-master
GLFW_INCLUDE_PATH = /usr/include/GLFW/
GLM_PATH = /usr/include/glm/
TINYOBJ_INCLUDE_PATH = /home/george/Documents/Projects/Libraries

DEBUG_OPTIONS = -g
RELEASE_OPTIONS = -Ofast -D NODEBUG

CFLAGS = -std=c++17 -I$(VULKAN_SDK_PATH)/include -I$(STB_INCLUDE_PATH) -I$(IDIR) -I$(GLFW_INCLUDE_PATH) -I$(GLM_PATH) -I$(TINYOBJ_INCLUDE_PATH) -fopenmp -pthread
LDFLAGS = -L$(VULKAN_SDK_PATH)/lib `pkg-config --static --libs glfw3` -lvulkan
WFLAGS =  -Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual

EXE_DEBUG=VulkanTest_DEBUG
EXE_RELEASE=VulkanTest_RELEASE


$(ODIR)/DEBUG/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUG_OPTIONS) $(WFLAGS)

$(EXE_DEBUG): $(OBJ_DEBUG)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(WFLAGS)

$(ODIR)/RELEASE/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(RELEASE_OPTIONS) $(WFLAGS)

$(EXE_RELEASE): $(OBJ_RELEASE)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(WFLAGS)

.PHONY: test clean

debug: $(EXE_DEBUG)
	@echo "DONE"

release: $(EXE_RELEASE)
	@echo "DONE"

all: $(EXE_RELEASE) $(EXE_DEBUG)
	@echo "DONE"

test_debug: $(EXE_DEBUG)
	@echo "COMPILING COMPLETE"
	LD_LIBRARY_PATH=$(VULKAN_SDK_PATH)/lib VK_LAYER_PATH=$(VULKAN_SDK_PATH)/etc/vulkan/explicit_layer.d ./$(EXE_DEBUG)

test_release: $(EXE_RELEASE)
	LD_LIBRARY_PATH=$(VULKAN_SDK_PATH)/lib VK_LAYER_PATH=$(VULKAN_SDK_PATH)/etc/vulkan/explicit_layer.d ./$(EXE_RELEASE)

debuging:
	LD_LIBRARY_PATH=$(VULKAN_SDK_PATH)/lib VK_LAYER_PATH=$(VULKAN_SDK_PATH)/etc/vulkan/explicit_layer.d gdb $(EXE_DEBUG)

clean_debug:
	rm -f $(ODIR)/DEBUG/*.o *~ $(INCDIR)/*~

clean_release:
	rm -f $(ODIR)/RELEASE/*.o *~ $(INCDIR)/*~

clean:
	rm -f $(ODIR)/RELEASE/*.o *~ $(INCDIR)/*~ $(ODIR)/DEBUG/*.o *~

wipe:
	rm -f $(ODIR)/DEBUG/*.o *~ $(INCDIR)/*~ $(EXE_DEBUG)

testexe: $(EXE_DEBUG)
	./$(EXE_DEBUG)

run:
	LD_LIBRARY_PATH=$(VULKAN_SDK_PATH)/lib VK_LAYER_PATH=$(VULKAN_SDK_PATH)/etc/vulkan/explicit_layer.d ./$(EXE_DEBUG)

runexe:
	./$(EXE_DEBUG)

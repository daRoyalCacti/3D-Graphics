#pragma once
#include "Pixels.h"
#include "static_simple_mesh.h"
#include "moving_simple_mesh.h"
#include "ubos.h"

#include <glm/glm.hpp>

const int no_images = 3; //2 squares and skybox
const int no_meshes = no_images; //each mesh has its own unique texture
const int no_camera_positions = 4;
namespace vk_files {
	//functions that return values needed to create arrays
	int read_Simple_Static_mesh();
	int read_texture();
	void read_ubo();
	int read_Simple_Moving_mesh();

	//main functions
	void Texture_to_Pixels(pixels*);
	void Vertices_to_Simple_Static_Mesh(staticSimpleMesh*);
	void Vertices_to_Simple_Moving_Mesh(moving_simple_mesh*);
	void Rotations_to_UBOs(ubo_model*);
	#ifdef precalculated_player_camera
		void Load_Camera_Positions(glm::vec3*, float*, float*);
	#endif
}

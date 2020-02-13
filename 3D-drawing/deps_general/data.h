#pragma once
#include "Pixels.h"
#include "static_simple_mesh.h"
#include "moving_simple_mesh.h"
#include "ubos.h"

#include <glm/glm.hpp>

const int no_images = 3; //2 squares and skybox
const int no_meshes = no_images; //each mesh has its own unique texture
const int no_camera_positions = 4;
namespace files {
	//functions that do all of the file reading
	// - they return values needed to create arrays and such for the vulkan objects the data needs to be put into
	uint32_t read_Simple_Static_mesh();
	uint32_t read_texture();
	void read_ubo();
	uint32_t read_Simple_Moving_mesh();

 	//functions to take the data in c data types and move it to the defined vulkan objects
	//this would make sense in another file but it was easier here because then no data needs to be passed
	namespace vk {
		void Texture_to_Pixels(pixels*);
		void Vertices_to_Simple_Static_Mesh(staticSimpleMesh*);
 		void Vertices_to_Simple_Moving_Mesh(moving_simple_mesh*);
 		void Rotations_to_UBOs(ubo_model*);
		#ifdef precalculated_player_camera
			void Camera_to_Vectors(glm::vec3*, float*, float*);
		#endif
	}

	#ifdef precalculated_player_camera
		uint32_t read_camera();
		void Camera_to_Vectors(glm::vec3*, float*, float*);
	#endif
}

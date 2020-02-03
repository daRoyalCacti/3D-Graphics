#include "data.h"
#include "global.h"

#include <chrono>
#include "global.h"

#include <string>
#include <cstring>
#include <fstream>
#include <iostream>

#include <mutex>

#include <glm/gtc/matrix_transform.hpp>

namespace files {
  const std::string file_extension = ".bin";

  uint32_t no_mesh; //number of static meshes
  uint32_t no_image; //number of textures
  uint32_t no_m_mesh; //number of moving meshes
  uint32_t no_ubo_mesh; //number of movements
  uint32_t* no_frames; //number of frames for each ubo
  uint32_t* frames_for_mesh; //number of frames for each moving mesh

  std::mutex mtx;

  std::vector<std::vector<Vertex>> Vertices; //static vertices
  std::vector<std::vector<uint32_t>> Indicies; //moving vertices

  std::vector<std::vector<std::vector<Vertex>>> m_Vertices; //array of vertices gives a mesh, array of meshes for every frame of animation, array of frames for each object
  std::vector<std::vector<uint32_t>> m_Indicies; //index array does not change between frames

  std::vector<std::vector<uint8_t>> images;
  std::vector<size_t> image_dimensions;
  std::vector<uint32_t> image_ids;


  std::vector<std::vector<glm::mat4>> rotations; //each mesh needs a rotation and each mesh has multiple frames of rotation

  #ifdef precalculated_player_camera //NOT COMPLETE ==================================================================
  	void Load_Camera_Positions(glm::vec3* camera_positions, float* camera_yaws, float* camera_pitchs) {
      glm::vec3 _camera_positions[no_camera_positions] = { {0,0,0} };
      float _camera_yaws[no_camera_positions] = { 230, 230, 230, 230 };
      float _camera_pitchs[no_camera_positions] = { -10, -10, -10, -10 };

      memcpy(camera_positions, _camera_positions, sizeof(_camera_positions)); //this most likely wont be needed when data is being read from file
      memcpy(camera_yaws, _camera_yaws, sizeof(_camera_yaws));
      memcpy(camera_pitchs, _camera_pitchs, sizeof(_camera_pitchs));
    } //end function
  #endif


  uint32_t read_Simple_Static_mesh() {
    //this functions reads the static meshes from files using a very set naming convention
    //all details about the files can be found is the program that is used to write them

    #ifdef detailed_timing
      auto start = std::chrono::steady_clock::now();
    #endif

  	unsigned data_first; //data required for sizing arrays and such
  	std::ifstream data_file_first("./Meshes/data" + file_extension, std::ios::binary); data_file_first.read((char*)&data_first, sizeof(unsigned) ); data_file_first.close(); //reading said data

    no_mesh = data_first;
  	unsigned no_data = data_first * 2 + 1; //number of verticies and indicies plus the first line

  	unsigned* reading_data = new unsigned[no_data]; //variable to be pointed to that contains no vertices and indices for all meshes
  	std::ifstream data_file("./Meshes/data" + file_extension, std::ios::binary); data_file.read((char*)&reading_data[0], no_data * sizeof(unsigned) ); data_file.close();

  	Vertices.resize(no_mesh);
  	Indicies.resize(no_mesh);

    unsigned *data_ptr = &reading_data[1]; //the pointer described above

    int no_mesh_vertices, no_mesh_indices; //variables used to create appropriately sized arrays and required to read the data from the binary files effectively

    float* reading_vertices, *reading_uvs; //variables for the data from the files to read direcly into -- will be converted to a more useful form later
  	for (int k = 0; k < static_cast<int>(no_mesh); k++) {
  		//variables describing the data
  		no_mesh_vertices = *data_ptr++;
  		no_mesh_indices = *data_ptr++;
  		//varibles for the data
  		reading_vertices = new float[no_mesh_vertices * 3];
  		reading_uvs = new float[no_mesh_vertices * 2];
      Indicies[k].resize(no_mesh_indices); //no reading variable required because the data is already in the correct form

  		//reading vertices
  		std::ifstream vertices_file(static_cast<std::string>("./Meshes/vertices_simple_static_") + std::to_string(k) + file_extension, std::ios::binary);
  		if (!vertices_file.is_open()) {throw std::runtime_error(static_cast<std::string>("failed to open vertex file ") + std::to_string(k) + file_extension);} //error checking
  		vertices_file.read((char*)&reading_vertices[0], no_mesh_vertices * 3 * sizeof(float)); vertices_file.close();

  		//reading texture coordinates
  		std::ifstream uvs_file(static_cast<std::string>("./Meshes/uvs_simple_static_") + std::to_string(k) + file_extension, std::ios::binary);
  		if (!uvs_file.is_open()) {throw std::runtime_error(static_cast<std::string>("failed to open uv file ") + std::to_string(k) + file_extension);} //error checking
  		uvs_file.read((char*)&reading_uvs[0], no_mesh_vertices * 2 * sizeof(float) ); uvs_file.close();

  		//reading indices
  		std::ifstream indices_file(static_cast<std::string>("./Meshes/indices_simple_static_") + std::to_string(k) + file_extension, std::ios::binary);
  		if (!indices_file.is_open()) {throw std::runtime_error(static_cast<std::string>("failed to open index file ") + std::to_string(k) + file_extension);} //error checking
  		indices_file.read((char*)&Indicies[k][0], sizeof(Indicies[k][0]) * Indicies[k].size() ); indices_file.close();

      Vertices[k].resize(no_mesh_vertices *  5); //need to set number of vertices for the given mesh

    //parallelizing the loop may be unnecessary
    #pragma omp parallel for
  		for (int i = 0; i < no_mesh_vertices; i++) {
        int counter_verticies = i * 3; //required for parallizing the loop
        int counter_uvs = i * 2;

        //glm does funny things if it is not specified this way
        Vertices[k][i].pos.x = reading_vertices[counter_verticies];
        Vertices[k][i].pos.y = reading_vertices[counter_verticies + 1]; //shouldn't use ++ because loop is parallized and make it atomic wouldn't make much sense
        Vertices[k][i].pos.z = reading_vertices[counter_verticies + 2];

        Vertices[k][i].texCoord.x = reading_uvs[counter_uvs];
        Vertices[k][i].texCoord.y = reading_uvs[counter_uvs + 1];
  		}


      delete [] reading_vertices;
      delete [] reading_uvs;

  	}

    delete [] reading_data;

    #ifdef detailed_timing
    	auto end = std::chrono::steady_clock::now();
      mtx.lock();
    	std::cout << "\t Mesh reading took \t\t\t" << std::chrono::duration <double, std::milli>(end - start).count() << "ms" << std::endl;
      mtx.unlock();
    #endif

    return no_mesh;
  }


  namespace vk {
    void Vertices_to_Simple_Static_Mesh(staticSimpleMesh* Squares) { //could be moved to read_Simple_Static_mesh? -- is simple enough
      #ifdef detailed_timing
        auto start = std::chrono::steady_clock::now();
      #endif
      //no need to parallize because is already stupid fast
      for (int i = 0; i < static_cast<int>(no_mesh); i++) {
        Squares[i].vertices = Vertices[i];
        Squares[i].indices = Indicies[i];
      }

      #ifdef detailed_timing
      	auto end = std::chrono::steady_clock::now();
        mtx.lock();
      	std::cout << "\t Vertex array filling took \t\t" << std::chrono::duration <double, std::milli>(end - start).count() << "ms" << std::endl;
        mtx.unlock();
      #endif

    }
  }



  uint32_t read_Simple_Moving_mesh() {
    #ifdef detailed_timing
    	auto start = std::chrono::steady_clock::now();
    #endif

    unsigned test_reading_data_first; //for reading in the amount of meshes to set the required array size
    std::ifstream data_file_first("./Meshes/m_data" + file_extension, std::ios::binary); data_file_first.read((char*)&test_reading_data_first, sizeof(unsigned) ); data_file_first.close();

    no_m_mesh = test_reading_data_first;
    unsigned *alldata = new unsigned[no_m_mesh * 3 + 1]; //number of vertices, indicies and frames + first value

    m_Indicies.resize(no_m_mesh); //resize of the number of meshes
    m_Vertices.resize(no_m_mesh);

    //reading data
    std::ifstream data_file("./Meshes/m_data" + file_extension, std::ios::binary); data_file.read((char*)&alldata[0], (no_m_mesh * 3 + 1) * sizeof(unsigned) ); data_file.close();
    const unsigned* testptr = &alldata[1]; //first value has already been used

    unsigned *no_mesh_vertices = new unsigned[no_m_mesh]; //necessary for sizing arrays, reading from binary files
    unsigned *no_mesh_indices = new unsigned[no_m_mesh];
    frames_for_mesh = new unsigned[no_m_mesh];


    for (unsigned i = 0; i < no_m_mesh; i++) {
      no_mesh_vertices[i] = *testptr++;
      no_mesh_indices[i] = *testptr++;
      frames_for_mesh[i] = *testptr++;

      m_Vertices[i].resize(frames_for_mesh[i]); //the second dimension to the array is for the number of frames of animation a mesh has
      m_Indicies[i].resize(no_mesh_indices[i]);

      //reading indices
  		std::ifstream indices_file(static_cast<std::string>("./Meshes/indices_simple_moving_") + std::to_string(i) + file_extension, std::ios::binary);
  		if (!indices_file.is_open()) {throw std::runtime_error(static_cast<std::string>("failed to open index file ") + std::to_string(i) + file_extension);}
  		indices_file.read((char*)&m_Indicies[i][0], sizeof(m_Indicies[i][0]) * m_Indicies[i].size() ); indices_file.close();


      float* reading_vertices = new float[no_mesh_vertices[i] * 3]; //required to read in data from file -- is then converted to move useful form
      float* reading_uvs = new float[no_mesh_vertices[i] * 2];

      for (unsigned j = 0; j < frames_for_mesh[i]; j++) {
        //reading vertices -- the vertices change every frame so they have to read for every frame of animation
        std::ifstream vertices_file(static_cast<std::string>("./Meshes/vertices_simple_moving_") + std::to_string(i) + "_" + std::to_string(j) + file_extension, std::ios::binary);
        if (!vertices_file.is_open()) {throw std::runtime_error(static_cast<std::string>("failed to open vertex file ") + std::to_string(i) + " for frame " + std::to_string(j) + file_extension);}
        vertices_file.read((char*)&reading_vertices[0], no_mesh_vertices[i] * 3 * sizeof(float)); vertices_file.close();


        //reading texture coordinates
        std::ifstream uvs_file(static_cast<std::string>("./Meshes/uvs_simple_moving_") + std::to_string(i) + "_" + std::to_string(j) + file_extension, std::ios::binary);
        if (!uvs_file.is_open()) {throw std::runtime_error(static_cast<std::string>("failed to open uv file ") + std::to_string(i) + " for frame " + std::to_string(j) + file_extension);}
        uvs_file.read((char*)&reading_uvs[0], no_mesh_vertices[i] * 2 * sizeof(float) ); uvs_file.close();

        m_Vertices[i][j].resize(no_mesh_vertices[i]);

      #pragma omp parallel for
        for (unsigned k = 0; k < no_mesh_vertices[i]; k++) {
          int counter_uvs = k * 2; //required to make loop run in parallel
          int counter_verticies = k * 3;

          //glm does funny things if not specified this way
          m_Vertices[i][j][k].pos.x = reading_vertices[counter_verticies];
          m_Vertices[i][j][k].pos.y = reading_vertices[counter_verticies + 1];
          m_Vertices[i][j][k].pos.z = reading_vertices[counter_verticies + 2];

          m_Vertices[i][j][k].texCoord.x = reading_uvs[counter_uvs];
          m_Vertices[i][j][k].texCoord.y = reading_uvs[counter_uvs + 1];
        }

      }
      delete [] reading_vertices;
      delete [] reading_uvs;
    }

    delete [] no_mesh_vertices;
    delete [] no_mesh_indices;
    delete [] alldata;

    #ifdef detailed_timing
    	auto end = std::chrono::steady_clock::now();
      mtx.lock();
    	std::cout << "\t Moving mesh reading took \t\t" << std::chrono::duration <double, std::milli>(end - start).count() << "ms" << std::endl;
      mtx.unlock();
    #endif

    return no_m_mesh;
  }


  namespace vk {
    void Vertices_to_Simple_Moving_Mesh(moving_simple_mesh* Squares) {
      #ifdef detailed_timing
      	auto start = std::chrono::steady_clock::now();
      #endif

      for (int i = 0; i < static_cast<int>(no_m_mesh); i++) { //for all moving meshes
        Squares[i].Mesh.indices = m_Indicies[i];
        Squares[i].frames = frames_for_mesh[i];
        Squares[i].Meshes.resize(static_cast<int>(Squares[i].frames));
        for (int j = 0; j < static_cast<int>(Squares[i].frames); j++) { //for every frame of animation
          Squares[i].Meshes[j] = m_Vertices[i][j];
        }
      }

      delete [] frames_for_mesh;
      //std::vector<std::vector<uint32_t>>().swap(m_Indicies);

      #ifdef detailed_timing
      	auto end = std::chrono::steady_clock::now();
        mtx.lock();
      	std::cout << "\t Moving vertex array filling took \t" << std::chrono::duration <double, std::milli>(end - start).count() << "ms" << std::endl;
        mtx.unlock();
      #endif
    }
  }



  uint32_t read_texture() {
    #ifdef detailed_timing
      auto start = std::chrono::steady_clock::now();
    #endif


    //data reading
    uint32_t initial_reading[2];
    std::ifstream data_file_first("./textures/data" + file_extension, std::ios::binary); data_file_first.read((char*)&initial_reading[0], sizeof(initial_reading) ); data_file_first.close();
    no_image = initial_reading[0];
    uint8_t mode = initial_reading[1];
    enum image_modes {EMPTY, PNG, BIN};

    if (mode == EMPTY) {
      throw std::runtime_error("Image mode EMPTY is not allowed");
    } else if (mode == PNG) {
      throw std::runtime_error("Png image reading is currently not supported");
    }

    images.resize(no_image);
    image_dimensions.resize(no_image * 2);

    uint32_t* alldata = new uint32_t[no_image * 2 + 2];  //sizes consist of width and height, 2 for intial reading
    std::ifstream data_file("./textures/data" + file_extension, std::ios::binary); data_file.read((char*)&alldata[0], (no_image * 2 + 2) * sizeof(uint32_t) ); data_file.close();

    uint32_t* data_ptr = &alldata[2];

    unsigned counter = 0;
    for (unsigned i = 0; i < no_image; i++) {
      unsigned imageWidth = *data_ptr++;
      unsigned imageHeight = *data_ptr++;
      images[i].resize(imageWidth * imageHeight * 4);
      image_dimensions[counter++] = imageWidth;
      image_dimensions[counter++] = imageHeight;

      std::ifstream image_file("./textures/texture_" + std::to_string(i) + file_extension, std::ios::binary); image_file.read((char*)&images[i][0], sizeof(images[i][0]) * images[i].size() ); image_file.close();
    }

    uint32_t first_data;
    std::ifstream t_data_file_first("./Meshes/t_data" + file_extension, std::ios::binary); t_data_file_first.read((char*)&first_data, sizeof(uint32_t) ); t_data_file_first.close();

    image_ids.resize(first_data + 1);
    std::ifstream t_data_file("./Meshes/t_data" + file_extension, std::ios::binary); t_data_file.read((char*)&image_ids[0], (first_data + 1) * sizeof(uint32_t) ); t_data_file.close();
    image_ids.erase(image_ids.begin()); //it needs all the data without the first element. So just removing the first element

    delete [] alldata;


    #ifdef detailed_timing
    	auto end = std::chrono::steady_clock::now();
      mtx.lock();
    	std::cout << "\t Texture data reading took \t\t" << std::chrono::duration <double, std::milli>(end - start).count() << "ms" << std::endl;
      mtx.unlock();
    #endif

    return no_image;
  }


  namespace vk {
    void Texture_to_Pixels(pixels* imagePixels) {
      #ifdef detailed_timing
        auto start = std::chrono::steady_clock::now();
      #endif


        for (int i = 0; i < static_cast<int>(no_image); i++) {
          imagePixels[i].pixels = new uint8_t[images[image_ids[i]].size()];
          std::copy(images[image_ids[i]].begin(), images[image_ids[i]].end(), imagePixels[i].pixels);
          imagePixels[i].texWidth = image_dimensions[2 * image_ids[i]];
          imagePixels[i].texHeight = image_dimensions[2 * image_ids[i] + 1];
        }


        #ifdef detailed_timing
        	auto end = std::chrono::steady_clock::now();
          mtx.lock();
        	std::cout << "\t Texture reading took \t\t\t" << std::chrono::duration <double, std::milli>(end - start).count() << "ms" << std::endl;
          mtx.unlock();
        #endif
    }
  }


  void read_ubo() {
    #ifdef detailed_timing
      auto start = std::chrono::steady_clock::now();
    #endif

    const int rotation_elements = 4, translation_elements = 3;

    unsigned test_reading_data_first;
    std::ifstream data_file_first("./Meshes/ubo_data" + file_extension, std::ios::binary); data_file_first.read((char*)&test_reading_data_first, sizeof(unsigned) ); data_file_first.close();

    unsigned *alldata = new unsigned[test_reading_data_first * 3 + 1];

    no_ubo_mesh = test_reading_data_first;
    //if (no_ubo_mesh != (no_mesh + no_m_mesh)) throw std::runtime_error("number of ubo model matrices does not equal the number of meshes");
    rotations.resize(no_ubo_mesh);

    std::ifstream data_file("./Meshes/ubo_data" + file_extension, std::ios::binary); data_file.read((char*)&alldata[0], (test_reading_data_first * 3 + 1) * sizeof(unsigned) ); data_file.close();
    unsigned* testptr = &alldata[1];

    no_frames = new unsigned[no_ubo_mesh];


    std::vector<float> reading_rotations;
    std::vector<float> reading_translation;

    float *rotations_ptr, *translations_ptr;

    for (size_t i = 0; i < static_cast<size_t>(no_ubo_mesh); i++) { //for each mesh
      no_frames[i] = *testptr++;
      rotations[i].resize(no_frames[i]);

      reading_rotations.resize(rotation_elements);
      reading_translation.resize(translation_elements);

      float rotation_angle;
      glm::vec3 rotation_vector, translation_vector;

      for (size_t j = 0; j < static_cast<size_t>(no_frames[i]); j++) { //for every frame of movement for a given mesh
        //reading the rotations for every frame
        std::ifstream rotations_file(static_cast<std::string>("./Meshes/rotations_") + std::to_string(i) + "_" + std::to_string(j) + file_extension, std::ios::binary);
        if (!rotations_file.is_open()) {throw std::runtime_error(static_cast<std::string>("failed to open rotations file ") + std::to_string(i) + file_extension);}
        rotations_file.read((char*)&reading_rotations[0], no_frames[i] * rotation_elements * sizeof(float)); rotations_file.close();


        //reading the translations for every frame
        std::ifstream translations_file(static_cast<std::string>("./Meshes/translations_") + std::to_string(i) + "_" + std::to_string(j) + file_extension, std::ios::binary);
        if (!translations_file.is_open()) {throw std::runtime_error(static_cast<std::string>("failed to open translations file ") + std::to_string(i) + file_extension);}
        translations_file.read((char*)&reading_translation[0], no_frames[i] * translation_elements * sizeof(float) ); translations_file.close();

        rotations_ptr = &reading_rotations[0];
        translations_ptr = &reading_translation[0];

        //glm doesnt behave nicely if the values are not set in this way
        rotation_angle = *rotations_ptr++;
        rotation_vector.x = *rotations_ptr++;
        rotation_vector.y = *rotations_ptr++;
        rotation_vector.z = *rotations_ptr++;

        translation_vector.x = *translations_ptr++;
        translation_vector.y = *translations_ptr++;
        translation_vector.z = *translations_ptr++;

        if (rotation_vector == glm::vec3(0.0f, 0.0f, 0.0f)) { //glm::rotate doesnt behave nicely if the rotation axis is the 0 vector
          rotations[i][j] = glm::translate(glm::mat4(1.0f), translation_vector);
        } else {
          rotations[i][j] = glm::translate(glm::rotate(glm::mat4(1.0f), rotation_angle, rotation_vector), translation_vector);
        } //end if

      } //end inner loop

    } //end outer loop

    delete [] alldata;
    //std::vector<std::vector<std::vector<Vertex>>>().swap(m_Vertices); //!!!must be here or else std::bad_alloc returnsis thrown -- NO IDEA WHY
    //std::vector<std::vector<Vertex>>().swap(Vertices);
    //std::vector<std::vector<uint32_t>>().swap(Indicies);

    #ifdef detailed_timing
      auto end = std::chrono::steady_clock::now();
      mtx.lock();
      std::cout << "\t UBO reading took \t\t\t" << std::chrono::duration <double, std::milli>(end - start).count() << "ms" << std::endl;
      mtx.unlock();
    #endif

  }


  namespace vk {
    void Rotations_to_UBOs(ubo_model* square_model) {
      #ifdef detailed_timing
        auto start = std::chrono::steady_clock::now();
      #endif

      for (unsigned i = 0; i < no_ubo_mesh; i++) { //for each mesh
        //std::cout << i << " " << no_mesh + no_m_mesh << std::endl;
        square_model[i].models.resize(no_frames[i]);
        square_model[i].total_frames = no_frames[i];

        for (unsigned j = 0; j < no_frames[i]; j++) {
          //if (i==4) rotations[i][j] = glm::mat4(1.0f);
          square_model[i].models[j] = rotations[i][j]; //for each frame of that mesh
        }
      } //end outer loop
      delete [] no_frames;
      //std::vector<std::vector<glm::mat4>>().swap(rotations);

      #ifdef detailed_timing
      	auto end = std::chrono::steady_clock::now();
        mtx.lock();
      	std::cout << "\t Rotation array filling took \t\t" << std::chrono::duration <double, std::milli>(end - start).count() << "ms" << std::endl;
        mtx.unlock();
      #endif
    }
  }


} //end namespace

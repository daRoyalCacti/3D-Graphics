#pragma once
#include <fstream>
#include <vector>
#include "global.h"
#include "helper.h"
#include <string>

const std::string file_extension = ".bin";
const std::string file_location = "/home/george/Documents/Projects/Major-3D/3D-drawing/Meshes/";

inline void fillData() {
  //helper function to fill the required array for the data required for reading the static meshes easily
  global::data.resize(global::all_vertices.size() * 2 + 1);
  global::data[0] = global::all_vertices.size();
  int counter = 0;
  for (size_t i = 0; i < static_cast<size_t>(global::all_vertices.size() * 2); i+=2, counter++) {
    global::data[i + 1] = global::all_vertices[counter].size() / 3; //number of vertices in mesh i
    global::data[i + 2] = global::all_indicies[counter].size(); //number of indicies in mesh i
  }
}

inline void fillm_Data() {
  //helper function to fill the required array for the data required for reading the moving meshes easily
  global::m_data.resize(global::all_m_vertices.size() * 3 + 1); //vertices, indices, and uvs + total number of meshes
  global::m_data[0] = global::all_m_vertices.size();
  int counter = 0;
  for (size_t i = 0; i < static_cast<size_t>(global::all_m_vertices.size() * 3); i+=3, counter++) {
    global::m_data[i + 1] = global::all_m_vertices[counter][0].size(); //number of vertices for mesh i
    global::m_data[i + 2] = global::all_m_indices[counter].size(); //number of indices for mesh i
    global::m_data[i + 3] = global::all_m_vertices[counter].size(); //number of frames for mesh i
  }
}

inline void fillubo_data() {
  global::ubo_data.resize(global::all_translations.size() + 1);
  global::ubo_data[0] = global::all_translations.size();

  for (size_t i = 0; i < static_cast<size_t>(global::all_translations.size()); i++) {
    global::ubo_data[i + 1] = global::all_translations[i].size();
  }
}

inline void fillt_data() {
  global::texture_data.resize(global::static_texture_ids.size() + global::moving_texture_ids.size() + 1);
  global::texture_data[0] = global::static_texture_ids.size() + global::moving_texture_ids.size();

  uint32_t static_size = global::static_texture_ids.size();

  for (uint32_t i = 0; i < static_size; i++) {
    global::texture_data[i + 1] = global::static_texture_ids[i];
  }

  uint32_t j;
  for (uint32_t i = static_size; i < static_size + global::moving_texture_ids.size(); i++) {
    j = i - static_size;
    global::texture_data[i + 1] = global::moving_texture_ids[j] + static_size;
  }
}


inline void write_all() {
  //---------------------------------------------------------------------------------------------------------------
  //writes meshes to files that are within the "all_vertices", "all_uvs", "all_indicies" vectors
  //also writes a data file which contains the necessary details for reading the data effectively
  //these arrays need to be filled prior to the call of this function or else the results will be undefined
  //---------------------------------------------------------------------------------------------------------------

  //static mesh error checking
  if (global::all_vertices.size() != global::all_uvs.size() || global::all_uvs.size() != global::all_indicies.size() || global::all_vertices.size() != global::all_indicies.size() ) {
    std::cerr << "Inequal number of vertices, indices and uvs for static meshes" << std::endl;
    std::cout << "Vertices: " << global::all_vertices.size() << "\tIndices: " << global::all_indicies.size() << "\tUvs: " << global::all_uvs.size() << std::endl;
  }

  //moving mesh error checking
  if (global::all_m_vertices.size() != global::all_m_uvs.size() || global::all_m_uvs.size() != global::all_m_indices.size() || global::all_m_vertices.size() != global::all_m_indices.size() ) {
    //if each mesh has a set of vertices, indices, and uvs
    std::cerr << "Inequal number of vertices, indices and uvs for moving meshes" << std::endl;
    std::cout << "Vertices: " << global::all_m_vertices.size() << "\tIndices: " << global::all_m_indices.size() << "\tUvs: " << global::all_m_uvs.size() << std::endl;
  }
  for (size_t i = 0; i < static_cast<size_t>(global::all_m_vertices.size()); i++) {
    if (global::all_m_vertices[i].size() != global::all_m_uvs[i].size()) { //no need to check indices because that is constant between frames
      //if each frame has vertices and uvs
      std::cerr << "Inequal number of vertices and uvs for moving meshes for frame " << i << std::endl;
      std::cout << "Vertices: " << global::all_m_vertices[i].size() << "\tUvs: " << global::all_m_uvs[i].size() << std::endl;
    }
  }

  //!!ubo error checking

  //these functions write the data necessary for reading the data back easily
  // - all the data writen is taken from global vectors to make the mesh creation process seperate from the writing process
  fillData();
  fillm_Data();
  fillubo_data();
  fillt_data();

  //-------------------------------------------------------------------------------------------------------------------------------------------------------
  //actually writing the data to file
  //there is a very specific naming convention that needs to be followed for the vulkan program to read the data -- this might be changed in the future
  // - for static meshes: <vertices, uvs, indices>_simple_static_<mesh id>
  // - for animated meshes: <vertices, uvs, indices>_simple_moving_<mesh id>_<frame>
  // - for movement : <translations, rotations>_<mesh id>_<frame>
  //all the data writen is taken from global vectors to make the mesh creation process seperate from the writing process
  //all data is written in binary files (for these programs binary files have no file extension) -- this might be changed in the future
  //-------------------------------------------------------------------------------------------------------------------------------------------------------

  //writing static meshes
  for (size_t k = 0; k < static_cast<size_t>(global::all_vertices.size()); k++){
    //for each mesh - write the components of the mesh to file
    std::ofstream output_vertices((file_location + "/vertices_simple_static_" + std::to_string(k) + file_extension).c_str(), std::ios::binary); output_vertices.write( (char *)&global::all_vertices[k][0], sizeof(float) * global::all_vertices[k].size() ); output_vertices.close();
    std::ofstream output_uvs((file_location + "uvs_simple_static_" + std::to_string(k) + file_extension).c_str(), std::ios::binary); output_uvs.write( (char *)&global::all_uvs[k][0], sizeof(float) * global::all_uvs[k].size() ); output_uvs.close();
    std::ofstream output_indices((file_location + "indices_simple_static_" + std::to_string(k) + file_extension).c_str(), std::ios::binary); output_indices.write( (char *)&global::all_indicies[k][0], sizeof(uint32_t) * global::all_indicies[k].size() ); output_indices.close();
  }

  //writing animated meshes
  for (size_t k = 0; k < static_cast<size_t>(global::all_m_vertices.size()); k++){
    //for each mesh write the components of the mesh to file
    //indices are in this loop because they do not change between frames
    std::ofstream output_m_indices((file_location + "indices_simple_moving_" + std::to_string(k) + file_extension).c_str(), std::ios::binary); output_m_indices.write( (char *)&global::all_m_indices[k][0], sizeof(uint32_t) * global::all_m_indices[k].size() ); output_m_indices.close();
    for (size_t i = 0; i < static_cast<size_t>(global::all_m_vertices[k].size()); i++) {
      //for each frame, write out the components of the mesh that change between frames
      std::ofstream output_m_vertices((file_location + "vertices_simple_moving_" + std::to_string(k) + "_" + std::to_string(i) + file_extension).c_str(), std::ios::binary); output_m_vertices.write( (char *)&global::all_m_vertices[k][i][0], sizeof(float) * global::all_m_vertices[k][i].size() ); output_m_vertices.close();
      std::ofstream output_m_uvs((file_location + "uvs_simple_moving_" + std::to_string(k) + "_" + std::to_string(i) + file_extension).c_str(), std::ios::binary); output_m_uvs.write( (char *)&global::all_m_uvs[k][i][0], sizeof(float) * global::all_m_uvs[k][i].size() ); output_m_uvs.close();
    }
  }

  //writing movement
  for (size_t k = 0; k < static_cast<size_t>(global::all_translations.size()); k++){
    //for each mesh
    for (size_t j = 0; j < static_cast<size_t>(global::all_translations[k].size()); j++) {
      //for each frame, write the necessary movement values
      std::ofstream output_rotations((file_location + "rotations_" + std::to_string(k) + "_" + std::to_string(j) + file_extension).c_str(), std::ios::binary); output_rotations.write( (char *)&global::all_rotations[k][j][0], sizeof(float) * 4 ); output_rotations.close();
      std::ofstream output_translations((file_location + "translations_" + std::to_string(k) + "_" + std::to_string(j) + file_extension).c_str(), std::ios::binary); output_translations.write( (char *)&global::all_translations[k][j][0], sizeof(float) * 3 ); output_translations.close();
    }
  }


  //writing the data required for reading the meshes easily to file
  //the files must be call "data" and "m_data" so the vulkan program can find the file -- might be changed in the future
  std::ofstream output_data((file_location + static_cast<std::string>("data") + file_extension).c_str(), std::ios::binary); output_data.write( (char *)&global::data[0], sizeof(global::data[0]) * global::data.size() ); output_data.close();
  std::ofstream output_m_data((file_location + static_cast<std::string>("m_data") + file_extension).c_str(), std::ios::binary); output_m_data.write( (char *)&global::m_data[0], sizeof(global::m_data[0]) * global::m_data.size() ); output_m_data.close();
  std::ofstream output_ubo_data(file_location + "ubo_data" + file_extension, std::ios::binary); output_ubo_data.write( (char *)&global::ubo_data[0], sizeof(global::ubo_data[0]) * global::ubo_data.size() ); output_ubo_data.close();
  //writing texture data
  std::ofstream output_textures(file_location + "t_data" + file_extension, std::ios::binary); output_textures.write((char*)&global::texture_data[0], sizeof(uint32_t) * global::texture_data.size()); output_textures.close();

}

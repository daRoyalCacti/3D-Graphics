#pragma once
#include <vector>
#include "global.h"
#include "vertex.h"
#include <iostream>

//shouldn't be inline -- need to fix
inline std::vector<Vertex> to_vertex(std::vector<float> v, std::vector<float> u) {
  if (v.size() / 3 != u.size() / 2) {
    std::cerr << "vectex and uv vector sizes are of non compatible sizes -- to_vertex(..)" << std::endl;
  }
  std::vector<Vertex> vertices;
  vertices.resize(v.size() / 3);
  unsigned j = 0, k = 0;
  for (unsigned i = 0; i < v.size()/3; i++, j+=3, k+=2) {
    vertices[i] = {{v[j], v[j + 1], v[j + 2]}, {u[k], u[k + 1]}};
  }

  return vertices;
}


inline uint32_t new_static_vertex(std::vector<float> vertices, std::vector<float> uvs) {
  global::all_vertex.push_back(to_vertex(vertices, uvs));
  return global::all_vertex.size() - 1;
}


inline uint32_t new_static_indices(std::vector<uint32_t> indices) {
  global::all_indicies.push_back(indices);
  return global::all_indicies.size() - 1; //id
}


//vector already filled with all frames version needs to be added!!!

inline uint32_t new_moving_vertex() {
  global::all_m_vertex.resize(global::all_m_vertex.size() + 1);
  return global::all_m_vertex.size() - 1;
}

inline void new_moving_vertex_frame(uint32_t mesh_id, std::vector<float> vertices, std::vector<float> uvs) {
  global::all_m_vertex[mesh_id].push_back(to_vertex(vertices, uvs));
}


inline uint32_t new_moving_indices(std::vector<uint32_t> indices) {
  global::all_m_indices.push_back(indices);
  return global::all_m_indices.size() - 1;
}




inline uint32_t new_rotation() {
  global::all_rotations.resize(global::all_rotations.size() + 1);
  return global::all_rotations.size() - 1;
}

inline uint32_t new_translation() {
  global::all_translations.resize(global::all_translations.size() + 1);
  return global::all_translations.size() - 1;
}

inline void new_rotation_frame(uint32_t id, float *rotation) {
  global::all_rotations[id].push_back(rotation);
}

inline void new_translation_frame(uint32_t id, float *translation) {
  global::all_translations[id].push_back(translation);
}

//mesh <id> has texture id <tid>
//mesh id is the id as the data is read in the drawing program -- all static ids followed by moving ids -- it goes in the order read from file
inline void static_mesh_has_texture(uint32_t id, uint32_t tid) {
  if (global::static_texture_ids.size() - 1 < id || global::static_texture_ids.size() == 0) {
    global::static_texture_ids.resize(id + 1);
  }
  global::static_texture_ids[id] = tid;
}
inline void moving_mesh_has_texture(uint32_t id, uint32_t tid) {
  if (global::moving_texture_ids.size() - 1 < id || global::moving_texture_ids.size() == 0) {
    global::moving_texture_ids.resize(id + 1);
  }
  global::moving_texture_ids[id] = tid;
}

#pragma once
#include <vector>
#include "vertex.h"

namespace global {
  //vectors that contain data required for reading the data effectively
  std::vector<unsigned> ubo_data; //movement data
  std::vector<unsigned> data; //static mesh data
  std::vector<unsigned> m_data; //animated mesh data

  //static mesh data
  std::vector<std::vector<Vertex>> all_vertex;
  std::vector<std::vector<uint32_t>> all_indicies;

  //animated mesh data
  std::vector<std::vector<std::vector<Vertex>>> all_m_vertex;
  std::vector<std::vector<uint32_t>> all_m_indices;

  //movement data
  std::vector<std::vector<float*>> all_translations;
  std::vector<std::vector<float*>> all_rotations;

  std::vector<uint32_t> static_texture_ids;
  std::vector<uint32_t> moving_texture_ids;
  std::vector<uint32_t> texture_data;

}

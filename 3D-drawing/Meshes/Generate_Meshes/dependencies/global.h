#pragma once
#include <vector>

namespace global {
  //vectors that contain data required for reading the data effectively
  std::vector<unsigned> ubo_data; //movement data
  std::vector<unsigned> data; //static mesh data
  std::vector<unsigned> m_data; //animated mesh data

  //static mesh data
  std::vector<std::vector<float>> all_vertices;
  std::vector<std::vector<float>> all_uvs;
  std::vector<std::vector<uint32_t>> all_indicies;

  //animated mesh data
  std::vector<std::vector<std::vector<float>>> all_m_vertices;
  std::vector<std::vector<std::vector<float>>> all_m_uvs;
  std::vector<std::vector<uint32_t>> all_m_indices;

  //movement data
  std::vector<std::vector<float*>> all_translations;
  std::vector<std::vector<float*>> all_rotations;

}

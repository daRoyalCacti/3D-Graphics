#pragma once
#include <vector>
#include "global.h"

int new_static_vertices(std::vector<float> vertices) {
  global::all_vertices.push_back(vertices);
  return global::all_vertices.size() - 1; //id
}

int new_static_indices(std::vector<uint32_t> indices) {
  global::all_indicies.push_back(indices);
  return global::all_indicies.size() - 1; //id
}

int new_static_uvs(std::vector<float> uvs) {
  global::all_uvs.push_back(uvs);
  return global::all_uvs.size() - 1;
}


int new_moving_vertices(std::vector<std::vector<float>> all_frames) {
  global::all_m_vertices.push_back(all_frames);
  return global::all_m_vertices.size();
}
int new_moving_vertices() {
  global::all_m_vertices.resize(global::all_m_vertices.size() + 1);
  return global::all_m_vertices.size() - 1;
}

void new_moving_vertices_frame(size_t mesh_id, std::vector<float> vertices) {
  global::all_m_vertices[mesh_id].push_back(vertices);
}

int new_moving_indices(std::vector<uint32_t> indices) {
  global::all_m_indices.push_back(indices);
  return global::all_m_indices.size() - 1;
}

int new_moving_uvs(std::vector<std::vector<float>> all_uvs) {
  global::all_m_uvs.push_back(all_uvs);
  return global::all_m_uvs.size() - 1;
}
int new_moving_uvs() {
  global::all_m_uvs.resize(global::all_m_uvs.size() + 1);
  return global::all_m_uvs.size() - 1;
}

void new_moving_uvs_frame(size_t mesh_id, std::vector<float> uvs) {
  global::all_m_uvs[mesh_id].push_back(uvs);
}

int new_rotation() {
  global::all_rotations.resize(global::all_rotations.size() + 1);
  return global::all_rotations.size() - 1;
}

int new_translation() {
  global::all_translations.resize(global::all_translations.size() + 1);
  return global::all_translations.size() - 1;
}

void new_rotation_frame(size_t id, float *rotation) {
  global::all_rotations[id].push_back(rotation);
}

void new_translation_frame(size_t id, float *translation) {
  global::all_translations[id].push_back(translation);
}

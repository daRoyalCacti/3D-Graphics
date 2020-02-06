#include <iostream>
#include <chrono>
#include "boring_test.h"
#include "main_writing.h"
#include "helper.h"
#include "shapes.h"

//#include "openCl_instance.h"

int main() {
  const int sphere_points = 20;
  auto start0 = std::chrono::high_resolution_clock::now();
  uint32_t id;

  id = new_static_vertex(shapes::cube::vertices(), shapes::cube::uvs()); new_static_indices(shapes::cube::indices()); static_mesh_has_texture(id, id);
  id = new_static_vertex(shapes::sphere::vertices(sphere_points), shapes::sphere::uvs(sphere_points)); new_static_indices(shapes::sphere::indices(sphere_points)); static_mesh_has_texture(id, id);
  id = new_static_vertex(shapes::cube::vertices(), shapes::cube::uvs()); new_static_indices(shapes::cube::indices()); static_mesh_has_texture(id, id);
  id = new_static_vertex(shapes::sphere::vertices(5), shapes::sphere::uvs(5)); new_static_indices(shapes::sphere::indices(5)); static_mesh_has_texture(id, id - 1);

  boring::create_moving_meshes();
  boring::create_movement();
  auto end0 = std::chrono::high_resolution_clock::now();
  std::cout << "Mesh generation took\t" << std::chrono::duration <double, std::milli>(end0 - start0).count() << "ms" << std::endl;

  auto start1 = std::chrono::high_resolution_clock::now();
  write_all();
  auto end1 = std::chrono::high_resolution_clock::now();
  std::cout << "File writing took\t" << std::chrono::duration <double, std::milli>(end1 - start1).count() << "ms" << std::endl;


  //testing
  /*const uint32_t size_data = 1e3;
  float data[size_data];
  float results[size_data];

  #pragma omp parallel for
  for (uint32_t i = 0; i < size_data; i++) {
    data[i] = i/100;
  }

  openCl_instance openCl;
  openCl.init();
  openCl.square(data, results, size_data);
  openCl.cleanup();*/


  return 0;
}

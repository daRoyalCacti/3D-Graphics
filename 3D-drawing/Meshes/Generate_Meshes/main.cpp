#include <iostream>
#include <chrono>
#include "boring_test.h"
#include "main_writing.h"
#include "helper.h"
#include "shapes.h"



int main() {
  //boring::create_static_meshes();
  const int sphere_points = 20;
  new_static_vertices(shapes::cube::vertices()); new_static_indices(shapes::cube::indices()); new_static_uvs(shapes::cube::uvs());
  new_static_vertices(shapes::sphere::vertices(sphere_points)); new_static_indices(shapes::sphere::indices(sphere_points)); new_static_uvs(shapes::sphere::uvs(sphere_points));
  new_static_vertices(shapes::cube::vertices()); new_static_indices(shapes::cube::indices()); new_static_uvs(shapes::cube::uvs());
  new_static_vertices(shapes::sphere::vertices(5)); new_static_indices(shapes::sphere::indices(5)); new_static_uvs(shapes::sphere::uvs(5));


  boring::create_moving_meshes();
  boring::create_movement();
  auto start0 = std::chrono::high_resolution_clock::now();
  write_all();
  auto end0 = std::chrono::high_resolution_clock::now();
  std::cout << "File writing took\t" << std::chrono::duration <double, std::milli>(end0 - start0).count() << "ms" << std::endl;

  return 0;
}

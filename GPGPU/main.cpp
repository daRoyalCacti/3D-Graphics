#include "openCl.h"
#include <chrono>
#include <iostream>


int main() {
  auto start = std::chrono::high_resolution_clock::now();

  openCl_instance openCl;
  int success = openCl.run();

  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "Completed in \t\t\t" << std::chrono::duration <double, std::milli>(end - start).count() << "ms" << std::endl;


  return success;
}

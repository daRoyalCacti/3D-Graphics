#include "openCl_instance.h"
#include <chrono>
#include <iostream>
#include <cmath>

const uint32_t size_data = 1e3;
const uint32_t size_data2 = 1e2;

float data[size_data];
float results[size_data];

float data2[size_data2];
float results2[size_data2];

int main() {
  auto start = std::chrono::high_resolution_clock::now();

  #pragma omp parallel for
  for (uint32_t i = 0; i < size_data; i++) { //to be made more concrete later
    data[i] = i/100;
  }

  #pragma omp parallel for
  for (uint32_t i = 0; i < size_data2; i++) {
    data2[i] = i/1000;
  }

  openCl_instance openCl;
  //openCl.run();
  openCl.init();
  openCl.square(data, results, size_data);
  openCl.square(data2, results2, size_data2);
  openCl.cleanup();

  #pragma omp parallel for
  for (uint32_t i = 0; i < size_data; i++) {
    if (fabs(results[i] - data[i] * data[i]) > 0.01) {
      std::cout << "error for group 1 at i = " << i << std::endl;
    }
  }

  #pragma omp parallel for
  for (uint32_t i = 0; i < size_data2; i++) {
    if (fabs(results2[i] - data2[i] * data2[i]) > 0.01) {
      std::cout << "error for group 2 at i = " << i << std::endl;
    }
  }


  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "Completed in \t\t\t" << std::chrono::duration <double, std::milli>(end - start).count() << "ms" << std::endl;


  return EXIT_SUCCESS;
}

#include <iostream>

#include "writing.h"

bitmap_t image_test;
std::string path = "../texture_4.png";

const int test_image_width = 100, test_image_height = 100;

int main() {
  image_test.width = test_image_width;
  image_test.height = test_image_height;
  image_test.pixels = new pixel_t[image_test.width * image_test.height];

  for (int i = 0; i < image_test.width; i++) {
    for (int j = 0; j < image_test.height; j++) {
      pixel_t* pixel = pixel_at(&image_test, i, j);
      pixel->red = i / (float)image_test.width * 255;
      pixel->green = i / (float)image_test.width * 255;
      pixel->blue = j / (float)image_test.height * 100;
    }
  }

  if (!generate_png(&image_test, path)) {
    std::cerr << "failed to generate png" << std::endl;
  }

  delete [] image_test.pixels;

  return 0;
}

#include <iostream>

#include "bitmaps.h"
#include "gradients.h"

const std::string file_location = "/home/george/Documents/Projects/Major-3D/3D-drawing/textures/";

const int image_width = 100, image_height = 100;  //used only for testing

namespace texture_examples = texture_generation::examples;

int main() {
  texture_generation::bitmaps_t images(texture_generation::bitmaps_t::get_main_output());

  images.add_Bitmap(texture_examples::gradient1(image_width / 2, image_height / 2));
  images.add_Bitmap(texture_examples::gradient2(image_width, image_height));
  images.add_Bitmap(texture_examples::gradient3(image_width, image_height));
  images.add_Bitmap(texture_examples::gradient4(image_width, image_height));
  images.add_Bitmap(texture_examples::gradient5(image_width, image_height));

  //images.write_images_png();
  images.write_images_bin();

  images.write_data();

  return 0;
}

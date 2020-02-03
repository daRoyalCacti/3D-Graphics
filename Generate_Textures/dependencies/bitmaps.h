#pragma once
#include <vector>
#include <cstdint>
#include <fstream>
#include <string>
#include <iostream>
#include "bitmap.h"

namespace texture_generation {
  struct bitmaps_t {

    std::string path;
    bitmaps_t(std::string output_location) : path(output_location) {}
    enum image_modes {EMPTY, PNG, BIN};
    uint32_t mode = EMPTY;

    std::vector<bitmap_t> bitmaps;
    std::vector<uint32_t> bitmapSizes;

    inline void add_Bitmap(bitmap_t bitmap) {
      bitmaps.push_back(bitmap);
      bitmapSizes.push_back(bitmap.width);
      bitmapSizes.push_back(bitmap.height);
    }

    inline void write_images_png() { //includes cleanup
      mode = PNG;
      for (auto& bitmap : bitmaps) {
        if (!bitmap.generate_png(path)) {
          std::cerr << "failed to generate png" << std::endl;
        }
        bitmap.cleanup();
      }
    }

    inline void write_images_bin() {
      mode = BIN;
      for (auto& bitmap : bitmaps) {
        bitmap.generate_bin(path);
        bitmap.cleanup();
      }
    }

    inline void write_data() {
      std::ofstream data(path + "data.bin", std::ios::binary);
      uint32_t no_images = bitmaps.size();
      data.write((char*)&no_images, sizeof(uint32_t));
      data.write((char*)&mode, sizeof(uint32_t));

      data.write((char*)&bitmapSizes[0], sizeof(uint32_t) * bitmapSizes.size());

      data.close();
    }

    __attribute__((const)) static inline const std::string get_main_output() {
      return "/home/george/Documents/Projects/Major-3D/3D-drawing/textures/";
    }

  };
}

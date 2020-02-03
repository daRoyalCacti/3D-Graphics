#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace texture_generation {
  class bitmap_t {
  private:
    uint8_t* pixels;

  public:

    uint8_t* pixel_at(int x, int y) {
      //a pointer to the pixles moved to the position given
      return pixels + (width * y + x) * 4;
    }

    size_t width;
    size_t height;


    bool generate_png(std::string path);

    void set_pixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
      uint8_t* pixel = pixel_at(x, y);
      *pixel++ = red;
      *pixel++ = green;
      *pixel++ = blue;
      *pixel = alpha;
    }

    inline void update_size() {
      pixels = new uint8_t[width * height * 4];
    }

    inline void set_dim(size_t w, size_t h) {
      width = w;
      height = h;
      update_size();
    }

    inline void cleanup() {
      delete [] pixels;
    }

    void generate_bin(std::string path);


  };
}

/*
##pragma once
#include <png.h>
#include <cstdint>
#include <string>
#include <vector>

struct pixel_t {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t alpha;
};

class bitmap_t {
private:
  pixel_t* pixels;

public:

  pixel_t* pixel_at(int x, int y) {
    //a pointer to the pixles moved to the position given
    return pixels + width * y + x;
  }

  size_t width;
  size_t height;


  bool generate_png(std::string path);

  void set_pixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
    pixel_t* pixel = pixel_at(x, y);
    pixel->red = red;
    pixel->green = green;
    pixel->blue = blue;
    pixel->alpha = alpha;
  }

  inline void update_size() {
    pixels = new pixel_t[width * height];
  }

  inline void set_dim(size_t w, size_t h) {
    width = w;
    height = h;
    update_size();
  }

  inline void cleanup() {
    delete [] pixels;
  }

  void generate_bin(std::string path);
*/

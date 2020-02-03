#pragma once
#include "bitmap.h"

namespace texture_generation {
    namespace examples {


    __attribute__((const)) inline bitmap_t gradient1(size_t width, size_t height) {
      bitmap_t image;
      image.set_dim(width ,height);

      for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
          image.set_pixel(i, j,
          i / (float)width * 255,
          i / (float)width * 255,
          j / (float)height * 255,
          255);
        }
      }
      return image;
    }

    __attribute__((const)) inline bitmap_t gradient2(size_t width, size_t height) {
      bitmap_t image;
      image.set_dim(width ,height);

      for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
          image.set_pixel(i, j,
          i / (float)width * 255,
          j / (float)height * 255,
          j / (float)height * 255,
          255);
        }
      }
      return image;
    }

    __attribute__((const)) inline bitmap_t gradient3(size_t width, size_t height) {
      bitmap_t image;
      image.set_dim(width ,height);

      for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
          image.set_pixel(i, j,
          0,
          i / (float)width * 255,
          j / (float)height * 255,
          255);
        }
      }
      return image;
    }

    __attribute__((const)) inline bitmap_t gradient4(size_t width, size_t height) {
      bitmap_t image;
      image.set_dim(width ,height);

      for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
          image.set_pixel(i, j,
          i / (float)width * 255,
          j / (float)height * 255,
          i / (float)width * 255,
          255);
        }
      }
      return image;
    }

    __attribute__((const)) inline bitmap_t gradient5(size_t width, size_t height) {
      bitmap_t image;
      image.set_dim(width ,height);

      for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
          image.set_pixel(i, j,
          i / (float)width * 255,
          0,
          j / (float)height * 255,
          255);
        }
      }
      return image;
    }

  }
}

/*
#pragma once
#include "helper.h"


inline void gradient1(bitmap_t* image, size_t width, size_t height) {
  image->width = width;
  image->height = height;
  image->pixels = new pixel_t[width * height];

  for (size_t i = 0; i < width; i++) {
    for (size_t j = 0; j < height; j++) {
      pixel_t* pixel = pixel_at(image, i, j);
      pixel->red = i / (float)width * 255;
      pixel->green = i / (float)width * 255;
      pixel->blue = j / (float)height * 255;
    }
  }
}

inline void gradient2(bitmap_t* image, size_t width, size_t height) {
  image->width = width;
  image->height = height;
  image->pixels = new pixel_t[width * height];

  for (size_t i = 0; i < width; i++) {
    for (size_t j = 0; j < height; j++) {
      pixel_t* pixel = pixel_at(image, i, j);
      pixel->red = i / (float)width * 255;
      pixel->green = j / (float)height * 255;
      pixel->blue = j / (float)height * 255;
    }
  }
}

inline void gradient3(bitmap_t* image, size_t width, size_t height) {
  image->width = width;
  image->height = height;
  image->pixels = new pixel_t[width * height];

  for (size_t i = 0; i < width; i++) {
    for (size_t j = 0; j < height; j++) {
      pixel_t* pixel = pixel_at(image, i, j);
      pixel->red = 0;
      pixel->green = i / (float)width * 255;
      pixel->blue = j / (float)height * 255;
    }
  }
}

inline void gradient4(bitmap_t* image, size_t width, size_t height) {
  image->width = width;
  image->height = height;
  image->pixels = new pixel_t[width * height];

  for (size_t i = 0; i < width; i++) {
    for (size_t j = 0; j < height; j++) {
      pixel_t* pixel = pixel_at(image, i, j);
      pixel->red = i / (float)width * 255;
      pixel->green = j / (float)height * 255;
      pixel->blue = i / (float)width * 255;
    }
  }
}

inline void gradient5(bitmap_t* image, size_t width, size_t height) {
  image->width = width;
  image->height = height;
  image->pixels = new pixel_t[width * height];

  for (size_t i = 0; i < width; i++) {
    for (size_t j = 0; j < height; j++) {
      pixel_t* pixel = pixel_at(image, i, j);
      pixel->red = i / (float)width * 255;
      pixel->green = 0;
      pixel->blue = j / (float)height * 255;
    }
  }
}
*/

#include "bitmap.h"
#include <iostream>
#include <png.h>
#include <fstream>

namespace texture_generation {
  bool bitmap_t::generate_png(std::string path ) {
    static unsigned mesh_num = 0;
    //the file
    FILE * fp;

    //no clue
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    png_byte** row_pointers = NULL;

    int pixel_size = 3; //rgb?
    int depth = 8; //stored as uint8??

    fp = fopen((path + "texture_" + std::to_string(mesh_num++) + ".png").c_str(), "wd");
    if (! fp) {
      std::cerr << "failed to open file" << std::endl;
      return false;
    }

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL) {
      std::cerr << "failed to create write struct" << std::endl;
      fclose(fp);
      return false;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
      std::cerr << "failed to create info struct" << std::endl;
      png_destroy_write_struct(&png_ptr, &info_ptr);
      fclose(fp);
      return false;
    }

    //wtf is setjmp
    if (setjmp(png_jmpbuf(png_ptr))) {
      std::cerr << "failed to png at some point" << std::endl;
      png_destroy_write_struct(&png_ptr, &info_ptr);
      fclose(fp);
      return false;
    }

    png_set_IHDR (png_ptr,
                    info_ptr,
                    width,
                    height,
                    depth,
                    PNG_COLOR_TYPE_RGB,
                    PNG_INTERLACE_NONE,
                    PNG_COMPRESSION_TYPE_DEFAULT,
                    PNG_FILTER_TYPE_DEFAULT);

    row_pointers = (png_byte**)png_malloc(png_ptr, height * sizeof(png_byte*));
  #pragma omp parallel for
    for (size_t y = 0; y < height; y++) {
      png_byte* row = (png_byte*)png_malloc(png_ptr, sizeof(uint8_t) * width * pixel_size); //used later
      row_pointers[y] = row;
      for (size_t x = 0; x < width; x++) {
        uint8_t* pixel = pixel_at(x, y);
        *row++ = *pixel++;
        *row++ = *pixel++;
        *row++ = *pixel;
      }
    }


    png_init_io(png_ptr, fp);
    png_set_rows(png_ptr, info_ptr, row_pointers);
    png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

    for (size_t i = 0; i < height; i++) {
      png_free(png_ptr, row_pointers[i]);
    }
    png_free(png_ptr, row_pointers);

    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);

    //did work
    return true;
  }


  void bitmap_t::generate_bin(std::string path) {
    static unsigned mesh_num = 0;

    std::ofstream output(path + "texture_" + std::to_string(mesh_num++) + ".bin", std::ios::binary);
    output.write((char*)&pixels[0], (width * height * 4) * sizeof(uint8_t));
    output.close();
  }
}

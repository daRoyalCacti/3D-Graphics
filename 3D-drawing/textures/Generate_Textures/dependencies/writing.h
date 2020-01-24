#include <png.h>

struct pixel_t {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};

struct bitmap_t{
  pixel_t* pixels;
  size_t width;
  size_t height;
};

static pixel_t* pixel_at(bitmap_t* bitmap, int x, int y) {
  return bitmap->pixels + bitmap->width * y + x;
}

int generate_png(bitmap_t *bitmap, std::string path ) {
  //the file
  FILE * fp;

  //no clue
  png_structp png_ptr = NULL;
  png_infop info_ptr = NULL;
  png_byte** row_pointers = NULL;

  int pixel_size = 3; //rgb?
  int depth = 8; //stored as uint8??

  fp = fopen(path.c_str(), "wd");
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
                  bitmap->width,
                  bitmap->height,
                  depth,
                  PNG_COLOR_TYPE_RGB,
                  PNG_INTERLACE_NONE,
                  PNG_COMPRESSION_TYPE_DEFAULT,
                  PNG_FILTER_TYPE_DEFAULT);

  row_pointers = (png_byte**)png_malloc(png_ptr, bitmap->height * sizeof(png_byte*));
#pragma omp parallel for
  for (int y = 0; y < bitmap->height; y++) {
    png_byte* row = (png_byte*)png_malloc(png_ptr, sizeof(uint8_t) * bitmap->width * pixel_size); //used later
    row_pointers[y] = row;
    for (int x = 0; x < bitmap->width; x++) {
      pixel_t* pixel = pixel_at(bitmap, x, y);
      *row++ = pixel->red;
      *row++ = pixel->green;
      *row++ = pixel->blue;
    }
  }


  png_init_io(png_ptr, fp);
  png_set_rows(png_ptr, info_ptr, row_pointers);
  png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

  for (int i = 0; i < bitmap->height; i++) {
    png_free(png_ptr, row_pointers[i]);
  }
  png_free(png_ptr, row_pointers);

  png_destroy_write_struct(&png_ptr, &info_ptr);
  fclose(fp);
  //did work
  return true;
}

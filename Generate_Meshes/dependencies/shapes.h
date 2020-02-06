#pragma once
#include <vector>
#include <cmath>
#include <iostream>

namespace shapes {
  namespace cube {
    __attribute__((const)) inline std::vector<float> vertices() {
      return {
        -0.5f, -0.5f, -0.5f, //0  -  0
         0.5f, -0.5f, -0.5f, //1  -  1
         0.5f, -0.5f,  0.5f, //2  -  2
         -0.5f, -0.5f,  0.5f, //3  -  3

        -0.5f,  0.5f, -0.5f, //4  -  4
        -0.5f,  0.5f, -0.5f, //4.1 - 5
        -0.5f,  0.5f, -0.5f, //4.2 - 6

         0.5f,  0.5f, -0.5f, //5  -  7
         0.5f,  0.5f, -0.5f, //5.1 - 8

         0.5f,  0.5f,  0.5f, //6  -  9
         0.5f,  0.5f,  0.5f, //6.1 - 10

        -0.5f,  0.5f,  0.5f, //7  -  11
        -0.5f,  0.5f,  0.5f, //7.1 - 12
        -0.5f,  0.5f,  0.5f //7.2 - 13
      };
    }

    __attribute__((const)) inline std::vector<float> uvs() {
      return {
        0.25f, 0.66f, //0  -  0
        0.5f, 0.66f, //1  -  1
        0.5f, 0.34f, //2  -  2
        0.25f, 0.34f, //3  -  3

        0.25f,  1.0f, //4  -  4
        0.0f, 0.66f, //4.1 - 5
        1.0f, 0.66f, //4.2 - 6

        0.5f,  1.0f, //5  -  7
        0.75f, 0.66f, //5.1 - 8

        0.5f,  0.0f, //6  -  9
        0.75f, 0.34f, //6.1 - 10

        0.25f,  0.0f, //7  -  11
        0.0f, 0.34f, //7.1 - 12
        1.0f, 0.34f  //7.2 - 13
      };
    }

    __attribute__((const)) inline std::vector<uint32_t> indices() {
      return {
        0,  1, 2,  2,  3, 0,  //bottom
        0,  4, 1,  1,  4, 7,  //front
        3,  2, 11, 11, 2, 9,  //back
        1,  8, 2,  2,  8, 10, //right
        0,  3, 5,  5,  3, 12, //left
        10, 8, 13, 13, 8, 6   //top
      };
    }

  } //end cube

  namespace sphere {
    __attribute__((const)) inline std::vector<float> vertices(unsigned rows = 10) {
      std::vector<float> vertex;
      vertex.resize(rows*rows * 3);


      int counter = 0;
      for (double i = 0; i <= M_PI; i+= M_PI/(double)(rows - 1)) { // no idea why rows - 1 and not just rows
        for (double j = 0; j <= 2 * M_PI; j+= 2 * M_PI/(double)(rows - 1)) {
          vertex[counter++] = static_cast<float>(sin(i)*cos(j));
          vertex[counter++] = static_cast<float>(sin(i)*sin(j));
          vertex[counter++] = static_cast<float>( cos(i));
        }
      }
      return vertex;
    }

    __attribute__((const)) inline std::vector<uint32_t> indices(unsigned rows = 10) {
      std::vector<uint32_t> index;
      index.resize((rows - 1) * (rows) * 6);

      int counter = 0;
      for (uint32_t j = 0; j < rows - 1; j++) {
        for (uint32_t i = 0; i < rows; i++) {
          index[counter++] = j + i * (rows  - 1);
          index[counter++] = j + (i + 1) * (rows  - 1);
          index[counter++] = j + (i + 1) * (rows  - 1) + 1;
          index[counter++] = j + (i + 1) * (rows  - 1) + 1;
          index[counter++] = j + 1 + i * (rows  - 1);
          index[counter++] = j + i * (rows  - 1);

        }
      }

      return index;
    }

    __attribute__((const)) inline std::vector<float> uvs(unsigned rows = 10) {
      std::vector<float> uv;
      uv.resize(rows * rows * 2);

      int counter = 0;
      for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < rows; j++) {
          uv[counter++] = i / (float)rows;
          uv[counter++] = j / (float)rows;
        }
      }

      return uv;
    }

  } //end sphere

} //end shapes

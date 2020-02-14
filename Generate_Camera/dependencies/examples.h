#pragma once
#include <glm/glm.hpp>

namespace Camera_Generation {
  namespace Examples {
    namespace pos {
      template<typename T>
      std::vector<glm::vec3> stationary(const glm::vec3 position, const T size) {
        std::vector<glm::vec3> return_vec;
        return_vec.resize(size);
        std::fill(return_vec.begin(), return_vec.end(),position);
        return return_vec;
      }
    }

    namespace pitch {
      template<typename T>
      std::vector<float> stationary(const double pitch, const T size) {
        std::vector<float> return_vec;
        return_vec.resize(size);
        std::fill(return_vec.begin(), return_vec.end(), pitch);
        return return_vec;
      }

    }

    namespace yaw {
      template<typename T>
      std::vector<float> stationary(const double yaw, const T size) {
        std::vector<float> return_vec;
        return_vec.resize(size);
        std::fill(return_vec.begin(), return_vec.end(), yaw);
        return return_vec;
      }

      template<typename T, typename U>
      std::vector<float> unif_rotate(const U rotation, const T size) {
        std::vector<float> return_vec;
        return_vec.resize(size);
        const U rotation_step = 360 / (double) rotation;
        for (T i = 0; i < size; i++) {
          return_vec[i] = rotation_step * i;
        }

        return return_vec;
      }

    }


  }
}

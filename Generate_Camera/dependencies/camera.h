#pragma once
#include <glm/glm.hpp>
#include <vector>

namespace Camera_Generation {

  struct Camera {
    std::string file_location;
    const uint32_t no_frames;

    std::vector<glm::vec3> positions;
    std::vector<float> yaws;
    std::vector<float> pitches;

    Camera(std::string file, const uint32_t frames) : file_location(file), no_frames(frames) {positions.resize(frames); yaws.resize(frames); pitches.resize(frames);}

    inline void set_positions(std::vector<glm::vec3> pos) {
      positions = pos;
    }

    inline void set_pitch(std::vector<float> pitch) {
      pitches = pitch;
    }

    inline void set_yaw(std::vector<float> yaw) {
      yaws = yaw;
    }

    inline void write() {
      std::ofstream data(file_location + "data.bin", std::ios::binary);
      data.write((char*)&no_frames, sizeof(uint32_t));
      data.close();

      std::ofstream pos(file_location + "pos.bin", std::ios::binary);
      pos.write((char*)&positions[0], sizeof(glm::vec3) * positions.size());
      pos.close();

      std::ofstream yaw(file_location + "yaw.bin", std::ios::binary);
      yaw.write((char*)&yaws[0], sizeof(float) * yaws.size());
      yaw.close();

      std::ofstream pitch(file_location + "pitch.bin", std::ios::binary);
      pitch.write((char*)&pitches[0], sizeof(float) * pitches.size());
      pitch.close();
    }

    __attribute__((const)) static inline const std::string get_main_output() {
      return "/home/george/Documents/Projects/Major-3D/3D-drawing/Camera/";
    }

  };

}

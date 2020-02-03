#pragma once
#include <vector>
#include "helper.h"

namespace boring {
  //plane thingo
  const std::vector<float> Vertices = {
    0.5f, 0.5f, 0.5f,
    1.5f, 0.5f, 0.5f,
    1.5f, 1.5f, 0.5f,
    0.5f, 1.5f, 0.5f
  };

  const std::vector<float> UVs = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f
  };

  const std::vector<uint32_t> indices = {
    0, 1, 2, 2, 3, 0
  };

  //stuffed plane
  const std::vector<float> Vertices2 = {
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    -1.0f, 1.0f, -1.0f
  };

  const std::vector<float> Uvs2 = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 1.0f
  };

  const std::vector<uint32_t> indices2 = {
    0, 1, 2, 2, 3, 0,
    2,4,0
  };

  //cube
  const std::vector<float> Vertices3 = {
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

  const std::vector<float> Uvs3 = {
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

  const std::vector<uint32_t> indices3 = {
    0,  1, 2,  2,  3, 0,  //bottom
    0,  4, 1,  1,  4, 7,  //front
    3,  2, 11, 11, 2, 9,  //back
    1,  8, 2,  2,  8, 10, //right
    0,  3, 5,  5,  3, 12, //left
    10, 8, 13, 13, 8, 6   //top
  };


  const std::vector<float> m_Vertices1_0 = {
    0.5f, 0.5f, 0.5f,
    1.5f, 0.5f, 0.5f,
    1.5f, 1.5f, 0.5f,
    0.5f, 1.5f, 0.5f
  };

  const std::vector<float> m_Vertices1_1 = {
    0.5f, 0.5f, 0.5f,
    1.5f, 0.5f, 0.5f,
    1.5f, 1.5f, 0.5f,
    1.5f, 1.5f, 1.5f
  };

  const std::vector<uint32_t> m_indices1 = {
    0, 1, 2, 2, 3, 0
  };

  const std::vector<float> m_Uvs1_0 = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f
  };


  float rotations_1[4] = {-90.0f, 1.0f, 0.0f, 0.0f};
  float translations_1[3] = {0.0f, 0.0f, 0.0f};

  float rotations_2[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  float translations_2[3] = {0.0f, 0.0f, 0.0f};

  float rotations_2_0[4] = {2.0f, 0.0f, 0.0f, 1.0f};
  float translations_2_0[3] = {0.0f, 2.0f, 0.0f};

  float rotations_3[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  float translations_3[3] = {0.0f, 1.0f, 0.0f};

  float rotations_4[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  float translations_4[3] = {0.0f, 2.0f, 2.0f};

  float rotations_5[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  float translations_5[3] = {0.0f, 2.0f, 4.0f};


  void create_static_meshes() {
    new_static_vertices(Vertices);
    new_static_indices(indices);
    new_static_uvs(UVs);

    new_static_vertices(Vertices2);
    new_static_indices(indices2);
    new_static_uvs(Uvs2);

    new_static_vertices(Vertices3);
    new_static_indices(indices3);
    new_static_uvs(Uvs3);
  }

  void create_moving_meshes() {
    uint32_t id;
    //mesh 1
    id = new_moving_vertices();
    new_moving_vertices_frame(id, m_Vertices1_0);
    new_moving_vertices_frame(id, m_Vertices1_1);
    new_moving_indices(m_indices1);
    moving_mesh_has_texture(id, id);
    id = new_moving_uvs();
    new_moving_uvs_frame(id, m_Uvs1_0);
    new_moving_uvs_frame(id, m_Uvs1_0);
  }

  void create_movement() {
    int id;
    id = new_rotation();
    new_rotation_frame(id, rotations_1);
    id = new_translation();
    new_translation_frame(id, translations_1);

    id = new_rotation();
    new_rotation_frame(id, rotations_2);
    new_rotation_frame(id, rotations_2_0);
    id = new_translation();
    new_translation_frame(id, translations_2);
    new_translation_frame(id, translations_2_0);

    id = new_rotation();
    new_rotation_frame(id, rotations_3);
    id = new_translation();
    new_translation_frame(id, translations_3);

    id = new_rotation();
    new_rotation_frame(id, rotations_4);
    id = new_translation();
    new_translation_frame(id, translations_4);

    id = new_rotation();
    new_rotation_frame(id, rotations_5);
    id = new_translation();
    new_translation_frame(id, translations_5);
  }


} //end namespace

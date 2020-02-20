#pragma once
#include <vector>
#include <limits>

//need a check to make sure number of data points are fine

template <typename T, typename U, typename W>
inline std::vector<float> cartesian_to_verticies(T* data, U xpoints, W ypoints, const bool axes = 0 /*1 = xyz, 0 = xzy*/) {
  std::vector<float> return_vec;
  const Q total_points = xpoints * ypoints * 3;  //can never be greater than uint32_t MAX or else vulkan app will break
  return_vec.resize(total_points);

  if (axes) {
    #pragma omp parallel for
    for (Q i = Q(0); i < total_points; i+= 3) {
      return_vec[i] = data[i];
      return_vec[i + 1] = data[i + 1];
      return_vec[i + 2] = data[i + 2];
    }
  } else {
    #pragma omp parallel for
    for (Q i = Q(0); i < total_points; i+= 3) {
      return_vec[i] = data[i];
      return_vec[i + 1] = data[i + 2];
      return_vec[i + 2] = data[i + 1];
    }
  }

  return return_vec;
}

template <typename T, typename U, typename W>
inline std::vector<float> cartesian_to_texture(T* data, U xpoints, W ypoints, const bool axes = 0 /*1 = xyz, 0 = xzy*/) {
  //axes should be the same as is "cartesian_to_verticies"
  std::vector<float> return_vec;
  const Q total_points = xpoints * ypoints * 3;
  return_vec.resize(total_points / 3 * 2);  //integer division is fine because T must be divisable by 3 because every point has an x,y,z component





  //max and min must lie between the max and min of T purely because the data is of type T -- thus T is the data type
  //max and min values
  T maxx = std::numeric_limits<T>::min();
  T minx = std::numeric_limits<T>::max();
  T maxy = std::numeric_limits<T>::min();
  T miny = std::numeric_limits<T>::max();



  if (axes) {
    //#pragma omp parallel for
    for (Q i = Q(0); i < total_points; i+=3) {
      if (data[i] > maxx) maxx = data[i];
      if (data[i] < minx) minx = data[i];
      if (data[i + 2] > maxy) maxy = data[i + 2];
      if (data[i + 2] < miny) miny = data[i + 2];
    }
  } else {
    //#pragma omp parallel for
    for (Q i = Q(0); i < total_points; i+=3) {
      if (data[i] > maxx) maxx = data[i];
      if (data[i] < minx) minx = data[i];
      if (data[i + 1] > maxy) maxy = data[i + 1];
      if (data[i + 1] < miny) miny = data[i + 1];
    }
  }


  //double because used in division and float may not have enough precision to represent the range properly
  //  range for uint32_t has 10 digits -- floats tend to have 7 correct digits
  double rangex = maxx - minx;
  double rangey = maxy - miny;


  if (axes) {
    #pragma omp parallel for
    for (Q i = Q(0); i < total_points; i+=3) {
      const Q j = i / 3 * 2;
      return_vec[j] = static_cast<float>((static_cast<T>(data[i]) - minx) / rangex);
      return_vec[j + 1] = static_cast<float>((static_cast<T>(data[i + 2]) - miny) / rangey);
    }
  } else {
    #pragma omp parallel for
    for (Q i = Q(0); i < total_points; i+=3) {
      const Q j = i / 3 * 2;
      return_vec[j] = static_cast<float>((static_cast<T>(data[i]) - minx) / rangex);
      return_vec[j+ 1] = static_cast<float>((static_cast<T>(data[i + 1]) - miny) / rangey);
    }
  }


  return return_vec;
}

template <typename T, typename U, typename W>
inline std::vector<float> cartesian_to_texture(T* data, U xpoints, W ypoints, T minx, T maxx, T miny, T maxy, const bool axes = 0 /*1 = xyz, 0 = xzy*/) {
  //axes should be the same as is "cartesian_to_verticies"
  std::vector<float> return_vec;
  const Q total_points = xpoints * ypoints * 3;
  return_vec.resize(total_points / 3 * 2);  //integer division is fine because T must be divisable by 3 because every point has an x,y,z component

  //double because used in division and because float may overflow
  double rangex = maxx - minx;
  double rangey = maxy - miny;


  if (axes) {
    #pragma omp parallel for
    for (Q i = Q(0); i < total_points; i+=3) {
      const Q j = i / 3 * 2;
      return_vec[j] = static_cast<float>((static_cast<T>(data[i]) - minx) / rangex);
      return_vec[j + 1] = static_cast<float>((static_cast<T>(data[i + 2]) - miny) / rangey);
    }
  } else {
    #pragma omp parallel for
    for (Q i = Q(0); i < total_points; i+=3) {
      const Q j = i / 3 * 2;
      return_vec[j] = static_cast<float>((static_cast<T>(data[i]) - minx) / rangex);
      return_vec[j+ 1] = static_cast<float>((static_cast<T>(data[i + 1]) - miny) / rangey);
    }
  }


  return return_vec;
}

template <typename U, typename W>
inline std::vector<uint32_t> cartesian_to_indices(U xpoints, W ypoints, const bool dir = 1 /*1 = ccw, 0 = cw*/) {
  //doesn't need data because the index array only depends on the laypout of the mesh not any specifics about the mesh
  //  the layout is always fixed -- cartesian
  std::vector<uint32_t> return_vec;
  const Q useful_points = (xpoints - 1) * (ypoints - 1) * 6;
  return_vec.resize(useful_points);

  const Q ct_xpoints = static_cast<Q>(xpoints);
  const Q ct_ypoints = static_cast<Q>(ypoints);


  if (dir == 1) {
    //rotation direction one -- ccw
    #pragma omp parallel for
    for (Q i = Q(0); i < ct_xpoints - 1; i++) {
      for (Q j = Q(0); j < ct_ypoints - 1; j++) {
        const Q index1 = (j + i * (ypoints - 1)) * 6;
        const Q index2 = (j + i * (ypoints));
        return_vec[index1] = index2;                    //intial point
        return_vec[index1 + 1] = index2 + 1;            //right 1
        return_vec[index1 + 2] = index2 + 1 + ypoints;  //right 1 up 1

        return_vec[index1 + 3] = index2 + 1 + ypoints;  //right 1 up 1
        return_vec[index1 + 4] = index2 + ypoints;      //up 1
        return_vec[index1 + 5] = index2;                //initial point
      }
    }
  } else {
    //rotation direction two -- cw
    #pragma omp parallel for
    for (Q i = Q(0); i < ct_xpoints - 1; i++) {
      for (Q j = Q(0); j < ct_ypoints - 1; j++) {
        const Q index1 = (j + i * (ypoints - 1)) * 6;
        const Q index2 = (j + i * (ypoints));
        return_vec[index1] = index2;                   //initial point
        return_vec[index1 + 1] = index2 + ypoints;     //up 1
        return_vec[index1 + 2] = index2 + 1 + ypoints; //right 1 up 1

        return_vec[index1 + 3] = index2 + 1 + ypoints; //right 1 up 1
        return_vec[index1 + 4] = index2 + 1;           //right 1
        return_vec[index1 + 5] = index2;               //initial point
      }
    }

  }


  return return_vec;
}

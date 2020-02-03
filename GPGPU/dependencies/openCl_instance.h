#pragma once

#include <CL/cl.hpp>



class openCl_instance {
private:
  cl_int err;
  cl_mem input_data;
  cl_mem output_data;

  cl_platform_id platform_id; //used to identify an opencl platform
  cl_uint num_platforms;
  const cl_uint platform_entries = 1;

  cl_device_id device_id; //used to identify an opencl compute device
  cl_uint num_of_devices;
  const cl_uint device_entries = 1;
  cl_device_type device_type = CL_DEVICE_TYPE_GPU; // other possibilities : CL_DEVICE_TYPE_CPU, CL_DEVICE_TYPE_ACCELERATOR, CL_DEVICE_TYPE_DEFAULT, CL_DEVICE_TYPE_ALL

  cl_context context;
  cl_context_properties properties[3]; //complicated and i dont really understand how it works

  cl_command_queue command_queue;

  cl_program program;

public:


  const char* programPath = "/home/george/Documents/Projects/CPP/GPGPU/gpu_code/square.cl";//"./gpu_code/square.cl";

  cl_kernel kernel;


  //void fill_data();

  void query_platform();

  void query_device();

  void create_context();

  void create_command_queue();

  void create_program_object_square();

  void build_program_square();

  void create_kernel_objects_square();

  void create_buffers_square(const uint32_t size);

  void write_to_buffers_square(float* input, const uint32_t size);

  void set_kernel_arguments_square();

  void enqueue_kernel_square(const uint32_t size);

  void read_from_buffers_square(float* output, const uint32_t size);

  void cleanup();

  //void run();

  void init();

  void square(float* input, float* output, const uint32_t size);
};

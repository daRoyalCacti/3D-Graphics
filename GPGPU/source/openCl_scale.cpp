#include "openCl_instance.h"
#include "error_checking.h"
#include <iostream>
#include <sstream>
#include <fstream>

const char* programPath_scale = "/home/george/Documents/Projects/Major-3D/GPGPU/gpu_code/scale.cl";

void openCl_instance::create_program_object_scale() {
  //creating the program object
  //a program is a collection of kernel functions -- kernel functions are what execute on device
  //===============================================================================================================================================================================================================
  //===============================================================================================================================================================================================================

  //reading in the program code as strings
  std::string programCode;
  std::ifstream programFile;

  try {
    programFile.open(programPath_scale);
    std::stringstream programStream;
    programStream << programFile.rdbuf();
    programFile.close();
    programCode = programStream.str();
  }
  catch (std::ifstream::failure& e) {
    std::cerr << "Program file could not be read at " << programPath_scale << std::endl;
  }

  const char* ProgramSource = programCode.c_str();

  program = clCreateProgramWithSource(
    context,
    1, //the number of strings in the next parameter
    (const char**) &ProgramSource, //the array of strings
    NULL, //the length of each string -- can be NULL terminated
    &err
  );

  cl_check_result(err, "clCreateProgramWithSource");


}

void openCl_instance::build_program_scale() {
  //Building program executables
  //compiling and linking the program object
  //===============================================================================================================================================================================================================
  err = clBuildProgram(
    program,
    0,    //number of devices in device list
    NULL, //device list -- NULL means all devices
    NULL, //a string of build options -- too many to state here
    NULL, //callback function
    NULL  //data arguments for callback function
  );

  //error checking
  //special error checking if kernel compiling fails
  //  needs to be called first because 'cl_check_result' exits
  if (err == CL_BUILD_PROGRAM_FAILURE) {
      std::cerr << "\tThere is a failure to build the program executable" << std::endl;

      //logging the build log
      char buffer[4096];
      size_t length;

      err = clGetProgramBuildInfo(
        program,
        device_id,//the device the executable was built for
        CL_PROGRAM_BUILD_LOG, //could also be CL_PROGRAM_BUILD_OPTIONS, CL_PROGRAM_BUILD_LOG
        sizeof(buffer), //size of buffer to write log to
        buffer, //the actual buffer
        &length //the acutal size in bytes of the log
      );

      cl_check_result(err, "clGetProgramBuildInfo");

      std::cout << "\nBuild Log:" << std::endl;
      std::printf("%s\n", buffer);
      exit(EXIT_FAILURE);
    }
  cl_check_result(err, "clBuildProgram");





}

void openCl_instance::create_kernel_objects_scale() {
  //creating kernel objects
  //kernel objects are an encapsulation of a __kernel function
  //===============================================================================================================================================================================================================

  kernel = clCreateKernel(
    program,
    "scale", //the name of kernel
    &err
  );

  //error checking
  cl_check_result(err, "clCreateKernel");

}

void openCl_instance::create_buffers_scale(const uint32_t size) {
  //Creating Buffers
  //===============================================================================================================================================================================================================
  input_data = clCreateBuffer(
    context,
    CL_MEM_READ_ONLY, //bit field used to specify the usage of memory -- possibilities are CL_MEM_READ_WRITE, CL_MEM_WRITE_ONLY, CL_MEM_READ_ONLY, CL_MEM_USE_HOST_PTR, CL_MEM_ALLOC_HOST_PTR, CL_MEM_COPY_HOST_PTR
    sizeof(float) * size,  //size in bytes of teh buffer to allocate
    NULL, //pointer to buffer data
    &err
  );

  cl_check_result(err, "clCreateBuffer");


  other_data = clCreateBuffer(
    context,
    CL_MEM_READ_ONLY, //bit field used to specify the usage of memory -- possibilities are CL_MEM_READ_WRITE, CL_MEM_WRITE_ONLY, CL_MEM_READ_ONLY, CL_MEM_USE_HOST_PTR, CL_MEM_ALLOC_HOST_PTR, CL_MEM_COPY_HOST_PTR
    sizeof(float),  //size in bytes of teh buffer to allocate
    NULL, //pointer to buffer data
    &err
  );

  cl_check_result(err, "clCreateBuffer");

  output_data = clCreateBuffer(
    context,
    CL_MEM_WRITE_ONLY, //bit field used to specify the usage of memory -- possibilities are CL_MEM_READ_WRITE, CL_MEM_WRITE_ONLY, CL_MEM_READ_ONLY, CL_MEM_USE_HOST_PTR, CL_MEM_ALLOC_HOST_PTR, CL_MEM_COPY_HOST_PTR
    sizeof(float) * size, //size in bytes of teh buffer to allocate
    NULL, //pointer to buffer data
    &err
  );

  cl_check_result(err, "clCreateBuffer");
}

void openCl_instance::write_to_buffers_scale(float* input, float* scale, const uint32_t size) {
  //Writing data to Buffers
  //===============================================================================================================================================================================================================
  err = clEnqueueWriteBuffer(
    command_queue,
    input_data, //memory buffer object to write to
    CL_TRUE, //true for blocking write -- not returned immediately
    0, //offset in the buffer object to write to
    sizeof(float) * size, //size in bytes of data to write
    input, // pointer to buffer in host memory to read data from
    0, //number of events in events list
    NULL, //events list that need to be complete before this will execute
    NULL //event object to return on completetion
  );

  cl_check_result(err, "clEnqueueWriteBuffer");


  err = clEnqueueWriteBuffer(
    command_queue,
    other_data, //memory buffer object to write to
    CL_TRUE, //true for blocking write -- not returned immediately
    0, //offset in the buffer object to write to
    sizeof(float), //size in bytes of data to write
    scale, // pointer to buffer in host memory to read data from
    0, //number of events in events list
    NULL, //events list that need to be complete before this will execute
    NULL //event object to return on completetion
  );

  cl_check_result(err, "clEnqueueWriteBuffer");
}

void openCl_instance::set_kernel_arguments_scale() {
  //setting kernel arguments
  //the arguments set in the __kernel function
  //===============================================================================================================================================================================================================
  //setting values for argument 0
  err = clSetKernelArg(
    kernel,
    0,  //kernel index
    sizeof(cl_mem), //arg size
    &input_data //arg value
  );

  //error checking
  cl_check_result(err, "clSetKernelArg");


  //setting values for argument 1
  err = clSetKernelArg(
    kernel,
    1,  //kernel index
    sizeof(cl_mem), //arg size
    &output_data //arg value
  );

  //error checking
  cl_check_result(err, "clSetKernelArg");
  //clGetKernelInfo(..) can be used to query information about the kernel object

  //setting values for argument 2
  err = clSetKernelArg(
    kernel,
    2,  //kernel index
    sizeof(cl_mem), //arg size
    &other_data //arg value
  );

  //error checking
  cl_check_result(err, "clSetKernelArg");

}

void openCl_instance::enqueue_kernel_scale(const uint32_t size) {
  //Program execution
  //===============================================================================================================================================================================================================
  //===============================================================================================================================================================================================================
  //Execute the kernel over the entire range of teh 1d input data set
  size_t global = size;
  err = clEnqueueNDRangeKernel(
    command_queue,
    kernel,
    1, //number of dimensions
    NULL, //reserved for future versions
    &global, //global work size
    NULL, //not sure if should be NULL - local work size
    0, //number of events
    NULL, //list of events
    NULL //event object to return on completion
  );

  cl_check_result(err, "clEnqueueNDRangeKernel");



}

void openCl_instance::read_from_buffers_scale(float* output, const uint32_t size) {
  //reading data back
  //===============================================================================================================================================================================================================

  err = clEnqueueReadBuffer(
    command_queue,
    output_data, //memory buffer to read from
    CL_TRUE, //true for blocking write -- not returned immediately
    0, //offset in teh buffer object to read from
    sizeof(float) * size, //size in bytes of data being read
    output, //pointer to buffer in host memory to store data
    0, //number of events
    NULL, //list of events that need to be completed first
    NULL //event object to return on completion
  );

  cl_check_result(err, "clEnqueueReadBuffer");


}

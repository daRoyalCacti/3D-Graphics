#include "openCl_instance.h"
#include "error_checking.h"
#include <iostream>
#include <string>
#include <cmath>
#include <chrono>

#define timing


void openCl_instance::query_platform() {
  //query for 1 openCl platform
  //===============================================================================================================================================================================================================
  err = clGetPlatformIDs( //used to retrieve a list of available platforms
    platform_entries, //num_entries : the number of platform entries (will be added to platform)
    &platform_id, //*platform : sets var to a list of found openCl platforms
    &num_platforms //*num_platforms : the number of platforms available
  );
  //clGetPlatformInfo(..) can be used to get information about the platform : see https://www.khronos.org/registry/OpenCL/sdk/1.0/docs/man/xhtml/clGetPlatformInfo.html

  //error checking
  cl_check_result(err, "clGetPlatformIDs");
}

void openCl_instance::query_device() {
  //query for 1 GPU compute device
  //===============================================================================================================================================================================================================

  err = clGetDeviceIDs( //used to search for compute devices
    platform_id,
    device_type, //the device type to search for
    device_entries, //num_entries : the number of devices to search for (in essence - is likely more complicated than that)
    &device_id, //*devices : the list of device ids
    &num_of_devices //*num_devices : the number of OpenCl devices for the given type found
  );
  //clGetDeviceInfo(..) can be used to find the capabilities for the found device -- very similar to clinfo in the shell

  cl_check_result(err, "clGetDeviceIDs");

}

void openCl_instance::create_context() {
  //create a context
  //contexts are used by openCl to manage command queues, program objects, kernel objects, and the sharing of memory objects
  //===============================================================================================================================================================================================================
  properties[0] = CL_CONTEXT_PLATFORM; //as by specification
  properties[1] = (cl_context_properties)platform_id; //as by specification -- cannot static_cast
  properties[2] = 0; //properties list must be terminated with a 0

  context = clCreateContext( //is quite slow
    properties,
    device_entries, //num_devices : number of devices in the device_id list - this was specified during the finding for devices
    &device_id, //*devices : the device id list
    NULL, //*pfn_notify : pointer to an error callback function
    NULL, //*user_data : argument to passs to the callback functin
    &err
  );

  cl_check_result(err, "clCreateContext");

}

void openCl_instance::create_command_queue() {
  //create a command queue
  //command queues allow commands to be sent to compute devices associated with a specified context
  //===============================================================================================================================================================================================================
  const cl_command_queue_properties command_queue_properties[] = {0}; //commented bello has details
  /*const cl_command_queue_properties command_queue_properties[] = {
    CL_QUEUE_PROPERTIES,
    CL_QUEUE_ON_DEVICE | CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE, //bit field values of CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE, CL_QUEUE_PROFILING_ENABLE, CL_QUEUE_ON_DEVICE, CL_QUEUE_ON_DEVICE_DEFAULT
    CL_QUEUE_SIZE, //size of the device queue in bytes
    CL_DEVICE_QUEUE_ON_DEVICE_PREFERRED_SIZE, // is default - should always be less than this value but must be less than CL_DEVICE_QUEUE_ON_DEVICE_MAX_SIZE
    0 //must be terminated with a 0
  };*/

  command_queue = clCreateCommandQueueWithProperties( //for earlier versions of opencl clCreateCommandQueue needs to be used
    context,
    device_id,
    command_queue_properties, //properties for the queue
    &err
  );


  if (err != CL_SUCCESS) { //specification says the err should be NULL if no errors but this seems to work
    std::cerr << "Failed to create command queue" << std::endl;
    if (err == CL_INVALID_CONTEXT) {
      std::cerr << "\tThe specified context is not valid" << std::endl;
    } else if (err == CL_INVALID_DEVICE) {
      std::cerr << "\tThe specified device is not valid" << std::endl;
    } else if (err == CL_INVALID_VALUE) {
      std::cerr << "\tThe values set in properties is not valid" << std::endl;
    } else if (err == CL_INVALID_QUEUE_PROPERTIES) {
      std::cerr << "\tThe queue properties are not supported by this device" << std::endl;
    } else if (err == CL_OUT_OF_RESOURCES) {
      std::cerr << "\tFailed to allocate resources on device" << std::endl;
    } else if (err == CL_OUT_OF_HOST_MEMORY) {
      std::cerr << "\tFailed to allocate resources on the host" << std::endl;
    }
    exit(EXIT_FAILURE);
  }
}



void openCl_instance::cleanup() {
  //clean up
  //===============================================================================================================================================================================================================
  clReleaseMemObject(input_data);
  clReleaseMemObject(output_data);
  clReleaseProgram(program);
  clReleaseKernel(kernel);
  clReleaseCommandQueue(command_queue);
  clReleaseContext(context);

}


void openCl_instance::init() {
  #ifdef timing
  	auto start1 = std::chrono::high_resolution_clock::now();
  #endif
  query_platform();
  #ifdef timing
  	auto end1 = std::chrono::high_resolution_clock::now();
  	std::cout << "Platform querying took \t\t\t" << std::chrono::duration <double, std::milli>(end1 - start1).count() << "ms" << std::endl;
  	auto start2 = std::chrono::high_resolution_clock::now();
  #endif
  query_device();
  #ifdef timing
  	auto end2 = std::chrono::high_resolution_clock::now();
  	std::cout << "Device querying took \t\t\t" << std::chrono::duration <double, std::milli>(end2 - start2).count() << "ms" << std::endl;
  	auto start3 = std::chrono::high_resolution_clock::now();
  #endif
  create_context();
  #ifdef timing
  	auto end3 = std::chrono::high_resolution_clock::now();
  	std::cout << "Context creation took \t\t\t" << std::chrono::duration <double, std::milli>(end3 - start3).count() << "ms" << std::endl;
  	auto start4 = std::chrono::high_resolution_clock::now();
  #endif
  create_command_queue();
  #ifdef timing
  	auto end4 = std::chrono::high_resolution_clock::now();
  	std::cout << "Command queue creation took \t\t" << std::chrono::duration <double, std::milli>(end4 - start4).count() << "ms" << std::endl;
  #endif
}

void openCl_instance::square(float* input, float* output, const uint32_t size) {
  #ifdef timing
    auto start5 = std::chrono::high_resolution_clock::now();
  #endif
  create_program_object_square();
  #ifdef timing
    auto end5 = std::chrono::high_resolution_clock::now();
    std::cout << "Program creation took \t\t\t" << std::chrono::duration <double, std::milli>(end5 - start5).count() << "ms" << std::endl;
    auto start6 = std::chrono::high_resolution_clock::now();
  #endif
  build_program_square();
  #ifdef timing
    auto end6 = std::chrono::high_resolution_clock::now();
    std::cout << "Program building took \t\t\t" << std::chrono::duration <double, std::milli>(end6 - start6).count() << "ms" << std::endl;
    auto start7 = std::chrono::high_resolution_clock::now();
  #endif
  create_kernel_objects_square();
  #ifdef timing
    auto end7 = std::chrono::high_resolution_clock::now();
    std::cout << "Kernel creation took \t\t\t" << std::chrono::duration <double, std::milli>(end7 - start7).count() << "ms" << std::endl;
    auto start8 = std::chrono::high_resolution_clock::now();
  #endif
  create_buffers_square(size);
  #ifdef timing
    auto end8 = std::chrono::high_resolution_clock::now();
    std::cout << "Buffer creation took \t\t\t" << std::chrono::duration <double, std::milli>(end8 - start8).count() << "ms" << std::endl;
    auto start9 = std::chrono::high_resolution_clock::now();
  #endif
  write_to_buffers_square(input, size);
  #ifdef timing
    auto end9 = std::chrono::high_resolution_clock::now();
    std::cout << "Buffer writing took \t\t\t" << std::chrono::duration <double, std::milli>(end9 - start9).count() << "ms" << std::endl;
    auto start10 = std::chrono::high_resolution_clock::now();
  #endif
  set_kernel_arguments_square();
  #ifdef timing
    auto end10 = std::chrono::high_resolution_clock::now();
    std::cout << "Kernel argument setting took \t\t" << std::chrono::duration <double, std::milli>(end10 - start10).count() << "ms" << std::endl;
    auto start11 = std::chrono::high_resolution_clock::now();
  #endif
  enqueue_kernel_square(size);
  #ifdef timing
    auto end11 = std::chrono::high_resolution_clock::now();
    std::cout << "Kernel enqueueing took \t\t\t" << std::chrono::duration <double, std::milli>(end11 - start11).count() << "ms" << std::endl;
    auto start12 = std::chrono::high_resolution_clock::now();
  #endif
  err = clFinish(command_queue); //wait for commands to be serviced before reading results
  cl_check_result(err, "clFinish");
  #ifdef timing
    auto end12 = std::chrono::high_resolution_clock::now();
    std::cout << "Time waiting \t\t\t\t" << std::chrono::duration <double, std::milli>(end12 - start12).count() << "ms" << std::endl;
    auto start13 = std::chrono::high_resolution_clock::now();
  #endif
  read_from_buffers_square(output, size);
  #ifdef timing
    auto end13 = std::chrono::high_resolution_clock::now();
    std::cout << "Buffer reading took \t\t\t" << std::chrono::duration <double, std::milli>(end13 - start13).count() << "ms" << std::endl;
  #endif
}

void openCl_instance::scale(float* input, float* output, float* scale, const uint32_t size) {
  #ifdef timing
    auto start5 = std::chrono::high_resolution_clock::now();
  #endif
  create_program_object_scale();
  #ifdef timing
    auto end5 = std::chrono::high_resolution_clock::now();
    std::cout << "Program creation took \t\t\t" << std::chrono::duration <double, std::milli>(end5 - start5).count() << "ms" << std::endl;
    auto start6 = std::chrono::high_resolution_clock::now();
  #endif
  build_program_scale();
  #ifdef timing
    auto end6 = std::chrono::high_resolution_clock::now();
    std::cout << "Program building took \t\t\t" << std::chrono::duration <double, std::milli>(end6 - start6).count() << "ms" << std::endl;
    auto start7 = std::chrono::high_resolution_clock::now();
  #endif
  create_kernel_objects_scale();
  #ifdef timing
    auto end7 = std::chrono::high_resolution_clock::now();
    std::cout << "Kernel creation took \t\t\t" << std::chrono::duration <double, std::milli>(end7 - start7).count() << "ms" << std::endl;
    auto start8 = std::chrono::high_resolution_clock::now();
  #endif
  create_buffers_scale(size);
  #ifdef timing
    auto end8 = std::chrono::high_resolution_clock::now();
    std::cout << "Buffer creation took \t\t\t" << std::chrono::duration <double, std::milli>(end8 - start8).count() << "ms" << std::endl;
    auto start9 = std::chrono::high_resolution_clock::now();
  #endif
  write_to_buffers_scale(input, scale, size);
  #ifdef timing
    auto end9 = std::chrono::high_resolution_clock::now();
    std::cout << "Buffer writing took \t\t\t" << std::chrono::duration <double, std::milli>(end9 - start9).count() << "ms" << std::endl;
    auto start10 = std::chrono::high_resolution_clock::now();
  #endif
  set_kernel_arguments_scale();
  #ifdef timing
    auto end10 = std::chrono::high_resolution_clock::now();
    std::cout << "Kernel argument setting took \t\t" << std::chrono::duration <double, std::milli>(end10 - start10).count() << "ms" << std::endl;
    auto start11 = std::chrono::high_resolution_clock::now();
  #endif
  enqueue_kernel_scale(size);
  #ifdef timing
    auto end11 = std::chrono::high_resolution_clock::now();
    std::cout << "Kernel enqueueing took \t\t\t" << std::chrono::duration <double, std::milli>(end11 - start11).count() << "ms" << std::endl;
    auto start12 = std::chrono::high_resolution_clock::now();
  #endif
  err = clFinish(command_queue); //wait for commands to be serviced before reading results
  cl_check_result(err, "clFinish");
  #ifdef timing
    auto end12 = std::chrono::high_resolution_clock::now();
    std::cout << "Time waiting \t\t\t\t" << std::chrono::duration <double, std::milli>(end12 - start12).count() << "ms" << std::endl;
    auto start13 = std::chrono::high_resolution_clock::now();
  #endif
  read_from_buffers_scale(output, size);
  #ifdef timing
    auto end13 = std::chrono::high_resolution_clock::now();
    std::cout << "Buffer reading took \t\t\t" << std::chrono::duration <double, std::milli>(end13 - start13).count() << "ms" << std::endl;
  #endif
}

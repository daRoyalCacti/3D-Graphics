#include "openCl_instance.h"
#include <iostream>
#include <sstream>
#include <fstream>


void openCl_instance::create_program_object_square() {
  //creating the program object
  //a program is a collection of kernel functions -- kernel functions are what execute on device
  //===============================================================================================================================================================================================================
  //===============================================================================================================================================================================================================

  //reading in the program code as strings
  std::string programCode;
  std::ifstream programFile;

  try {
    programFile.open(programPath);
    std::stringstream programStream;
    programStream << programFile.rdbuf();
    programFile.close();
    programCode = programStream.str();
  }
  catch (std::ifstream::failure e) {
    std::cerr << "Program file could not be read at " << programPath << std::endl;
  }

  const char* ProgramSource = programCode.c_str();

  program = clCreateProgramWithSource(
    context,
    1, //the number of strings in the next parameter
    (const char**) &ProgramSource, //the array of strings
    NULL, //the length of each string -- can be NULL terminated
    &err
  );

  if (err != CL_SUCCESS) {
    std::cerr << "Failed create program from source" << std::endl;
    if (err == CL_INVALID_CONTEXT) {
      std::cerr << "\tThe specified context is invalid" << std::endl;
    } else if (err == CL_INVALID_VALUE) {
      std::cerr << "\tCount is 0 or any entry in strings in NULL" << std::endl;
    } else if (err == CL_OUT_OF_HOST_MEMORY) {
      std::cerr << "\tFailed to allocate resources on the host" << std::endl;
    }
    exit(EXIT_FAILURE);
  }
  //Building program executables
  //compiling and linking the program object
  //===============================================================================================================================================================================================================
  err = clBuildProgram(
    program,
    0,    //number of devices in device lish
    NULL, //device list -- NULL means all devices
    NULL, //a string of build options -- too many to state here
    NULL, //callback function
    NULL  //data arguments for callback function
  );

  //error checking
  if (err != CL_SUCCESS) {
    std::cerr << "Failed to build program executables" << std::endl;
    if (err == CL_INVALID_PROGRAM) {
      std::cerr << "\tThe program is not a valid program" << std::endl;
    } else if (err == CL_INVALID_VALUE) {
      std::cerr << "\tThere is a problem with some of the specifed values" << std::endl;
    } else if (err == CL_INVALID_DEVICE) {
      std::cerr << "\tThe devices specifed are not associated with the devices in the program" << std::endl;
    } else if (err == CL_INVALID_BINARY) {
      std::cerr << "\tThere is valid program binary loaded" << std::endl;
    } else if (err == CL_INVALID_BUILD_OPTIONS) {
      std::cerr << "\tThe build options are invalid" << std::endl;
    } else if (err == CL_INVALID_OPERATION) {
      std::cerr << "\tA previous call to clBuildProgram for the current program has not been completed" << std::endl;
    } else if (err == CL_COMPILER_NOT_AVAILABLE) {
      std::cerr << "\tA compiler is not available" << std::endl;
    } else if (err == CL_BUILD_PROGRAM_FAILURE) {
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

      if (err != CL_SUCCESS) {
        std::cerr << "Failed to get build info" << std::endl;
        if (err == CL_INVALID_DEVICE) {
          std::cerr << "\tThe device specified is not associated with the program" << std::endl;
        } else if (err == CL_INVALID_VALUE) {
          std::cerr << "\tError with some specified values" << std::endl;
        } else if (err == CL_INVALID_PROGRAM) {
          std::cerr << "\tProgram specifed is not a valid program" << std::endl;
        }
      }

      std::cout << "\nBuild Log:" << std::endl;
      std::printf("%s\n", buffer);

    } else if (err == CL_INVALID_OPERATION) {
      std::cerr << "\tThere are kernel objects attached to the program" << std::endl;
    } else if (err == CL_OUT_OF_HOST_MEMORY) {
      std::cerr << "\tFailed to allocate resources on the host" << std::endl;
    }
    exit(EXIT_FAILURE);
  }

}

void openCl_instance::build_program_square() {
  //Building program executables
  //compiling and linking the program object
  //===============================================================================================================================================================================================================
  err = clBuildProgram(
    program,
    0,    //number of devices in device lish
    NULL, //device list -- NULL means all devices
    NULL, //a string of build options -- too many to state here
    NULL, //callback function
    NULL  //data arguments for callback function
  );

  //error checking
  if (err != CL_SUCCESS) {
    std::cerr << "Failed to build program executables" << std::endl;
    if (err == CL_INVALID_PROGRAM) {
      std::cerr << "\tThe program is not a valid program" << std::endl;
    } else if (err == CL_INVALID_VALUE) {
      std::cerr << "\tThere is a problem with some of the specifed values" << std::endl;
    } else if (err == CL_INVALID_DEVICE) {
      std::cerr << "\tThe devices specifed are not associated with the devices in the program" << std::endl;
    } else if (err == CL_INVALID_BINARY) {
      std::cerr << "\tThere is valid program binary loaded" << std::endl;
    } else if (err == CL_INVALID_BUILD_OPTIONS) {
      std::cerr << "\tThe build options are invalid" << std::endl;
    } else if (err == CL_INVALID_OPERATION) {
      std::cerr << "\tA previous call to clBuildProgram for the current program has not been completed" << std::endl;
    } else if (err == CL_COMPILER_NOT_AVAILABLE) {
      std::cerr << "\tA compiler is not available" << std::endl;
    } else if (err == CL_BUILD_PROGRAM_FAILURE) {
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

      if (err != CL_SUCCESS) {
        std::cerr << "Failed to get build info" << std::endl;
        if (err == CL_INVALID_DEVICE) {
          std::cerr << "\tThe device specified is not associated with the program" << std::endl;
        } else if (err == CL_INVALID_VALUE) {
          std::cerr << "\tError with some specified values" << std::endl;
        } else if (err == CL_INVALID_PROGRAM) {
          std::cerr << "\tProgram specifed is not a valid program" << std::endl;
        }
      }

      std::cout << "\nBuild Log:" << std::endl;
      std::printf("%s\n", buffer);

    } else if (err == CL_INVALID_OPERATION) {
      std::cerr << "\tThere are kernel objects attached to the program" << std::endl;
    } else if (err == CL_OUT_OF_HOST_MEMORY) {
      std::cerr << "\tFailed to allocate resources on the host" << std::endl;
    }
    exit(EXIT_FAILURE);
  }

}

void openCl_instance::create_kernel_objects_square() {
  //creating kernel objects
  //kernel objects are an encapsulation of a __kernel function
  //===============================================================================================================================================================================================================

  kernel = clCreateKernel(
    program,
    "square", //the name of kernel
    &err
  );

  //error checking
  if (err != CL_SUCCESS) {
    std::cerr << "Failed to create kernel" << std::endl;
    if (err == CL_INVALID_PROGRAM) {
      std::cerr << "The program specifed is not a valid program object" << std::endl;
    } else if (err == CL_INVALID_PROGRAM_EXECUTABLE) {
      std::cerr << "There is not successfully built executable for the specifed program" << std::endl;
    } else if (err == CL_INVALID_KERNEL_NAME) {
      std::cerr << "The kernel name is not found" << std::endl;
    } else if (err == CL_INVALID_KERNEL_DEFINITION) {
      std::cerr << "Kernel defintion is invalid" << std::endl; //don't really understand -- see specification
    } else if (err == CL_INVALID_VALUE) {
      std::cerr << "Kernel name cannot be NULL" << std::endl;
    } else if (err == CL_OUT_OF_HOST_MEMORY) {
      std::cerr << "Failed to allocate resources on the host" << std::endl;
    }

    exit(EXIT_FAILURE);
  }

}

void openCl_instance::create_buffers_square(const uint32_t size) {
  //Creating Buffers
  //===============================================================================================================================================================================================================
  input_data = clCreateBuffer(
    context,
    CL_MEM_READ_ONLY, //bit field used to specify the usage of memory -- possibilities are CL_MEM_READ_WRITE, CL_MEM_WRITE_ONLY, CL_MEM_READ_ONLY, CL_MEM_USE_HOST_PTR, CL_MEM_ALLOC_HOST_PTR, CL_MEM_COPY_HOST_PTR
    sizeof(float) * size,  //size in bytes of teh buffer to allocate
    NULL, //pointer to buffer data
    &err
  );

  if (err != CL_SUCCESS) {
    std::cerr << "Failed to allocate device memory" << std::endl;
    if (err == CL_INVALID_CONTEXT) {
      std::cerr << "\tThe context specifed is not a valid context" << std::endl;
    } else if (err == CL_INVALID_VALUE) {
      std::cerr << "\tThe flags used to specify the usage of memory are not valid" << std::endl;
    } else if (err == CL_INVALID_BUFFER_SIZE) {
      std::cerr << "\tThe buffer size is 0\n\tor the buffer size is greater than CL_DEVICE_MAX_MEM_ALLOC_SIZE value specified in the table from clGetDeviceInfo" << std::endl;
    } else if (err == CL_INVALID_HOST_PTR) {
      std::cerr << "\tThere is a problem with the pointer to the data on host" << std::endl; //all cases are too long to type here -- see specification
    } else if (err == CL_MEM_OBJECT_ALLOCATION_FAILURE) {
      std::cerr << "\tFailed to allocate memory for the buffer object" << std::endl;
    } else if (err == CL_OUT_OF_HOST_MEMORY) {
      std::cerr << "\tFailed to allocate resources on the host" << std::endl;
    }

    exit(EXIT_FAILURE);
  }

  output_data = clCreateBuffer(
    context,
    CL_MEM_WRITE_ONLY, //bit field used to specify the usage of memory -- possibilities are CL_MEM_READ_WRITE, CL_MEM_WRITE_ONLY, CL_MEM_READ_ONLY, CL_MEM_USE_HOST_PTR, CL_MEM_ALLOC_HOST_PTR, CL_MEM_COPY_HOST_PTR
    sizeof(float) * size, //size in bytes of teh buffer to allocate
    NULL, //pointer to buffer data
    &err
  );

  if (err != CL_SUCCESS) {
    std::cerr << "Failed to allocate device memory" << std::endl;
    if (err == CL_INVALID_CONTEXT) {
      std::cerr << "\tThe context specifed is not a valid context" << std::endl;
    } else if (err == CL_INVALID_VALUE) {
      std::cerr << "\tThe flags used to specify the usage of memory are not valid" << std::endl;
    } else if (err == CL_INVALID_BUFFER_SIZE) {
      std::cerr << "\tThe buffer size is 0\n\tor the buffer size is greater than CL_DEVICE_MAX_MEM_ALLOC_SIZE value specified in the table from clGetDeviceInfo" << std::endl;
    } else if (err == CL_INVALID_HOST_PTR) {
      std::cerr << "\tThere is a problem with the pointer to the data on host" << std::endl; //all cases are too long to type here -- see specification
    } else if (err == CL_MEM_OBJECT_ALLOCATION_FAILURE) {
      std::cerr << "\tFailed to allocate memory for the buffer object" << std::endl;
    } else if (err == CL_OUT_OF_HOST_MEMORY) {
      std::cerr << "\tFailed to allocate resources on the host" << std::endl;
    }

    exit(EXIT_FAILURE);
  }
}

void openCl_instance::write_to_buffers_square(float* input, const uint32_t size) {
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

  if (err != CL_SUCCESS) {
    std::cerr << "Failed to write to buffer" << std::endl;
    if (err == CL_INVALID_COMMAND_QUEUE) {
      std::cerr << "\tThe command queue specified is not a valid command queue" << std::endl;
    } else if (err == CL_INVALID_CONTEXT) {
      std::cerr << "\tThe context associated with command queue and buffer are not the same\n\tor the context associated with the command queue and event wait list are not the same" << std::endl;
    } else if (err == CL_INVALID_MEM_OBJECT) {
      std::cerr << "\tThe specified buffer is not a valid buffer object" << std::endl;
    } else if (err == CL_INVALID_VALUE) {
      std::cerr << "\tThe region being written is out of bounds\n\tor if the data pointer is NULL" << std::endl;
    } else if (err == CL_INVALID_EVENT_WAIT_LIST) {
      std::cerr << "\tThere is a problem with the event wait list or the number of events" << std::endl; //too many cases to write here
    } else if (err == CL_MEM_OBJECT_ALLOCATION_FAILURE) {
      std::cerr << "\tFailed to allocate memory for data store with the specified buffer" << std::endl;
    } else if (err == CL_OUT_OF_HOST_MEMORY) {
      std::cerr << "\tFailed to allocate resources on the host" << std::endl;
    }

    exit(EXIT_FAILURE);
  }
}

void openCl_instance::set_kernel_arguments_square() {
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
  if (err != CL_SUCCESS) {
    std::cerr << "Failed to set kernel Arg" << std::endl;
    if (err == CL_INVALID_KERNEL) {
      std::cerr << "\tThe kernel specifed is not a valid kernel object" << std::endl;
    } else if (err == CL_INVALID_ARG_INDEX) {
      std::cerr << "\tThe argument index sepcified is not a valid index" << std::endl;
    } else if (err == CL_INVALID_ARG_VALUE) {
      std::cerr << "\tArgument value cannot be NULL for an argument not declared with __local" << std::endl;
    } else if (err == CL_INVALID_MEM_OBJECT) {
      std::cerr << "\tArgument declared as a memory object does not have an argument value that is a memory object" << std::endl; //don't understand
    } else if (err == CL_INVALID_SAMPLER) {
      std::cerr << "\tArgument declared as sampler_t does not have an argument value that is sampler_t" << std::endl;
    } else if (err == CL_INVALID_ARG_SIZE) {
      std::cerr << "\tArgument size does not match the size of the data type\n\tor the argument is a memory object and arguments size is not the size of cl_mem\n\tor argument size is 0 and the argument is declared with __local\n\tor the argument is a sampler and argument size is size of cl_sampler" << std::endl;
    }
  }

  //setting values for argument 1
  err = clSetKernelArg(
    kernel,
    1,  //kernel index
    sizeof(cl_mem), //arg size
    &output_data //arg value
  );

  //error checking
  if (err != CL_SUCCESS) {
    std::cerr << "Failed to set kernel Arg" << std::endl;
    if (err == CL_INVALID_KERNEL) {
      std::cerr << "\tThe kernel specifed is not a valid kernel object" << std::endl;
    } else if (err == CL_INVALID_ARG_INDEX) {
      std::cerr << "\tThe argument index sepcified is not a valid index" << std::endl;
    } else if (err == CL_INVALID_ARG_VALUE) {
      std::cerr << "\tArgument value cannot be NULL for an argument not declared with __local" << std::endl;
    } else if (err == CL_INVALID_MEM_OBJECT) {
      std::cerr << "\tArgument declared as a memory object does not have an argument value that is a memory object" << std::endl; //don't understand
    } else if (err == CL_INVALID_SAMPLER) {
      std::cerr << "\tArgument declared as sampler_t does not have an argument value that is sampler_t" << std::endl;
    } else if (err == CL_INVALID_ARG_SIZE) {
      std::cerr << "\tArgument size does not match the size of the data type\n\tor the argument is a memory object and arguments size is not the size of cl_mem\n\tor argument size is 0 and the argument is declared with __local\n\tor the argument is a sampler and argument size is size of cl_sampler" << std::endl;
    }
    exit(EXIT_FAILURE);
  }
  //clGetKernelInfo(..) can be used to query information about the kernel object

}

void openCl_instance::enqueue_kernel_square(const uint32_t size) {
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

  if (err != CL_SUCCESS) {
    std::cerr << "Failed to enqueue the kernel" << std::endl;
    if (err == CL_INVALID_PROGRAM_EXECUTABLE) {
      std::cerr << "\tThere is no successfully built exectable available for the device associated with the command_queue" << std::endl;
    } else if (err == CL_INVALID_COMMAND_QUEUE) {
      std::cerr << "\tThe specifed command queue is not a valid command queue" << std::endl;
    } else if (err == CL_INVALID_KERNEL) {
      std::cerr << "\tThe specifed kernel is not a valid kernel object" << std::endl;
    } else if (err == CL_INVALID_CONTEXT) {
      std::cerr << "\tThe context associated with the command queue is not the same as the context associated with the kernel\n\tor the context associated with the command queue is not the same as the context associated with the events" << std::endl;
    } else if (err == CL_INVALID_KERNEL_ARGS) {
      std::cerr << "\tThe kernel argument values have not been specifed" << std::endl;
    } else if (err == CL_INVALID_WORK_DIMENSION) {
      std::cerr << "\tThe work dimension must be an integer between 1 and 3 inclusive" << std::endl;
    } else if (err == CL_INVALID_WORK_GROUP_SIZE) {
      std::cerr << "\tThe local work size does not divide the global work size\n\tor the global work size does not match the work group size specifed for the kernel using __attribute__ in the program source\n\tor the multiplication of the local work sizes for each dimension is greater than the value specifed by CL_DEVICE_MAX_WORK_GROUP_SIZE in the table returned by clGetDeviceInfo\n\tor if the local work size is NULL and __attribute__ is used to declare the work group size in program source" << std::endl; //specification has 3 seperate errors all with the same value
    } else if (err == CL_INVALID_WORK_ITEM_SIZE) {
      std::cerr << "\tThe number of work items specified in any dimension of the local work size is greater than the corresponding values specified by CL_DEVICE_MAX_WORK_ITEM_SIZES[dimension]" << std::endl;
    } else if (err == CL_INVALID_GLOBAL_OFFSET) {
      std::cerr << "\tGlobal offset must be set to NULL" << std::endl;
    } else if (err == CL_OUT_OF_RESOURCES) {
      std::cerr << "\tFailed to queue the execution of kernel on the command queue becuase of insufficient resources needed to execute the kernel" << std::endl; //spec has examples for how this can happen
    } else if (err == CL_MEM_OBJECT_ALLOCATION_FAILURE) {
      std::cerr << "\tFailed to allocate memory for data store associated with image or buffer objects specifed as arguments to the kernel" << std::endl;
    } else if (err == CL_INVALID_EVENT_WAIT_LIST) {
      std::cerr << "\tEvent wait list is NULL but the number of events specified for the wait list is greater than 0\n\tor event wait list is not NULL but the number of events specified for the wait list is 0\n\tor the event objects in the event wait list are not valid events" << std::endl;
    } else if (err == CL_OUT_OF_HOST_MEMORY) {
      std::cerr << "\tFailed to allocate resources on the host" << std::endl;
    }

    exit(EXIT_FAILURE);
  }

}

void openCl_instance::read_from_buffers_square(float* output, const uint32_t size) {
  //reading data back
  //===============================================================================================================================================================================================================

  if (err != CL_SUCCESS) {
    std::cerr << "Failed to wait for command queue" << std::endl;
    if (err == 	CL_INVALID_COMMAND_QUEUE) {
      std::cerr << "\tThe command queue specified is not a valid command queue" << std::endl;
    } else if (err == CL_OUT_OF_HOST_MEMORY) {
      std::cerr << "\tFailed to allocate resources on the host" << std::endl;
    }

    exit(EXIT_FAILURE);
  }

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

  if (err != CL_SUCCESS) {
    std::cerr << "Failed to read buffer" << std::endl;
    if (err == CL_INVALID_COMMAND_QUEUE) {
      std::cerr << "\tThe command queue specified is not a valid command queue" << std::endl;
    } else if (err == CL_INVALID_CONTEXT) {
      std::cerr << "\tThe context associated with command queue and buffer are not the same\n\tor the context associated with the command queue and event wait list are not the same" << std::endl;
    } else if (err == CL_INVALID_MEM_OBJECT) {
      std::cerr << "\tThe specified buffer is not a valid buffer object" << std::endl;
    } else if (err == CL_INVALID_VALUE) {
      std::cerr << "\tThe region being written is out of bounds\n\tor if the data pointer is NULL" << std::endl;
    } else if (err == CL_INVALID_EVENT_WAIT_LIST) {
      std::cerr << "\tThere is a problem with the event wait list or the number of events" << std::endl; //too many cases to write here
    } else if (err == CL_MEM_OBJECT_ALLOCATION_FAILURE) {
      std::cerr << "\tFailed to allocate memory for data store with the specified buffer" << std::endl;
    } else if (err == CL_OUT_OF_HOST_MEMORY) {
      std::cerr << "\tFailed to allocate resources on the host" << std::endl;
    }

    exit(EXIT_FAILURE);
  }
}

#include "error_checking.h"
#include <iostream>

//false == error, true == success
void cl_check_result(cl_int err, const std::string function) {
  if (function == "clGetPlatformIDs") {
    if (err != CL_SUCCESS) { //there was some error
      std::cerr << "Failed to get platform ids" << std::endl;
      if (err == CL_INVALID_VALUE) {
        std::cerr << "\tThe platforms and number of platforms are null or the number of entries is 0" << std::endl;
      } else if (err == -1001) {
        std::cerr << "\tThis could be because the ICD could not be found or some other issue with the development environment" << std::endl;
      }
      exit(EXIT_FAILURE);
    }


  } else if (function == "clGetDeviceIDs") {
    if (err != CL_SUCCESS) {
      std::cerr << "Failed to get device ids" << std::endl;
      if (err == CL_INVALID_PLATFORM) {
        std::cerr << "\tThe platform id entered is not for a valid platform" << std::endl;
      } else if (err == CL_INVALID_DEVICE_TYPE) {
        std::cerr << "\tThe device type entered is not a valid type of openCl device" << std::endl;
      } else if (err == CL_INVALID_VALUE) {
        std::cerr << "\tThere is an issue with the values for the number of entries and the device type" << std::endl;
      } else if (err == CL_DEVICE_NOT_FOUND) {
        std::cerr << "\tNo OpenCl devices were found of the specified device type" << std::endl;
      }
      exit(EXIT_FAILURE);
    }



  } else if (function == "clCreateContext") {
    if (err != CL_SUCCESS) {
      std::cerr << "Failed to create context" << std::endl;
      if (err == CL_INVALID_PLATFORM) {
        std::cerr << "\tThere is a problem with the properties\n\tor the platfrom specified is not valid" << std::endl;
      } else if (err == CL_INVALID_VALUE) {
        std::cerr << "\tThere is a problem with some of the set values" << std::endl;
      } else if (err == CL_INVALID_DEVICE) {
        std::cerr << "\tThe device is invalid or the device is not associated with the specified platform" << std::endl;
      } else if (err == CL_DEVICE_NOT_AVAILABLE) {
        std::cerr << "\tDevice is not available but is a valid device" << std::endl;
      } else if (err == CL_OUT_OF_HOST_MEMORY) {
        std::cerr << "\tFailed to allocate resources on the host" << std::endl;
      }
      exit(EXIT_FAILURE);
    }




  } else if (function == "clCreateProgramWithSource") {
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


  } else if (function == "clBuildProgram") {
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
        std::cerr << "\tor there are kernel objects attached to the program" << std::endl;
      } else if (err == CL_COMPILER_NOT_AVAILABLE) {
        std::cerr << "\tA compiler is not available" << std::endl;
      } else if (err == CL_OUT_OF_HOST_MEMORY) {
        std::cerr << "\tFailed to allocate resources on the host" << std::endl;
      }
      exit(EXIT_FAILURE);
    }



    } else if (function == "clGetProgramBuildInfo") {
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
      exit(EXIT_FAILURE);




    } else if (function == "clCreateKernel") {
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




    } else if (function == "clCreateBuffer") {
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




    } else if (function == "clEnqueueWriteBuffer") {
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




    } else if (function == "clSetKernelArg") {
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



    } else if (function == "clEnqueueNDRangeKernel") {
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




    } else if (function == "clFinish") {
      if (err != CL_SUCCESS) {
        std::cerr << "Failed to wait for command queue" << std::endl;
        if (err == 	CL_INVALID_COMMAND_QUEUE) {
          std::cerr << "\tThe command queue specified is not a valid command queue" << std::endl;
        } else if (err == CL_OUT_OF_HOST_MEMORY) {
          std::cerr << "\tFailed to allocate resources on the host" << std::endl;
        }

        exit(EXIT_FAILURE);
      }


    } else if (function == "clEnqueueReadBuffer") {
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







}

#include <thread>							//for using threads
#include <iostream>						//for logging errors and logging that the program crashed
#include <chrono>							//for timing
#include "vulkan_instance.h"	//for all vulkan functions
#include "window_inputs.h" 		//for processing keyboard inputs

#ifdef _WIN32
	#include <windows.h> 				//for closing console
#endif

int main() {
#ifdef _WIN32
#ifdef	NODEBUG
	//setting the terminal not to show in release modes on windows
	//it is pointless to try and hide the teminal on linux because most of the time the program is launched through the terminal
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
#endif
#endif

	#ifndef NODEBUG
		std::cout << "\n\n\n\n\n\n\n\n\n\n\n"; //to make the console look neater after compiling lots of files
		//only in debug becasue nothing gets written to the console during release
	#endif

	vulkanApp app;
	try {

		std::thread thread1(&vulkanApp::loadData, &app);			//reading the mesh data from files
		std::thread thread2(&vulkanApp::initWindow, &app);		//creating the window which vulkan will write to
		//the 2 can be exectued in parallel because they share no data
		thread1.join();
		thread2.join();

		app.initVulkan(); 		//initialising vulkan
													//this can not be done in parallel because the surface created by "initWindow" needs to be used for initilising vulkan

		while (!glfwWindowShouldClose(app.window)) {	//keep the loop going until it is decided that the window should close
			#ifdef framerate
				auto start = std::chrono::high_resolution_clock::now();
			#endif
			//there is likely some threading to be done here, but drawFrame is very slow compared to everything else
			glfwPollEvents();													//get keyboard inputs and mouse movements
			processWindowInput(app.window, &camera);	//process these inputs
			app.drawFrame();													//reader the next frame to the window
			app.framecounter++;												//incrementing the framecounter every frame -- framecounter is used to getting frames of meshes and frames of movements
			#ifdef framerate
				auto end = std::chrono::high_resolution_clock::now();
				std::cout << "Framerate " << 1000/std::chrono::duration <float, std::milli>(end - start).count() << " fps" << std::endl;
			#endif
		}

		app.cleanup();			//destroying resources used by vulkan
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;					//logging the error
		std::cout << "\nProgram has crashed!" << std::endl;

		#ifdef _WIN32
			getchar(); //because the windows terminal will automatically close when the program ends, there needs to be a way of keeping it open so the error messagese can be read
		#endif

		return EXIT_FAILURE; //program creashed so of course return failure
	}

	return EXIT_SUCCESS; //program completed normally
}

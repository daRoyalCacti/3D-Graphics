//#include <thread>
#include <iostream>
#include "basicApp.h"
#ifdef _WIN32
#include<windows.h>
#endif

int main() {
#ifdef _WIN32
#ifdef	NODEBUG
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
#endif
#endif

	basicApp app;
	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		std::cout << "\nProgram has crashed!" << std::endl;
	#ifdef _WIN32
		getchar();
	#endif
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

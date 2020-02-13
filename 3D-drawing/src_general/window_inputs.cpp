#include "window_inputs.h"
#include <iostream>
#include "global.h"
#include "vulkan_instance.h"


float currentFrame, lastFrame, delta_time;
bool first_frame_camera = true;
bool last_frame_plus = false;
bool last_frame_minus = false;


void processWindowInput(GLFWwindow *window){

	//could be a better way of doing this
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

#ifdef player_camera
		currentFrame = glfwGetTime();
		if (first_frame_camera) {
			lastFrame = currentFrame;
			first_frame_camera = false;
		}

		delta_time = currentFrame - lastFrame;
		lastFrame = currentFrame;
		global::camera.MovementSpeed = global::camera.targetSpeed * delta_time;


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
      global::camera.move_forward();
		}

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
      global::camera.move_backward();
		}

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
      global::camera.move_right();
		}

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
      global::camera.move_left();
		}

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
      global::camera.move_up();
		}

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
      global::camera.move_down();
		}

#endif

	if (glfwGetKey(window,GLFW_KEY_KP_ADD) == GLFW_PRESS) {
		if (!last_frame_plus) {
			global::framecounter = global::framecounter + 1;
		}
		last_frame_plus = true;
	}

	if (glfwGetKey(window,GLFW_KEY_KP_ADD) == GLFW_RELEASE) {
		last_frame_plus = false;
	}


	if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS) {
		if (!last_frame_minus) {
			uint64_t last_framecounter = global::framecounter;
			global::framecounter = global::framecounter - 1;
			if (global::framecounter > last_framecounter) {	//'-1' will always make a number smaller, so if its bigger then there's been underflow (framecounter is unsigned)
				global::framecounter = 0;
			}
		}
		last_frame_minus = true;
	}

	if (glfwGetKey(window,GLFW_KEY_KP_SUBTRACT) == GLFW_RELEASE) {
		last_frame_minus = false;
	}

	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		global::increase_frames = true;
	}

	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
		global::increase_frames = false;
	}


	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}

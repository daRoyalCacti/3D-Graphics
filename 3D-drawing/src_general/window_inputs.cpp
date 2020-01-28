#include "window_inputs.h"
#include <iostream>
#include "global.h"

void processWindowInput(GLFWwindow *window, playerCamera* camera){

	//could be a better way of doing this
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

#ifdef player_camera
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
      camera->move_forward();
		}

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
      camera->move_backward();
		}

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
      camera->move_right();
		}

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
      camera->move_left();
		}

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
      camera->move_up();
		}

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
      camera->move_down();
		}
#endif
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}

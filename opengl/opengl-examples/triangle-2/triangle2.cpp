/*******************************************************************
 This program shows how to send data from a shader stage to another.
********************************************************************/

#include <iostream>
#include <cstring>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

const int WINDOW_WITDH = 1920;
const int WIDNOW_HEIGHT = 1080;

int main(int argc, char* argv[]) {
	int major = -1;
	int minor = -1;
	int rev = -1;
	/*iniitialization hints*/
	glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, GLFW_TRUE);

	/*Initialize GFLW*/
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW." << std::endl;
		return -1;
	}

	/*Show GLFW info.*/
	std::cout << "GFLW compile time : " << GLFW_VERSION_MAJOR << " " << GLFW_VERSION_MINOR << " " << GLFW_VERSION_REVISION << std::endl;
	glfwGetVersion(&major, &minor, &rev);
	std::cout << "GFLW run time : " << major << " " << minor << " " << rev << std::endl;

	/*window creation hints*/
	glfwDefaultWindowHints();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_NO_ERROR, GLFW_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
	glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
	glfwWindowHint(GLFW_FLOATING, GLFW_FALSE);
	glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);

	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WITDH, WIDNOW_HEIGHT, "Triangle 2", NULL, NULL);
	if (NULL == window) {
		std::cout << "Failed to create a window." << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Load OpenGL context API with glfwGetProcAddress" << std::endl;
	}
	else if (gladLoadGL()) {
		std::cout << "Load OpenGL context API with gladLoadGL" << std::endl;
	}
	else {
		std::cout << "Failed to load OpenGL context API." << std::endl;
		glfwTerminate();
		return -1;
	}

	

	/*compile shaders*/

	/*create a program object*/

	/*load data into shader pipeline.*/

	/*rendering loop*/

	/*teminate GLFW*/
	glfwTerminate();
	return 0;
}
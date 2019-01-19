#include<iostream>

/*
* You must include glad.h before glfw3.h in that glad.h can promise include the correct version of OpenGL header files.
*/
#include<glad/glad.h>
#include<GLFW/glfw3.h>


int main(int argc, char* argv[]) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "An OpenGL Context Window", NULL, NULL);
	if (NULL == window) {
		std::cout << "Failed to create a glfw window." << std::endl;
		glfwTerminate();
	}
	return 0;
}
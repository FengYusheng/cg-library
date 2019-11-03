#include <iostream>
#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaders.h"




int main(int argc, char* argv[]) {
	int major = -1;
	int minor = -1;
	int rev = -1;

	/*Initialization Hints
	* glfwInit()
	*/

	/*Initialize OpenGL context.*/
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW." << std::endl;
		return -1;
	}

	/*GLFW VERSION*/
	std::cout << "GLFW Version: " << glfwGetVersionString() << std::endl;
	glfwGetVersion(&major, &minor, &rev);
	printf("GLFW MAJOR: %d, MINOR: %d, REV: %d\n", major, minor, rev);

	/*Set OpenGL context hints.*/
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	glfwTerminate();

	system("pause");
	return 0;
}
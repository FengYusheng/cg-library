#include <iostream>
#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaders.h"

const int SCR_WIDTH = 1024;
const int SCR_HEIGHT = 768;

void processInput(GLFWwindow*);
void framebuffer_size_cb(GLFWwindow*, int, int);

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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

	/*Set window hints*/
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
	glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
	glfwWindowHint(GLFW_FLOATING, GLFW_FALSE); // turn off "always-on-top"
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello, rectangle", NULL, NULL);
	if (NULL == window) {
		std::cout << "Failed to create the context window." << std::endl;
		glfwTerminate();
		system("pause");
		return -1;
	}

	/*Load OpenGL context fucntion pointer*/

	glfwSetFramebufferSizeCallback(window, framebuffer_size_cb);


	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window) {
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, true);
	}
}

/*https://www.glfw.org/docs/latest/window_guide.html#buffer_swap
* The size of a framebuffer may change independently of the size of a window, 
* for example if the window is dragged between a regular monitor and a high-DPI one.
*/
void framebuffer_size_cb(GLFWwindow* window, int width, int height) {
	//glViewport(0, 0, width, height);
}
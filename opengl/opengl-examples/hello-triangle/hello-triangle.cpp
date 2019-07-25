#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "shaders.h"

// settings
const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 768;

void framebuffer_size_callback(GLFWwindow*, int, int);

int main(int argc, char* argv[])
{
	/**
	* Get your current glfw verion.
	*/
	int major = -1;
	int minor = -1;
	int rev = -1;

	glfwGetVersion(&major, &minor, &rev);
	printf("GLFW version is %d, %d, %d\n", major, minor, rev);

	/*Initialize and configure.*/
	if (!glfwInit())
	{
		std::cout << "glfwInit failed!" << std::endl;
		return -1;
	}

	/*Set hints for window creation.
	*
	* https://www.glfw.org/docs/latest/window_guide.html#window_hints
	*/
	glfwDefaultWindowHints();

	/*Opengl context related hints*/
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/*Framebuffer related buffer*/
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

	/*Window related hints*/

	/*OpenGL context creation*/
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello Triangle", NULL, NULL);
	if (NULL == window)
	{
		std::cout << "GLFW window creation failed!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/* Load OpenGL function pointer to this window's context.
	* https://glad.dav1d.de/
	*/
	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Load OpenGL functions with glfwGetProcesAddress." << std::endl;
		printf("The OpenGL version loaded is %d, %d\n", GLVersion.major, GLVersion.minor);
	}
	else if (gladLoadGL())
	{
		std::cout << "Load OpenGL functions with gladLoadGL." << std::endl;
		printf("The OpenGL version loaded is %d, %d\n", GLVersion.major, GLVersion.minor);
	}
	else
	{
		std::cout << "Failed to load OpenGL functions." << std::endl;
		glfwTerminate();
		return -1;
	}

	/*Get current OpenGL context version with glGetString*/
	printf("The version of current OpenGL context is %s\n", glGetString(GL_VERSION));
	printf("The vendor of current OpenGL context is %s\n", glGetString(GL_VENDOR));
	printf("The renderer of current OpenGL context is %s\n", glGetString(GL_RENDERER));
	printf("Then shading language version of current OpenGL context is %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));



	//system("pause");
	glfwTerminate();
	
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
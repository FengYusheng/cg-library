#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// settings
const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 768;

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

	glfwTerminate();
	
	return 0;
}
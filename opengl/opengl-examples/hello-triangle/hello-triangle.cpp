#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

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
	}

	/*Set hints for window creation.
	*
	* https://www.glfw.org/docs/latest/window_guide.html#window_hints
	*/
	glfwDefaultWindowHints();

	/*Opengl context related hints*/
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);

	/*Window related hints*/

	glfwTerminate();

	system("pause");
	
	return 0;
}
#include<iostream>

/*
* You must include glad.h before glfw3.h in that glad.h can promise include the correct version of OpenGL header files.
*/
#include<glad/glad.h>
#include<GLFW/glfw3.h>


int main(int argc, char* argv[]) {
	/*GLFW Version*/
	int major = -1;
	int minor = -1;
	int rev = -1;
	glfwGetVersion(&major, &minor, &rev);
	printf("GLFW Version: %d, %d, %d\n", major, minor, rev);

	/*If glfwInit fails, it calls glfwTerminate before returning. 
	 *If it succeeds, you should call glfwTerminate before the application exists.
	 */
	if (!glfwInit()) {
		std::cout << "Failed to initialize an OpenGL Context via GLFW." << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "An OpenGL Context Window", NULL, NULL);
	if (NULL == window) {
		std::cout << "Failed to create a glfw window." << std::endl;
		glfwTerminate();
	}

	glfwTerminate();
	return 0;
}
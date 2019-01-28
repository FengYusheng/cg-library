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

	/*Window creation hints.*/
	/*Speicify which client API to create context for.*/
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

	/*
	 *Specify which context API to use to create context,
	 *GLFW_EGL_CONTEXT_API or GLFW_NATIVE_CONTEXT_API.
	 */
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

	/*
	 *These two constrants aren't hard. Creation will fail if your OpenGL version of the created context 
	 *is less than the one requested.
	 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/*
	* This is function creates a window and its associated OpenGL or OpenGL ES context. The options 
	* controlling how the context should be created are specified by window hints.
	*/
	GLFWwindow* window = glfwCreateWindow(1024, 768, "An OpenGL Context Window", NULL, NULL);
	if (NULL == window) {
		std::cout << "Failed to create a glfw window." << std::endl;
		glfwTerminate();
	}

	/*Make the context of the specified window current on the calling thread.*/
	glfwMakeContextCurrent(window);
	glfwTerminate();
	return 0;
}
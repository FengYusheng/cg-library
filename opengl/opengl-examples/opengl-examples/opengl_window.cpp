#include<iostream>

/*
 * You must include glad.h before glfw3.h in that glad.h can promise include the correct version of OpenGL
 * header files.
 */
#include<glad/glad.h>
#include<GLFW/glfw3.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* window) {

}


int main(int argc, char* argv[]) {
	/*GLFW Version*/
	int major = -1;
	int minor = -1;
	int rev = -1;
	glfwGetVersion(&major, &minor, &rev);
	printf("GLFW Version: %d.%d.%d\n", major, minor, rev);

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
		return -1;
	}

	/*Make the context of the specified window current on the calling thread.*/
	glfwMakeContextCurrent(window);

	/*Initialize GLAD to load all OpenGL functions into your OpenGL context.*/
	/*It's recommended to use the loading function provided by your context creation framework.*/
	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Load OpenGL functions using glfwGetProcAddress." << std::endl;
		printf("The OpenGL version loaded actually is %d.%d\n", GLVersion.major, GLVersion.minor);
	}
	else if (gladLoadGL()) {
		std::cout << "Load OpenGL functions using builtin loader." << std::endl;
		printf("The OpenGL version loaded actually is %d.%d\n", GLVersion.major, GLVersion.minor);
	}
	else {
		std::cout << "Failed to initialize GLAD." << std::endl;
		glfwTerminate();
		return -1;
	}
	
	/*
	 * The mapping between the normalized coordinate and window coordinate is :
	 * x(w) = x + witdth/2 + x(nd)*witdth/2 
	 * y(w) = y + height/2 + y(nd)*height/2 
	 * glViewport(0, 0, 1024, 768);
	 * glfwSetFramebufferSizeCallback VS glfwSetWindowSizeCallback
	 */

	/*glfwSetWindowSizeCallback(window, framebuffer_size_callback);*/
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/*Input Mode*/
	int sticky_keys = glfwGetInputMode(window, GLFW_STICKY_KEYS);
	printf("Is current input mode Sticky Keys? %d\n", sticky_keys);
	
	/*Each iteration of render loop produces a frame.*/
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
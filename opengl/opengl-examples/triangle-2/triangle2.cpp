/*******************************************************************
 This program shows how to send data from a shader stage to another.
********************************************************************/

#include <iostream>
#include <cstring>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"

const int WINDOW_WITDH = 1920;
const int WIDNOW_HEIGHT = 1080;

void frame_buffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

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

	glfwSetWindowSizeCallback(window, frame_buffer_size_callback);

	/*compile shaders*/
	int status = 0;
	char info[512] = { '\0' };

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSourceCodes, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		std::cout << "vertex shader compilation failed!" << std::endl;
		std::memset(info, 0, sizeof(info));
		glGetShaderInfoLog(vertexShader, sizeof(info), NULL, info);
		std::cout << "Vertex shader compilation info: " << info << std::endl;
		glfwTerminate();
		return -1;
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSourceCodes, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		std::cout << "fragment shader compilation failed!" << std::endl;
		std::memset(info, 0, sizeof(info));
		glGetShaderInfoLog(fragmentShader, sizeof(info), NULL, info);
		std::cout << "Fragement shader compliaiton info: " << info << std::endl;
		glfwTerminate();
		return -1;
	}

	/*create a program object*/
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (GL_FALSE == status) {
		std::cout << " linking program failed!" << std::endl;
		std::memset(info, 0, sizeof(info));
		glGetProgramInfoLog(shaderProgram, sizeof(info), NULL, info);
		std::cout << "Linking program info: " << info << std::endl;
		glfwTerminate();
		return -1;
	}

	glUseProgram(shaderProgram);

	/*load data into shader pipeline.*/
	float data[] = {
		//vertex positions    colors
		-0.5f, 0.5f, 0.0f,    1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
		0.5F, -0.5f, 0.0f,    0.2f, 0.3f, 0.1f
	};

	unsigned int indices[] = {
		0, 1, 2, // first triangle
		2, 3, 1 // second triangle
	};
	
	/*VAO is a configuration object. OpenGL will render images according to the configrations stored in VAO.*/
	/*EBO, VBO are both generic data buffer. They are allocated in GPU memory.*/
	unsigned int VAO, VBO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	// https://stackoverflow.com/questions/23026612/gldrawelements-crash-opengl-3-2-windows-7
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 6*sizeof(GL_FLOAT), (void*)0);
	glEnableVertexArrayAttrib(VAO, 0);
	//glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6*sizeof(GL_FLOAT), (void*)(3*sizeof(GL_FLOAT)));
	glEnableVertexArrayAttrib(VAO, 1);
	//glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/*rendering loop*/
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.5f, 0.5f, 0.1f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		processInput(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	/*teminate GLFW*/
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
	glfwTerminate();
	return 0;
}
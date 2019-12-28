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
	int compileStatus = GL_FALSE;
	int linkStatus = GL_FALSE;
	char infoLog[512] = { '\0' };

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

	glfwMakeContextCurrent(window);

	/*Load OpenGL context fucntion pointer*/
	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Load OpenGL context API with glfwGetProcArddress function" << std::endl;
	}
	else if (gladLoadGL()) {
		std::cout << "Load OpenGL context API with gladLoadGL function" << std::endl;
	}
	else {
		std::cout << "Faild to load OpenGL context API." << std::endl;
		system("pause");
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_cb);

	/*OpenGL context info*/
	std::cout << "GL_VERDOR and GL_RENDERED can be used to specify a platform." << std::endl;
	std::cout << "The company which is responsible for this implementation is " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "The render is " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Ther version is " << glGetString(GL_VERSION) << std::endl;
	std::cout << "The shader language version is " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	/*Compile vertext shader.*/
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileStatus);
	if (!compileStatus) {
		std::memset(infoLog, 0, sizeof(infoLog));
		glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
		std::cout << "Failed to compile vertex shader: " << infoLog << std::endl;
		glfwTerminate();
		system("pause");
		return -1;
	}

	/*Compile fragment shader.*/
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileStatus);
	if (!compileStatus) {
		std::memset(infoLog, 0, sizeof(fragmentShader));
		glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
		std::cout << "Failed to compile fragment shader: " << infoLog << std::endl;
		glfwTerminate();
		system("pause");
		return -1;
	}

	/*Link shaders: create a program object and attach shader objects to it.*/
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus);
	if (!linkStatus) {
		glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
		std::cout << "Failed to link shade program: " << infoLog << std::endl;
		glfwTerminate();
		system("pause");
		return -1;
	}

	/*These shader objects can be deleted after attaching them to a shader program object.
	* These shader objects are makred for deleted. They aren't deleted until they are no longer attached to a program object.
	*/
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int VAO, VBO, EBO;

	float vertices[] = {
		0.5f, 0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f, // bottom right
		-0.5f, 0.5f, 0.0f, // top left
		-0.5f, -0.5f, 0.0f // bottom left
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		2, 3, 0 // second triangle
	};

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	/*Load vertex attributes to vertex shaders*/
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	/*Speicify which vertex attributes are loaded into VAO, gl_Position*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), (void*)0);
	/*Enable gl_Position*/
	glEnableVertexAttribArray(0);
	/*We have loaed vertex attributes into VAO and we can unbind VBO.*/
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	/*This is unnecessary. Just in case incorrect modification for this VAO.*/
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		/*Specify the background color.*/
		glClearColor(0.2f, 0.2f, 0.3f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		/*Start up the configurations in VAO, the following draw calls draw primitives according to these configurations.*/
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		/*This step is unnecessary.*/
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBindVertexArray(0);

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
	glViewport(0, 0, width, height);
}
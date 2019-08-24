#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstring>
#include <iostream>

#include "shaders.h"

// settings
const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 768;

void framebuffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow* window);

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

	/*Build and compile shader programs.*/
	/*-----------------------------------*/
	/*vertex shader*/
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	/*Check for vertex shader compilation status.*/
	int success = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	char infoLog[512] = { '\0' };
	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);

	if (!success)
	{
		std::cout << "Vertex shader compilation status: " << success << std::endl;
		std::cout << "Error::Shader::Vertex::Compilation Failed: \n" << infoLog << std::endl;

	}

	/*fragment shader*/
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	/*Check fragment shader compilation status.*/
	success = GL_FALSE;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	std::memset(infoLog, 0, sizeof(infoLog));
	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);

	if (!success)
	{
		std::cout << "Fragment shader compilation status: " << success << std::endl;
		std::cout << "Error::Shader::Fragment::Compilation Failed: \n" << infoLog << std::endl;
	}

	/*Link shaders.*/
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	/*Check link status.*/
	success = GL_FALSE;
	std::memset(infoLog, 0, sizeof(infoLog));
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		std::cout << "Program link status is " << success << std::endl;
		glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
		std::cout << "Error::Shader Programe::Link Failed: \n" << infoLog << std::endl;
	}

	/*Delete shader objects
	*these shader objects are flagged for deletion. They won't be deleted until they aren't attached to any program object.
	*/
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	/*The vertex shader is the first stage of OpenGL rendering pipeline. We need to specify its input manually*/
	/*We want to draw a triangle, so we specify three vertices' poisiton.*/
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, //left
		0.5f, -0.5f, 0.0f, //right
		0.0f, 0.5f, 0.0f, //top
	};

	/*The buffer in OpengGl refers to a piece of memory in GPU. There are various kinds of buffer in OpenGL and we can send data into these
	* buffers. OpenGL shader pipeline can access these data from buffers. We can send vertex data (AKA vertex attributes) into a buffer as 
	* the vertx shader input. We often call this kind of buffer used to store vertex attributes as VBO, vertex buffer object.
	*/

	/*Generate a buffer name. The name is just an integer. Bind an actual buffer object to this name.
	* Then we can access this buffer object via this buffer name.
	*/
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	/*GL_ARRAY_BUFFER indicates this buffer object is used to store vertex attributes for vertex shader.*/
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	/*Link vertex attributes. We want to modify "position" vertex attribute now.
	* 0 This parameter specifies which vertex attribute we want to modfiy. We have set "position" vertex attribute to 0 in vertex shader.
	*	We want to modify "position" vertex attribute so we assign 0 to this parameter.
	* 
	* 3 This parameter specifes how many components this attribute has. We assgin 3 to it since "posisiton" vertex attribute has 3 
	* components, x, y, z.
	*
	* GL_FLOAT This parameter specifies the data type of each vertex attribute component.
	*
	* GL_FALSE This parameter specifies if the data values should be normalized. We set it to false since the values are between -1 and 1.
	*
	* 3*sizeof(GL_FLOAT) This parameter specifies the offset between two vertex attributes. We set it to 3*sizeof(GL_FLOAT) since the second 
	* position vertex attribtue is 3*sizeof(GL_FLOAT) away from the first one in our vertex shader input.
	*
	* (void*)0 This parameter speicifies where the first position vertex attribute starts in the buffer object. There are just position data
	* in the buffer now. So we assign 0 to it.
	*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
	/*Our vertex shader processes position vertex atrritube for now. Enable position vertex attribute.*/
	glEnableVertexAttribArray(0);

	/*render loop*/
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);

		/*event processing:
		* https://www.glfw.org/docs/latest/input_guide.html#events
		*/
		glfwPollEvents();
	}
	
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	/* https://www.glfw.org/docs/latest/window_guide.html#window_close */
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
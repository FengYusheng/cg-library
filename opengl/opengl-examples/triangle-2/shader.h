#pragma once
// https://gamedev.stackexchange.com/questions/153078/what-can-i-do-with-the-4th-component-of-gl-position

const char* vertexShaderSourceCodes = "#version 450 core\n"
"layout (location=0) in vec3 aPos;\n"
"layout (location=1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main() {\n"
"	gl_Position = vec4(aPos, 1.0f);\n"
"	ourColor = aColor;\n"
"}\0";

const char* fragmentShaderSourceCodes = "#version 450 core\n"
"in vec3 ourColor;\n"
"out vec4 fragColor;\n"
"void main() {\n"
"	fragColor = vec4(ourColor, 1.0f);\n"
"}\0";
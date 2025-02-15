#include"Shader.hpp"
#include<GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const char* vertexShaderSrc = 
"#version 330 core\n"
"layout (location = 0) in vec3 pos;\n"
"\n"
"void main() {\n"
"	gl_Position = vec4(pos, 1.0);\n"
"}\n";

const char* fragmentShaderSrc =
"#version 330 core\n"
"out vec4 col;\n"
"\n"
"void main() {\n"
"	col = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
"}\n";

const float vertices[] = {
	 0.0f,  0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f
};

const int winWidth = 800, winHeight = 600;

int main() {
	// initializes GLFW. Potential Errors currently uncatched.
	glfwInit();

	// give GLFW hints about what OpenGL version we're using
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "Game", NULL, NULL);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize glad\n";
		return -1;
	}

	glViewport(0, 0, winWidth, winHeight);
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);

	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/*unsigned int vertexShader, fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);

	glCompileShader(vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if(!success)
	{
    	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if(!success)
	{
    	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int program;

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glUseProgram(program);*/

	Shader shader("../src/shader/vertex_shader.glsl", "../src/shader/fragment_shader.glsl");
	shader.use();

	int attribs;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &attribs);
	std::cout << attribs << std::endl;

	while(!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
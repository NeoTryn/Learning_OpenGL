// include filesystem to display cwd
#include <filesystem>
// include iostream for debug printing
#include <iostream>

// include shader class
#include "Shader.hpp"

// define width and height of window
#define WIDTH 800
#define HEIGHT 600

// declare the framebuffer_size_callback as well as process_input 
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

// define the vertices to display our triangle
const float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,	0.5f, 0.0f
};

int main() {
	
	// hints for glfw to know about opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// initialize glfw
	if (!glfwInit()) {
		std::cout << "GLFW couldn't initialize... Terminating program." << std::endl;
		glfwTerminate();
		return -1;
	}

	// define our window
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "SPACE INVADERS", NULL, NULL);

	if (!window) {
		std::cout << "window creation failed..." << std::endl;
	}

	glfwMakeContextCurrent(window);
	// set callback to the function we defined before
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Couldn't load GLAD..." << std::endl;
	}

	// set opengl viewport
	glViewport(0, 0, WIDTH, HEIGHT);

	// set clear color
	glClearColor(0.2f, 0.3f, 0.75f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// print out cwd
	std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

	unsigned int VBO, VAO;

	// generate and bind VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// generate and bind VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// set the vertices as VBO data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// set pointer 0 to the data we just set in the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	// declare our own shader
	Shader shader("vertex_shader.glsl", "fragment_shader.glsl");

	// game loop
	while (!glfwWindowShouldClose(window)) {
		process_input(window);

		// clear the colors every frame
		glClear(GL_COLOR_BUFFER_BIT);

		// draw triangle
		shader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	// end program
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

// definition of the framebuffer_size_callback.
// just set the opengl viewport to the new window size
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// definition of process_input
// check if esc is pressed. if so set that the window should close.
void process_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, true);
	}
}
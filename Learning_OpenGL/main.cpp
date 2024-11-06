// include filesystem to display cwd
#include <filesystem>
// include iostream for debug printing
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "Texture.hpp"

// define width and height of window
#define WIDTH 800
#define HEIGHT 600

// declare the framebuffer_size_callback as well as process_input 
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

// define the vertices to display our triangle



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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// print out cwd
	// std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

	/*float vertices[] = {
		// positions           // texture coords
		 1.0f, 1.0f, 0.0f,   1.0f, 1.0f, // top right
		 1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // bottom right
		 0.0f, 0.0f, 0.0f,   0.0f, 0.0f, // bottom left
		 0.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};*/

	float vertices[] = {
		// pos      // tex
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	Shader shader("vertex_shader.glsl", "fragment_shader.glsl");

	unsigned int VBO, VAO, EBO;

	// generate and bind VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// generate and bind VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// set the vertices as VBO data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// set pointer 0 to the data we just set in the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	Texture texture("awesomeface.png", GL_RGBA);
	//Texture texture2("awesomeface.png", GL_RGB);

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));

	view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
	projection = glm::ortho(0.0f, 4.0f, 0.0f, 3.0f , -1.0f, 1.0f);
	//projection = glm::perspective(glm::radians(45.0f), static_cast<float>(WIDTH) / static_cast<float>(HEIGHT), 0.1f, 100.0f);
	//model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));

	// declare our own shader
	shader.use();
	texture.use(0);
	shader.setInt("texture1", 0);

	glUniformMatrix4fv(glGetUniformLocation(shader.id , "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader.id, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader.id, "model"), 1, GL_FALSE, glm::value_ptr(model));

	//texture2.use(1);
	shader.setInt("texture2", 1);

	// game loop
	while (!glfwWindowShouldClose(window)) {
		process_input(window);

		// clear the colors every frame
		glClear(GL_COLOR_BUFFER_BIT);

		// draw triangle
		shader.use();
		
		glBindVertexArray(VAO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

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
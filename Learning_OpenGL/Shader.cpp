#include "Shader.hpp"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
	std::string vertexString, fragmentString;

	Shader::readFromFile(vertexShaderPath, &vertexString);
	Shader::readFromFile(fragmentShaderPath, &fragmentString);

	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	// std::cout << "VertexShader: " << vertexCode << std::endl << "FragmentShader: " << fragmentCode << std::endl;

	unsigned int vertexShader, fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexCode, NULL);
	glCompileShader(vertexShader);

	int success;
	char buffer[BUFSIZE];

	Shader::checkShaderCompileError(vertexShader, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, BUFSIZE, NULL, buffer);
		std::cout << "Vertex Shader compilation failed... InfoLog:" << std::endl << buffer << std::endl;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
	glCompileShader(fragmentShader);

	Shader::checkShaderCompileError(fragmentShader, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, BUFSIZE, NULL, buffer);
		std::cout << "Fragment Shader compilation failed... InfoLog:" << std::endl << buffer << std::endl;
	}

	Shader::id = glCreateProgram();
	glAttachShader(Shader::id, vertexShader);
	glAttachShader(Shader::id, fragmentShader);
	glLinkProgram(Shader::id);

	Shader::checkProgramLinkError(&success);

	if (!success) {
		glGetProgramInfoLog(Shader::id, BUFSIZE, NULL, buffer);
		std::cout << "Shader Program linking failed...InfoLog:" << std::endl << buffer << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::readFromFile(const char* path, std::string* stringToWrite) {
	std::ifstream stream(path);

	std::string line;

	while (std::getline(stream, line)) {
		*stringToWrite += line;
		*stringToWrite += "\n";
	}
}

void Shader::checkShaderCompileError(unsigned int shader, int* success) {
	glGetShaderiv(shader, GL_COMPILE_STATUS, success);
}

void Shader::checkProgramLinkError(int* success) {
	glGetProgramiv(Shader::id, GL_LINK_STATUS, success);
}

void Shader::use() {
	glUseProgram(Shader::id);
}

void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(Shader::id, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(Shader::id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(Shader::id, name.c_str()), value);
}
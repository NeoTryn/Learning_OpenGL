#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>

#ifndef SHADER_HPP
#define SHADER_HPP

#define BUFSIZE 512

class Shader {
public:
	unsigned int id;

	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	void readFromFile(const char* path, std::string* stringToWrite);
	void checkShaderCompileError(unsigned int shader, int* success);
	void checkProgramLinkError(int* success);
	void use();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
};

#endif
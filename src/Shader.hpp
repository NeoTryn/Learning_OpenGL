#include<glad/glad.h>

#include<iostream>
#include<fstream>

#include<string>

#ifndef Shader_HPP
#define Shader_HPP

class Shader {
public:

    unsigned int programId, vShaderId, fShaderId;

    Shader(std::string vShaderPath, std::string fShaderPath);

    void use();

    void setInt(int value, std::string location);
    void setBool(bool value, std::string location);
    void setFloat(float value, std::string location);

    void destroyShader(unsigned int shader);

private:

    void checkShaderError(unsigned int shader, int type);
    void checkProgramError(unsigned int program);

    const char* readShaderFromFile(std::string path);
};

#endif
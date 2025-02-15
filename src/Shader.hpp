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

private:

    int checkShaderError();
    int checkProgramError();

    const char* readShaderFromFile(std::string path);
};

#endif
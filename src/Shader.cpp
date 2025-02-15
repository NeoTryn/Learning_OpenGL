#include "Shader.hpp"

Shader::Shader(std::string vShaderPath, std::string fShaderPath) {
    std::string vShaderSrc = Shader::readShaderFromFile(vShaderPath);
    std::string fShaderSrc = Shader::readShaderFromFile(fShaderPath);

    const char* vShaderCStr = vShaderSrc.c_str();
    const char* fShaderCStr = fShaderSrc.c_str();

    std::cout << "Fragment Shader: " << fShaderSrc << std::endl;

    Shader::vShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(Shader::vShaderId, 1, &vShaderCStr, NULL);
    glCompileShader(Shader::vShaderId);

    Shader::checkShaderError(Shader::vShaderId, GL_VERTEX_SHADER);

    Shader::fShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(Shader::fShaderId, 1, &fShaderCStr, NULL);
    glCompileShader(Shader::fShaderId);

    Shader::checkShaderError(Shader::fShaderId, GL_FRAGMENT_SHADER);

    Shader::programId = glCreateProgram();
    glAttachShader(Shader::programId, Shader::vShaderId);
    glAttachShader(Shader::programId, Shader::fShaderId);
    glLinkProgram(Shader::programId);

    Shader::checkProgramError(Shader::programId);
}

std::string Shader::readShaderFromFile(std::string path) {
    std::string shader;

    std::ifstream ShaderFile(path);
    ShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {
        std::stringstream stream;

        stream << ShaderFile.rdbuf();

        ShaderFile.close();
        shader = stream.str();
    }
    catch(std::ifstream::failure e) {
        std::cout << "Couldn't read file...\n";
    }

    std::cout << shader;

    return shader;
}

void Shader::checkShaderError(unsigned int shader, int type) {
    int success;
    char log[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, log);
        std::string type_str;
        if (type == GL_VERTEX_SHADER) {
            type_str = "Vertex";
        }
        else if (type == GL_FRAGMENT_SHADER) {
            type_str = "Fragment";
        }
        else if (type == GL_GEOMETRY_SHADER) {
            type_str = "Geometry";
        }
        std::cout << type_str << " Shader Compilation failed: " << log << "\n";
    }
}

void Shader::checkProgramError(unsigned int program) {
    int success;
    char log[512];

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, log);
        std::cout << "Shader Program Compilation failed: " << log << "\n";
    }
}

void Shader::destroyShader(unsigned int shader) {
    glDeleteShader(shader);
    std::cout << "Shader destroyed successfully.\n";
}

void Shader::use() {
    glUseProgram(Shader::programId);
}

void Shader::setInt(int value, std::string location) {
    glUniform1i(glGetUniformLocation(Shader::programId, location.c_str()), value);
}

void Shader::setBool(bool value, std::string location) {
    glUniform1i(glGetUniformLocation(Shader::programId, location.c_str()), static_cast<int>(value));
}

void Shader::setFloat(float value, std::string location) {
    glUniform1f(glGetUniformLocation(Shader::programId, location.c_str()), value);
}
#include "Shader.hpp"

Shader::Shader(std::string vShaderPath, std::string fShaderPath) {
    const char* vShaderSrc = Shader::readShaderFromFile(vShaderPath);
    const char* fShaderSrc = Shader::readShaderFromFile(fShaderPath);

    Shader::vShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(Shader::vShaderId, 1, &vShaderSrc, NULL);
    glCompileShader(Shader::vShaderId);

    Shader::checkShaderError(Shader::vShaderId, GL_VERTEX_SHADER);

    Shader::fShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(Shader::fShaderId, 1, &fShaderSrc, NULL);
    glCompileShader(Shader::fShaderId);

    Shader::checkShaderError(Shader::fShaderId, GL_FRAGMENT_SHADER);

    Shader::programId = glCreateProgram();
    glAttachShader(Shader::programId, Shader::vShaderId);
    glAttachShader(Shader::programId, Shader::fShaderId);
    glLinkProgram(Shader::programId);

    Shader::checkProgramError(Shader::programId);
}

const char* Shader::readShaderFromFile(std::string path) {
    std::string shader, line;

    std::ifstream ShaderFile(path);

    try {
        std::string line;

        while(getline(ShaderFile, line)) {
            shader.append(line);
        }
    }
    catch(std::exception e) {
        std::cout << e.what() << "\n";
    }

    ShaderFile.close();
    return shader.c_str();
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
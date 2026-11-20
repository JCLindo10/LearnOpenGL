#pragma once
#include <string>

unsigned int getShaderProgram();
unsigned int getShaderProgram(const std::string vertexShaderPath, const std::string fragmentShaderPath);

class Shader {
    public:
        unsigned int programId;

        Shader(const std::string vertexPath, const std::string fragmentPath);

        void use(); // Activates the program

        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
};
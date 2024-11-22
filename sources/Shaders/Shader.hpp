//
// Created by Marcilio on 22/11/2024.
//

#ifndef SHADERS_HPP
#define SHADERS_HPP


#pragma once
#include <string>
#include <glm/glm.hpp>
#include <GL/gl.h>

class Shader {
    public:
    GLuint ID; // Identificador do programa shader

    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
    void setUniform(const std::string& name, float value);
    void setUniform(const std::string& name, int value);
    void setUniform(const std::string& name, const glm::vec3& value);
    void setUniform(const std::string& name, const glm::mat4& value);
};



#endif //SHADERS_HPP

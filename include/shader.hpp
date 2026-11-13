#pragma once

#include <glad/gl.h>

#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

struct Shader
{
    Shader();

    void use();
    bool compile(const char* vertPath, const char* fragPath);

    // for setting uniform variables in the shader
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

    void setVec2(const std::string& name, float x, float y) const;
    void setVec2(const std::string& name, const glm::vec2& vec) const;

    void setVec3(const std::string& name, float x, float y, float z) const;
    void setVec3(const std::string& name, const glm::vec3& vec) const;

    void setMat4(const std::string& name, const glm::mat4& mat) const;

private:
    unsigned id = 0;
};
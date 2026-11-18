#pragma once

#include <iostream>
#include <format>
#include <vector>
#include <array>
#include <bitset>
#include <unordered_map>
#include <cstdint>

#include <glad/gl.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Axis
{
    inline constexpr glm::vec3 X{ 1.0f, 0.0f, 0.0f };
    inline constexpr glm::vec3 Y{ 0.0f, 1.0f, 0.0f };
    inline constexpr glm::vec3 Z{ 0.0f, 0.0f, 1.0f };

    inline constexpr glm::vec3 XY{ 1.0f, 1.0f, 0.0f };
    inline constexpr glm::vec3 XZ{ 1.0f, 0.0f, 1.0f };
    inline constexpr glm::vec3 YZ{ 0.0f, 1.0f, 1.0f };

    inline constexpr glm::vec3 XYZ{ 1.0f, 1.0f, 1.0f };
}
#pragma once

#include <glm/fwd.hpp>

struct GLFWwindow;
// class Camera2D;

namespace Input {
    void init(GLFWwindow* glfwWindow);

    void setViewAndProjectionMatrices(glm::mat4 const& view, glm::mat4 const& projection);
    
    void beginFrame();
    // void update();
    // void update(Key key, GLFWwindow* glfwWindow);
    // void update(Mouse mouse, GLFWwindow* glfwWindow);
    // void updateScroll(GLFWwindow* glfwWindow); // (double sX, double sY)
    // void updateMousePos(GLFWwindow* glfwWindow); // (double x, double y)
}
#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

class Window
{
private:
    static constexpr int s_startWidth = 800;
    static constexpr int s_startHeight = 600;
    static constexpr const char* s_windowName = "Red Hot Zombies";

    GLFWwindow* m_window = nullptr;
    glm::ivec2 m_winSize = { s_startWidth, s_startHeight };

private:
    void destroy();

public:
    Window();
    ~Window();
    
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool init();
    bool shouldClose() const;
    void processInput();
    void pollEvents();
    void swapBuffers();

    glm::ivec2 getWinSize() const { return m_winSize; }
};
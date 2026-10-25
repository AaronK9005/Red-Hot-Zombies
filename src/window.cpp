#include "window.hpp"

#include <iostream>
#include <fstream>

Window::Window() {}

Window::~Window()
{
    destroy();
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

bool Window::init()
{
    // std::fstream errorFile(LOGS_PATH "errorLog.txt");

    if (!glfwInit())
    {
        std::cerr << "glfwInit() failed" << std::endl;
        return false;
    }

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    #if __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    m_window = glfwCreateWindow(
        s_startWidth,
        s_startHeight,
        s_windowName,
        nullptr, // glfwGetPrimaryMonitor()
        nullptr
    );

    if (!m_window)
    {
        std::cerr << "glfwCreateWindow() failed" << std::endl;
        return false;
    }

    // make fullscreen
    // glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), )

    glfwMakeContextCurrent(m_window);

	glfwSetKeyCallback(m_window, nullptr);  // keyCallback
	glfwSetMouseButtonCallback(m_window, nullptr);  // mouseCallback
	glfwSetWindowFocusCallback(m_window, nullptr);  // WindowFocusCallback
	glfwSetWindowSizeCallback(m_window, nullptr);  // WindowSizeCallback
	glfwSetCursorPosCallback(m_window, nullptr);  // cursorPositionCallback
	glfwSetCharCallback(m_window, nullptr);  // characterCallback
	glfwSetScrollCallback(m_window, nullptr);  // scrollCallback
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback); //?

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        std::cerr << "gladLoadGL() failed" << std::endl;
        return false;
    }

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    return true;
}

void Window::destroy()
{
    if (m_window)
    {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }

    glfwTerminate();
}

bool Window::shouldClose() const
{
    return !m_window || glfwWindowShouldClose(m_window);
}

void Window::processInput()
{
    if (
        glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
        glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS
    )
    {
        glfwSetWindowShouldClose(m_window, true);
    }
}
void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::swapBuffers()
{
    glfwSwapBuffers(m_window);
}



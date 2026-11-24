#include "window.hpp"

#include "pch.hpp"
#include <gl/GL.h>

Window::Window() {}

Window::~Window()
{
    destroy();
}

#pragma region |> window callbacks <|
void Window::Callbacks::framebufferSize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::Callbacks::windowSize(GLFWwindow* window, int width, int height)
{
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

    self->m_winSize = {width, height};
}
#pragma endregion

bool Window::init()
{
    if (!glfwInit())
    {
        std::cerr << "glfwInit() failed" << std::endl;
        return false;
    }

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // #if DEBUG
    // glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    // #endif

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
    glfwSetWindowUserPointer(m_window, this);

    // #if DEBUG
    // int flags;
    // glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    // if (!(flags & GL_CONTEXT_FLAG_DEBUG_BIT))
    // {
    //     std::cout << "Window::init(): Failed to init debug context\n";
    //     return false;
    // }
    // #endif

	glfwSetWindowFocusCallback(m_window, nullptr);  // WindowFocusCallback
	glfwSetWindowSizeCallback(m_window, Callbacks::windowSize);
	glfwSetCharCallback(m_window, nullptr);  // characterCallback
    glfwSetFramebufferSizeCallback(m_window, Callbacks::framebufferSize);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        std::cerr << "gladLoadGL() failed" << std::endl;
        return false;
    }

    glClearColor(0.4f, 0.4f, 0.2f, 1.0f);

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



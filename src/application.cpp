#include "application.hpp"
#include "timer.hpp"

Application::Application()
{

}

Application::~Application()
{
    
}

bool Application::init()
{
    if (!window.init())
    {
        return false;
    }

    return true;
}

void Application::run()
{
    bool running = true;

    Timer timer{};

    while (running)
    {
        window.processInput();

        if (window.shouldClose())
        {
            running = false;
            break;
        }

        float dt = timer.getDeltaTime();

        glClear(GL_COLOR_BUFFER_BIT);

        window.swapBuffers();
        window.pollEvents();
    }
}

void Application::shutdown()
{

}


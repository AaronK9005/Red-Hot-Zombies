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

    if (!m_shader.compile(SHADERS_PATH "basic.vert", SHADERS_PATH "basic.frag"))
    {
        return false;
    }

    if (!renderer.init(window))
    {
        return false;
    }
    renderer.setShader(m_shader);
    renderer.setCamera(camera);

    if (!game.init(window.getWinSize()))
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

        game.handleInput();

        game.update(dt);

        renderer.render(game);        

        window.swapBuffers();
        window.pollEvents();
        window.updateInput();
    }
}

void Application::shutdown()
{

}


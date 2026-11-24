#include "application.hpp"
#include "timer.hpp"
#include "platform/input_update.hpp"

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
    renderer.setCamera(m_camera);

    Input::init(window.getGLFWwindow());
    Input::setViewAndProjectionMatrices(m_camera.getViewMatrix(), renderer.getProjectionMatrix());

    if (!game.init(window.getWinSize()))
    {
        return false;
    }

    if (!test_texture.loadFromFile(RESOURCES_PATH "assets/color_splash_bg.jpg"))
    {
        std::cout << "test texture loading failed\n";
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
        Input::beginFrame();

        window.processInput();

        window.pollEvents();

        if (window.shouldClose())
        {
            running = false;
            break;
        }

        float dt = getDeltaTime();

        Input::setViewAndProjectionMatrices(
            m_camera.getViewMatrix(),
            renderer.getProjectionMatrix()
        );

        PlayerInput playerInput = game.handleInput();

        game.update(playerInput, dt);

        m_camera.m_position = game.m_data.player.m_position;

        renderer.render(game);        

        window.swapBuffers();
    }
}

void Application::shutdown()
{

}

float Application::getDeltaTime()
{
    auto currentTime = std::chrono::high_resolution_clock::now();

    float dt = std::chrono::duration<float>(currentTime - lastTime).count();

    lastTime = currentTime;

    return dt;
}
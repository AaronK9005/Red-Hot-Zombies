#pragma once

#include "window.hpp"
#include "game.hpp"
#include "renderer.hpp"
#include "camera.hpp"
#include "shader.hpp"

class Application
{
    Window window{};
    Renderer renderer{};
    Camera2D camera{};
    Shader m_shader{};
    Game game{};

public:
    Application();
    ~Application();
    bool init();
    void run();
    void shutdown();
};
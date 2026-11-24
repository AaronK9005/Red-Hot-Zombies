#pragma once

#include "pch.hpp"
#include "window.hpp"
#include "game.hpp"
#include "renderer.hpp"
#include "camera.hpp"
#include "shader.hpp"

// for testing only
#include "texture.hpp"

class Application
{
    Window window{};
    Renderer renderer{};
    Camera2D m_camera{};
    Shader m_shader{};
    Game game{};

    std::chrono::high_resolution_clock::time_point lastTime{};

    // for testing only
    Texture test_texture{};

public:
    Application();
    ~Application();
    bool init();
    void run();
    void shutdown();

private:
    float getDeltaTime();
};
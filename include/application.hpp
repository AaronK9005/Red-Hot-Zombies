#pragma once

#include "window.hpp"
#include "game.hpp"

class Application
{
    Window window{};
    Game game{};
    bool keys[GLFW_KEY_LAST + 1]{};

public:
    Application();
    ~Application();
    bool init();
    void run();
    void shutdown();
};
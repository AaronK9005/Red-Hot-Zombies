#pragma once

#include "window.hpp"
#include "game.hpp"

class Application
{
    Window window{};
    Game game{};

public:
    Application();
    ~Application();
    bool init();
    void run();
    void shutdown();
};
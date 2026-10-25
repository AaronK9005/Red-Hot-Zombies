#pragma once

#include "window.hpp"

class Application
{
    Window window{};

public:
    Application();
    ~Application();
    bool init();
    void run();
    void shutdown();
};
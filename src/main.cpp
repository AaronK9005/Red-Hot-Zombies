#include <iostream>

#include "application.hpp"

int main()
{
    Application app;
    if (app.init())
    {
        app.run();
    }
    app.shutdown();

    return 0;
}
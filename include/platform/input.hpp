#pragma once

#include "platform/keyboard.hpp"
#include "platform/mousebuttons.hpp"

namespace Input {
    bool isPressed(Key key); // is held down
    bool justPressed(Key key); // was pressed this frame
    bool justReleased(Key key); // was released this frame

    bool isPressed(Mouse mouse); // is held down
    bool justPressed(Mouse mouse); // was pressed this frame
    bool justReleased(Mouse mouse); // was released this frame
};
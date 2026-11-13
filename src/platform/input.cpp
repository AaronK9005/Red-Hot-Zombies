#include "platform/input.hpp"

#include <bitset>

static std::bitset<static_cast<size_t>(Key::COUNT)> currentKeyboard;
static std::bitset<static_cast<size_t>(Key::COUNT)> previousKeyboard;

static std::bitset<static_cast<size_t>(Mouse::COUNT)> currentMouse;
static std::bitset<static_cast<size_t>(Mouse::COUNT)> previousMouse;

namespace Input
{
    void update(Key key, bool value)
    {
        previousKeyboard[static_cast<size_t>(key)] = currentKeyboard[static_cast<size_t>(key)];
        currentKeyboard[static_cast<size_t>(key)] = value;
    }

    bool isPressed(Key key)
    {
        return currentKeyboard[static_cast<size_t>(key)];
    }

    bool justPressed(Key key)
    {
        return currentKeyboard[static_cast<size_t>(key)] && !previousKeyboard[static_cast<size_t>(key)];
    }

    bool justReleased(Key key)
    {
        return !currentKeyboard[static_cast<size_t>(key)] && previousKeyboard[static_cast<size_t>(key)];
    }

    void update(Mouse mouse, bool value)
    {
        previousMouse[static_cast<size_t>(mouse)] = currentMouse[static_cast<size_t>(mouse)];
        currentMouse[static_cast<size_t>(mouse)] = value;
    }

    bool isPressed(Mouse mouse)
    {
        return currentMouse[static_cast<size_t>(mouse)];
    }

    bool justPressed(Mouse mouse)
    {
        return currentMouse[static_cast<size_t>(mouse)] && !previousMouse[static_cast<size_t>(mouse)];
    }

    bool justReleased(Mouse mouse)
    {
        return !currentMouse[static_cast<size_t>(mouse)] && previousMouse[static_cast<size_t>(mouse)];
    }


} // namespace Input

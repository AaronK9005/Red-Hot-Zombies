#pragma once

enum class Mouse {
    NONE = -1,
    button1, button2, button3, button4,
    button5, button6, button7, button8,
    COUNT,

    LEFT = button1,
    RIGHT = button2,
    MIDDLE = button3,

    BUTTON_FIRST = button1,
    BUTTON_LAST = button2,
};
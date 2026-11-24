#include "platform/input.hpp"
#include "platform/input_update.hpp"

#include <bitset>
#include <glm/mat4x4.hpp>

static constexpr auto makeGLFWtoKeyMapping()
{
    std::array<Key, GLFW_KEY_LAST + 1> map{};
    map.fill(Key::NONE);

    map[GLFW_KEY_SPACE] = Key::SPACE;
    map[GLFW_KEY_APOSTROPHE] = Key::APOSTROPHE;
    map[GLFW_KEY_COMMA] = Key::COMMA;
    map[GLFW_KEY_MINUS] = Key::MINUS;
    map[GLFW_KEY_PERIOD] = Key::PERIOD;
    map[GLFW_KEY_SLASH] = Key::SLASH;
    map[GLFW_KEY_0] = Key::KEY_0;
    map[GLFW_KEY_1] = Key::KEY_1;
    map[GLFW_KEY_2] = Key::KEY_2;
    map[GLFW_KEY_3] = Key::KEY_3;
    map[GLFW_KEY_4] = Key::KEY_4;
    map[GLFW_KEY_5] = Key::KEY_5;
    map[GLFW_KEY_6] = Key::KEY_6;
    map[GLFW_KEY_7] = Key::KEY_7;
    map[GLFW_KEY_8] = Key::KEY_8;
    map[GLFW_KEY_9] = Key::KEY_9;
    map[GLFW_KEY_SEMICOLON] = Key::SEMICOLON;
    map[GLFW_KEY_EQUAL] = Key::EQUAL;
    map[GLFW_KEY_A] = Key::A;
    map[GLFW_KEY_B] = Key::B;
    map[GLFW_KEY_C] = Key::C;
    map[GLFW_KEY_D] = Key::D;
    map[GLFW_KEY_E] = Key::E;
    map[GLFW_KEY_F] = Key::F;
    map[GLFW_KEY_G] = Key::G;
    map[GLFW_KEY_H] = Key::H;
    map[GLFW_KEY_I] = Key::I;
    map[GLFW_KEY_J] = Key::J;
    map[GLFW_KEY_K] = Key::K;
    map[GLFW_KEY_L] = Key::L;
    map[GLFW_KEY_M] = Key::M;
    map[GLFW_KEY_N] = Key::N;
    map[GLFW_KEY_O] = Key::O;
    map[GLFW_KEY_P] = Key::P;
    map[GLFW_KEY_Q] = Key::Q;
    map[GLFW_KEY_R] = Key::R;
    map[GLFW_KEY_S] = Key::S;
    map[GLFW_KEY_T] = Key::T;
    map[GLFW_KEY_U] = Key::U;
    map[GLFW_KEY_V] = Key::V;
    map[GLFW_KEY_W] = Key::W;
    map[GLFW_KEY_X] = Key::X;
    map[GLFW_KEY_Y] = Key::Y;
    map[GLFW_KEY_Z] = Key::Z;
    map[GLFW_KEY_LEFT_BRACKET] = Key::LEFT_BRACKET;
    map[GLFW_KEY_BACKSLASH] = Key::BACKSLASH;
    map[GLFW_KEY_RIGHT_BRACKET] = Key::RIGHT_BRACKET;
    map[GLFW_KEY_GRAVE_ACCENT] = Key::GRAVE_ACCENT;
    map[GLFW_KEY_WORLD_1] = Key::WORLD_1;
    map[GLFW_KEY_WORLD_2] = Key::WORLD_2;

    map[GLFW_KEY_ESCAPE] = Key::ESCAPE;
    map[GLFW_KEY_ENTER] = Key::ENTER;
    map[GLFW_KEY_TAB] = Key::TAB;
    map[GLFW_KEY_BACKSPACE] = Key::BACKSPACE;
    map[GLFW_KEY_INSERT] = Key::INSERT;
    map[GLFW_KEY_DELETE] = Key::DELETE;
    map[GLFW_KEY_RIGHT] = Key::RIGHT;
    map[GLFW_KEY_LEFT] = Key::LEFT;
    map[GLFW_KEY_DOWN] = Key::DOWN;
    map[GLFW_KEY_UP] = Key::UP;
    map[GLFW_KEY_PAGE_UP] = Key::PAGE_UP;
    map[GLFW_KEY_PAGE_DOWN] = Key::PAGE_DOWN;
    map[GLFW_KEY_HOME] = Key::HOME;
    map[GLFW_KEY_END] = Key::END;
    map[GLFW_KEY_CAPS_LOCK] = Key::CAPS_LOCK;
    map[GLFW_KEY_SCROLL_LOCK] = Key::SCROLL_LOCK;
    map[GLFW_KEY_NUM_LOCK] = Key::NUM_LOCK;
    map[GLFW_KEY_PRINT_SCREEN] = Key::PRINT_SCREEN;
    map[GLFW_KEY_PAUSE] = Key::PAUSE;
    map[GLFW_KEY_F1] = Key::F1;
    map[GLFW_KEY_F2] = Key::F2;
    map[GLFW_KEY_F3] = Key::F3;
    map[GLFW_KEY_F4] = Key::F4;
    map[GLFW_KEY_F5] = Key::F5;
    map[GLFW_KEY_F6] = Key::F6;
    map[GLFW_KEY_F7] = Key::F7;
    map[GLFW_KEY_F8] = Key::F8;
    map[GLFW_KEY_F9] = Key::F9;
    map[GLFW_KEY_F10] = Key::F10;
    map[GLFW_KEY_F11] = Key::F11;
    map[GLFW_KEY_F12] = Key::F12;
    map[GLFW_KEY_F13] = Key::F13;
    map[GLFW_KEY_F14] = Key::F14;
    map[GLFW_KEY_F15] = Key::F15;
    map[GLFW_KEY_F16] = Key::F16;
    map[GLFW_KEY_F17] = Key::F17;
    map[GLFW_KEY_F18] = Key::F18;
    map[GLFW_KEY_F19] = Key::F19;
    map[GLFW_KEY_F20] = Key::F20;
    map[GLFW_KEY_F21] = Key::F21;
    map[GLFW_KEY_F22] = Key::F22;
    map[GLFW_KEY_F23] = Key::F23;
    map[GLFW_KEY_F24] = Key::F24;
    map[GLFW_KEY_F25] = Key::F25;
    map[GLFW_KEY_KP_0] = Key::KP_0;
    map[GLFW_KEY_KP_1] = Key::KP_1;
    map[GLFW_KEY_KP_2] = Key::KP_2;
    map[GLFW_KEY_KP_3] = Key::KP_3;
    map[GLFW_KEY_KP_4] = Key::KP_4;
    map[GLFW_KEY_KP_5] = Key::KP_5;
    map[GLFW_KEY_KP_6] = Key::KP_6;
    map[GLFW_KEY_KP_7] = Key::KP_7;
    map[GLFW_KEY_KP_8] = Key::KP_8;
    map[GLFW_KEY_KP_9] = Key::KP_9;
    map[GLFW_KEY_KP_DECIMAL] = Key::KP_DECIMAL;
    map[GLFW_KEY_KP_DIVIDE] = Key::KP_DIVIDE;
    map[GLFW_KEY_KP_MULTIPLY] = Key::KP_MULTIPLY;
    map[GLFW_KEY_KP_SUBTRACT] = Key::KP_SUBTRACT;
    map[GLFW_KEY_KP_ADD] = Key::KP_ADD;
    map[GLFW_KEY_KP_ENTER] = Key::KP_ENTER;
    map[GLFW_KEY_KP_EQUAL] = Key::KP_EQUAL;
    map[GLFW_KEY_LEFT_SHIFT] = Key::LEFT_SHIFT;
    map[GLFW_KEY_LEFT_CONTROL] = Key::LEFT_CONTROL;
    map[GLFW_KEY_LEFT_ALT] = Key::LEFT_ALT;
    map[GLFW_KEY_LEFT_SUPER] = Key::LEFT_SUPER;
    map[GLFW_KEY_RIGHT_SHIFT] = Key::RIGHT_SHIFT;
    map[GLFW_KEY_RIGHT_CONTROL] = Key::RIGHT_CONTROL;
    map[GLFW_KEY_RIGHT_ALT] = Key::RIGHT_ALT;
    map[GLFW_KEY_RIGHT_SUPER] = Key::RIGHT_SUPER;
    map[GLFW_KEY_MENU] = Key::MENU;

    return map;
}

namespace Input
{
    static constexpr std::array mouseToGLFW = {
        GLFW_MOUSE_BUTTON_1,
        GLFW_MOUSE_BUTTON_2,
        GLFW_MOUSE_BUTTON_3,
        GLFW_MOUSE_BUTTON_4,
        GLFW_MOUSE_BUTTON_5,
        GLFW_MOUSE_BUTTON_6,
        GLFW_MOUSE_BUTTON_7,
        GLFW_MOUSE_BUTTON_8
    };
    static constexpr std::array GLFWtoMouse = {
        Mouse::button1,
        Mouse::button2,
        Mouse::button3,
        Mouse::button4,
        Mouse::button5,
        Mouse::button6,
        Mouse::button7,
        Mouse::button8
    };

    static constexpr std::array keyToGLFW = {
        /* printable keys */
        GLFW_KEY_SPACE,
        GLFW_KEY_APOSTROPHE,
        GLFW_KEY_COMMA,
        GLFW_KEY_MINUS,
        GLFW_KEY_PERIOD,
        GLFW_KEY_SLASH,
        GLFW_KEY_0,
        GLFW_KEY_1,
        GLFW_KEY_2,
        GLFW_KEY_3,
        GLFW_KEY_4,
        GLFW_KEY_5,
        GLFW_KEY_6,
        GLFW_KEY_7,
        GLFW_KEY_8,
        GLFW_KEY_9,
        GLFW_KEY_SEMICOLON,
        GLFW_KEY_EQUAL,
        GLFW_KEY_A,
        GLFW_KEY_B,
        GLFW_KEY_C,
        GLFW_KEY_D,
        GLFW_KEY_E,
        GLFW_KEY_F,
        GLFW_KEY_G,
        GLFW_KEY_H,
        GLFW_KEY_I,
        GLFW_KEY_J,
        GLFW_KEY_K,
        GLFW_KEY_L,
        GLFW_KEY_M,
        GLFW_KEY_N,
        GLFW_KEY_O,
        GLFW_KEY_P,
        GLFW_KEY_Q,
        GLFW_KEY_R,
        GLFW_KEY_S,
        GLFW_KEY_T,
        GLFW_KEY_U,
        GLFW_KEY_V,
        GLFW_KEY_W,
        GLFW_KEY_X,
        GLFW_KEY_Y,
        GLFW_KEY_Z,
        GLFW_KEY_LEFT_BRACKET,
        GLFW_KEY_BACKSLASH,
        GLFW_KEY_RIGHT_BRACKET,
        GLFW_KEY_GRAVE_ACCENT,
        GLFW_KEY_WORLD_1,
        GLFW_KEY_WORLD_2,

        /* function keys */
        GLFW_KEY_ESCAPE,
        GLFW_KEY_ENTER,
        GLFW_KEY_TAB,
        GLFW_KEY_BACKSPACE,
        GLFW_KEY_INSERT,
        GLFW_KEY_DELETE,
        GLFW_KEY_RIGHT,
        GLFW_KEY_LEFT,
        GLFW_KEY_DOWN,
        GLFW_KEY_UP,
        GLFW_KEY_PAGE_UP,
        GLFW_KEY_PAGE_DOWN,
        GLFW_KEY_HOME,
        GLFW_KEY_END,
        GLFW_KEY_CAPS_LOCK,
        GLFW_KEY_SCROLL_LOCK,
        GLFW_KEY_NUM_LOCK,
        GLFW_KEY_PRINT_SCREEN,
        GLFW_KEY_PAUSE,
        GLFW_KEY_F1,
        GLFW_KEY_F2,
        GLFW_KEY_F3,
        GLFW_KEY_F4,
        GLFW_KEY_F5,
        GLFW_KEY_F6,
        GLFW_KEY_F7,
        GLFW_KEY_F8,
        GLFW_KEY_F9,
        GLFW_KEY_F10,
        GLFW_KEY_F11,
        GLFW_KEY_F12,
        GLFW_KEY_F13,
        GLFW_KEY_F14,
        GLFW_KEY_F15,
        GLFW_KEY_F16,
        GLFW_KEY_F17,
        GLFW_KEY_F18,
        GLFW_KEY_F19,
        GLFW_KEY_F20,
        GLFW_KEY_F21,
        GLFW_KEY_F22,
        GLFW_KEY_F23,
        GLFW_KEY_F24,
        GLFW_KEY_F25,
        GLFW_KEY_KP_0,
        GLFW_KEY_KP_1,
        GLFW_KEY_KP_2,
        GLFW_KEY_KP_3,
        GLFW_KEY_KP_4,
        GLFW_KEY_KP_5,
        GLFW_KEY_KP_6,
        GLFW_KEY_KP_7,
        GLFW_KEY_KP_8,
        GLFW_KEY_KP_9,
        GLFW_KEY_KP_DECIMAL,
        GLFW_KEY_KP_DIVIDE,
        GLFW_KEY_KP_MULTIPLY,
        GLFW_KEY_KP_SUBTRACT,
        GLFW_KEY_KP_ADD,
        GLFW_KEY_KP_ENTER,
        GLFW_KEY_KP_EQUAL,
        GLFW_KEY_LEFT_SHIFT,
        GLFW_KEY_LEFT_CONTROL,
        GLFW_KEY_LEFT_ALT,
        GLFW_KEY_LEFT_SUPER,
        GLFW_KEY_RIGHT_SHIFT,
        GLFW_KEY_RIGHT_CONTROL,
        GLFW_KEY_RIGHT_ALT,
        GLFW_KEY_RIGHT_SUPER,
        GLFW_KEY_MENU,
    };
    static constexpr std::array GLFWtoKey = makeGLFWtoKeyMapping();

    static std::bitset<static_cast<size_t>(Key::COUNT)> currentKeyboard;
    static std::bitset<static_cast<size_t>(Key::COUNT)> previousKeyboard;

    static std::bitset<static_cast<size_t>(Mouse::COUNT)> currentMouse;
    static std::bitset<static_cast<size_t>(Mouse::COUNT)> previousMouse;

    static GLFWwindow* window = nullptr;

    static double mouse_x, mouse_y;
    static double prevMouse_x, prevMouse_y;
    static double scroll_x, scroll_y;

    // static float worldX = 0.0f, worldY = 0.0f;
    static float ndcX = 0.0f, ndcY = 0.0f, ndcZ = 0.0f; // normal device coordinates <-1,1>
    static glm::mat4 inverseVP;

    void init(GLFWwindow* glfwWindow)
    {
        window = glfwWindow;

        glfwSetKeyCallback(glfwWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods){
            // if (key < (int)Key::FIRST || key > (int)Key::LAST) return;

            int i = static_cast<int>(GLFWtoKey[key]);

            currentKeyboard[i] = action != GLFW_RELEASE;
        });

        glfwSetMouseButtonCallback(glfwWindow, [](GLFWwindow* window, int button, int action, int mods){
            // if (button < (int)Mouse::BUTTON_FIRST || button > (int)Mouse::BUTTON_LAST) return;

            int i = static_cast<int>(GLFWtoMouse[button]);

            currentMouse[i] = action != GLFW_RELEASE;
            
            // Mouse mouse = GLFWtoMouse[button];
            // if (mouse == Mouse::RIGHT && action == GLFW_PRESS)
            // {
            //     std::cout << "Right mouse pressed\n";
            // }
        });

        glfwSetCursorPosCallback(glfwWindow, [](GLFWwindow* window, double xpos, double ypos){
            prevMouse_x = mouse_x;
            prevMouse_y = mouse_y;

            mouse_x = xpos;
            mouse_y = ypos;

            int width, height;
            glfwGetWindowSize(window, &width, &height);

            ndcX = 2.0f * mouse_x / width - 1.0f;
            ndcY = 1.0f - 2.0f * mouse_y / height;
        });

        glfwSetScrollCallback(glfwWindow, [](GLFWwindow* window, double xoffset, double yoffset){
            scroll_x = xoffset;
            scroll_y = yoffset;
        });

        glfwGetCursorPos(glfwWindow, &mouse_x, &mouse_y);
        glfwSetCursorPos(glfwWindow, mouse_x, mouse_y);
    }

    void setViewAndProjectionMatrices(glm::mat4 const& view, glm::mat4 const& projection)
    {
        glm::mat4 vp = projection * view; // projection * view matrix
        inverseVP = glm::inverse(vp);

        glm::vec4 clip = vp * glm::vec4(0, 0, 0, 1);
        ndcZ = clip.z / clip.w;
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

    glm::vec2 getMousePos()
    {
        return { mouse_x, mouse_y };
    }

    glm::vec2 getMouseDelta()
    {
        return { mouse_x - prevMouse_x, mouse_y - prevMouse_y };
    }

    glm::vec2 getMouseScroll()
    {
        return { scroll_x, scroll_y };
    }

    glm::vec2 getMousePos_NDC()
    {
        return { ndcX, ndcY };
    }

    glm::vec2 getMousePos_world()
    {
        glm::vec4 world = inverseVP * glm::vec4(ndcX, ndcY, ndcZ, 1.0f);
        world /= world.w;

        return { world.x, world.y };
    }

    double getScroll_x()
    {
        return scroll_x;
    }

    double getScroll_y()
    {
        return scroll_y;
    }

    void beginFrame()
    {
        previousKeyboard = currentKeyboard;
        previousMouse = currentMouse;
    }

    // * old stuff *
    /*
    // void update()
    // {
    //     // for (int i = static_cast<int>(Key::FIRST); i <= static_cast<int>(Key::LAST); i++)
    //     // {
    //     //     Input::update(static_cast<Key>(i), m_window);
    //     // }

    //     // for (int i = static_cast<int>(Mouse::BUTTON_FIRST); i <= static_cast<int>(Mouse::BUTTON_LAST); i++)
    //     // {
    //     //     Input::update(static_cast<Mouse>(i), m_window);
    //     // }

    //     // Input::updateMousePos(m_window);
    //     // Input::updateScroll(m_window);
    // }

    // void update(Key key, GLFWwindow* glfwWindow)
    // {
    //     bool value = glfwGetKey(glfwWindow, keyToGLFW[(int)key]) == GLFW_PRESS;
    //     previousKeyboard[static_cast<size_t>(key)] = currentKeyboard[static_cast<size_t>(key)];
    //     currentKeyboard[static_cast<size_t>(key)] = value;
    // }

    // void update(Mouse mouse, GLFWwindow* glfwWindow)
    // {
    //     bool value = glfwGetMouseButton(glfwWindow, mouseToGLFW[(int)mouse]) == GLFW_PRESS;
    //     previousMouse[static_cast<size_t>(mouse)] = currentMouse[static_cast<size_t>(mouse)];
    //     currentMouse[static_cast<size_t>(mouse)] = value;
    // }

    // void updateScroll(GLFWwindow* glfwWindow)
    // {
        
    // }

    // void updateMousePos(GLFWwindow* glfwWindow)
    // {
    //     prevMouse_x = mouse_x;
    //     prevMouse_y = mouse_y;

    //     glfwGetCursorPos(glfwWindow, &mouse_x, &mouse_y);
    // }
    */

} // namespace Input

#ifndef INPUT_HAND_H
#define INPUT_HAND_H

#include "game.hpp"

class Game;

class InputHandler {
    public:
    InputHandler(Game* game);
    private:
    Game* game;
    bool firstMouseInput;
    float mouseLastX;
    float mouseLastY;
    float yaw;
    float pitch;
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    class CallbackWrapper {
        public:
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
        static InputHandler* staticInputHandler;
    };
};


#endif
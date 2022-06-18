#ifndef INPUT_HAND_H
#define INPUT_HAND_H

#include "../game.hpp"
#include "../../window/window.hpp"

class Game;

struct InputHandler {
public:
    InputHandler();
    void process_inputs(Window* window, Game* game, float deltaTime);
    void bind_input_callbacks(Window* window, Game* game);
private:
    bool firstMouseInput;
    float mouseLastX;
    float mouseLastY;
    float yaw;
    float pitch;
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void resize_callback(GLFWwindow* window, int width, int height);
    class CallbackWrapper {
        public:
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
        static void resize_callback(GLFWwindow* window, int width, int height);
        static InputHandler* staticInputHandler;
    };
};


#endif
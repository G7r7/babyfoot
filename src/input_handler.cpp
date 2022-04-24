#include "input_handler.hpp"

InputHandler* InputHandler::CallbackWrapper::staticInputHandler;

InputHandler::InputHandler(Game* game) : game{game}
{
    int width;
    int height;
    glfwGetWindowSize(game->window, &width, &height);
    this->firstMouseInput = true;
    this->mouseLastX = width/2;
    this->mouseLastY = height/2;
    this->yaw = -90.0f;
    this->pitch = 0.0f;
    CallbackWrapper::staticInputHandler = this;
    glfwSetKeyCallback(this->game->window, CallbackWrapper::key_callback);
    glfwSetCursorPosCallback(this->game->window, CallbackWrapper::mouse_callback);  
    glfwSetScrollCallback(this->game->window, CallbackWrapper::scroll_callback);
}

void InputHandler::process_inputs() {
    // Light strength
    if(glfwGetKey(game->window, GLFW_KEY_PAGE_UP) == GLFW_PRESS) {
        if (this->game->scene.light->strength < 1) {}
            this->game->scene.light->strength += this->game->deltaTime * 0.5f;
    }
    if(glfwGetKey(game->window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS) {
        if (this->game->scene.light->strength > 0)
            this->game->scene.light->strength -= this->game->deltaTime * 0.5f;
    }
    // Camera translation
    float cameraSpeed = 2.5f * this->game->deltaTime;
    if (glfwGetKey(game->window, GLFW_KEY_W) == GLFW_PRESS)
        game->scene.camera->position += cameraSpeed * game->scene.camera->front;
    if (glfwGetKey(game->window, GLFW_KEY_S) == GLFW_PRESS)
        game->scene.camera->position -= cameraSpeed * game->scene.camera->front;
    if (glfwGetKey(game->window, GLFW_KEY_A) == GLFW_PRESS)
        game->scene.camera->position -= cameraSpeed * glm::normalize(glm::cross(game->scene.camera->front, game->scene.camera->up));
    if (glfwGetKey(game->window, GLFW_KEY_D) == GLFW_PRESS)
        game->scene.camera->position += cameraSpeed * glm::normalize(glm::cross(game->scene.camera->front, game->scene.camera->up));
    if(glfwGetKey(game->window, GLFW_KEY_P) == GLFW_PRESS)
        game->scene.camera->FOV += 20 * this->game->deltaTime;
    if(glfwGetKey(game->window, GLFW_KEY_O) == GLFW_PRESS)
        game->scene.camera->FOV -= 20 * this->game->deltaTime;
}

void InputHandler::CallbackWrapper::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    staticInputHandler->key_callback(window, key, scancode, action, mods);
}

void InputHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{   
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    // if(key == GLFW_KEY_G && action == GLFW_PRESS)
    //     game->scene.objects[0].glow();
}

void InputHandler::CallbackWrapper::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    staticInputHandler->mouse_callback(window, xpos, ypos);
}

void InputHandler::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouseInput) // initially set to true
    {
        mouseLastX = xpos;
        mouseLastY = ypos;
        firstMouseInput = false;
    }

    float xOffset = xpos - mouseLastX;
    float yOffset = mouseLastY - ypos; // reversed since y-coordinates range from bottom to top
    mouseLastX = xpos;
    mouseLastY = ypos;

    const float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    this->yaw   += xOffset;
    this->pitch += yOffset;  

    if(this->pitch > 89.0f)
        this->pitch =  89.0f;
    if(this->pitch < -89.0f)
        this->pitch = -89.0f;

    glm::vec3 direction;
    // yaw transformation
    direction.x = cos(glm::radians(this->yaw)); // Note that we convert the angle to radians first
    direction.z = sin(glm::radians(this->yaw));
    // pitch transformation
    direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    direction.y = sin(glm::radians(this->pitch));
    direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->game->scene.camera->front = glm::normalize(direction);
}

void InputHandler::CallbackWrapper::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    staticInputHandler->scroll_callback(window, xoffset, yoffset);
}

void InputHandler::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    this->game->scene.camera->FOV -= (float)yoffset;
    if (this->game->scene.camera->FOV < 1.0f)
        this->game->scene.camera->FOV = 1.0f;
    if (this->game->scene.camera->FOV > 45.0f)
        this->game->scene.camera->FOV = 45.0f; 
}
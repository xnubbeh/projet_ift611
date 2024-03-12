#include "../header/input_manager.h"

void InputManager::ProcessInput(GLFWwindow* window) {

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        InputManager::getInstance()->pressedKey[Key::W] = true;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        InputManager::getInstance()->pressedKey[Key::S] = true;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        InputManager::getInstance()->pressedKey[Key::A] = true;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        InputManager::getInstance()->pressedKey[Key::D] = true;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) {
        InputManager::getInstance()->pressedKey[Key::W] = false;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE) {
        InputManager::getInstance()->pressedKey[Key::S] = false;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) {
        InputManager::getInstance()->pressedKey[Key::A] = false;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE) {
        InputManager::getInstance()->pressedKey[Key::D] = false;
    }
}
//
// Created by Marcilio on 21/11/2024.
//

#include "Callbacks.hpp"

#include "../../debug/DebugWindow.hpp"
#include "../Camera/Camera.hpp"

namespace GameHelpers {
    void Callbacks::cameraInput_KeyCallback(GLFWwindow *window, const int key, int scancode, const int action, int mods) {
        auto *camera = static_cast<Camera *>(glfwGetWindowUserPointer(window));

        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            camera->isMouseFocused = false;
        } if (key == GLFW_KEY_F11 && action == GLFW_PRESS) {
            if(camera->isWindowMaximized) {
                camera->isWindowMaximized = false;
                camera->isMouseFocused = true;
                // glfwMaximizeWindow(window);
                glfwSetWindowMonitor(window, nullptr, 100, 100, camera->width, camera->height, GLFW_DONT_CARE);
            } else {
                camera->isWindowMaximized = true;
                camera->isMouseFocused = true;
                GLFWmonitor* monitor = glfwGetPrimaryMonitor();
                const GLFWvidmode* mode = glfwGetVideoMode(monitor);
                glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
                // glfwRestoreWindow(window);
            }
        }

        if (key > 0 && key < 1024) {
            // Movimento para frente (W) e para trás (S)
            if(action == GLFW_PRESS || action == GLFW_REPEAT) {
                camera->keyStates[key] = true;
            } else if (action == GLFW_RELEASE) {
                camera->keyStates[key] = false;
            }
        }
    }

    void Callbacks::cameraInput_MouseCallback(GLFWwindow *window, double xpos, double ypos) {
        const ImGuiIO& io = ImGui::GetIO();
        auto *camera = static_cast<Camera *>(glfwGetWindowUserPointer(window));

        if (!camera->isMouseFocused) return;

        if (camera->firstTimeMouse) {
            camera->lastMouseXPos = xpos;
            camera->firstTimeMouse = false;
            return;
        }
        // Ignore cliques do mouse se ele estiver interagindo com o ImGui
        if (io.WantCaptureMouse) {
            return; // O ImGui está capturando o mouse, ignore os callbacks
        }

        const double dx = xpos - camera->lastMouseXPos;
        const double dy = ypos - camera->lastMouseYPos;
        camera->lastMouseXPos = xpos;
        camera->lastMouseYPos = ypos;

        camera->yaw += dx * camera->mouseSensitivity;
        camera->pitch -= dy * camera->mouseSensitivity;
    }

    void Callbacks::windowFocusCallback(GLFWwindow *window, int focused) {
        ImGuiIO& io = ImGui::GetIO();

        // Ignore eventos de foco da janela se o ImGui estiver ativo
        if (io.WantCaptureKeyboard || io.WantTextInput) {
            return; // O ImGui está capturando eventos de teclado, ignore os callbacks
        }
        auto *camera = static_cast<Camera *>(glfwGetWindowUserPointer(window));
        if (focused) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            camera->isMouseFocused = true;
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            camera->isMouseFocused = false;
        }
    }

    void Callbacks::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
        ImGuiIO& io = ImGui::GetIO();

        // Ignore cliques do mouse se ele estiver interagindo com o ImGui
        if (io.WantCaptureMouse) {
            return; // O ImGui está capturando o mouse, ignore os callbacks
        }
        auto *camera = static_cast<Camera *>(glfwGetWindowUserPointer(window));
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            if(!camera->isMouseFocused) {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                camera->isMouseFocused = true;
            }
        }
    }


}

//
// Created by Marcilio on 18/11/2024.
//

#include "Camera.hpp"

#include <iostream>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <GL/glu.h>

namespace GameHelpers {
    Camera::Camera(const glm::vec3 position, int width, int height) {
        this->width = width;
        this->height = height;

        this->position = position;
        this->direction = glm::vec3(0, 0, -1);
        this->left = glm::vec3(-1, 0, 0);
        this->up = glm::vec3(0, 1, 0);

        this->isMouseFocused = true;

        this->velocity = 0;
        this->walkSpeed = 10;
        this->sprintBoost = 2.5f;
        this->mouseSensitivity = 0.15f;
        this->moveDirection = glm::vec3(0, 0, 0);
        this->lastMouseXPos = 0;
        this->lastMouseYPos = 0;
        this->firstTimeMouse = true;
        this->lastFrame = 0;

        this->deltaTime = 0;
        this->yaw = 0;
        this->pitch = 0;

        this->isWindowMaximized = false;
    }

    void Camera::update(const GLfloat currentDeltaTime) {
        deltaTime = currentDeltaTime;

        if(yaw > 360 || yaw < -360)
            yaw = 0;
        if(pitch >= 90) pitch = 89;
        if(pitch <= -90) pitch = -89.0;


        const glm::vec3 lookPosition = position + direction;
        gluLookAt(position.x, position.y, position.z,
                  lookPosition.x, lookPosition.y, lookPosition.z,
                  up.x, up.y, up.z);

        moveDirection = glm::vec3(0.0f, 0.0f, 0.0f); // Limpa o movimento a cada frame

        // Movimento para frente (W) e para trás (S)
        if (keyStates[GLFW_KEY_W])
            // Movimento apenas nos planos XZ, sem alterar Y
                moveDirection += glm::vec3(direction.x, 0.0f, direction.z) * velocity; // Move para frente
        if (keyStates[GLFW_KEY_S])
            // Movimento apenas nos planos XZ, sem alterar Y
                moveDirection -= glm::vec3(direction.x, 0.0f, direction.z) * velocity; // Move para trás

        // Movimento para a direita (D) e para a esquerda (A)
        if (keyStates[GLFW_KEY_D])
            moveDirection -= left * velocity; // Move para a direita
        if (keyStates[GLFW_KEY_A])
            moveDirection += left * velocity; // Move para a esquerda

        // Movimento para cima (Space) e para baixo (Shift)
        if (keyStates[GLFW_KEY_SPACE])
            moveDirection.y = velocity; // Move para cima
        if (keyStates[GLFW_KEY_LEFT_SHIFT])
            moveDirection.y = -velocity; // Move para baixo


        if(keyStates[GLFW_KEY_LEFT_CONTROL])
            velocity = sprintBoost * walkSpeed;
        if (!keyStates[GLFW_KEY_LEFT_CONTROL])
            velocity = walkSpeed;

        // Atualiza a posição com a movimentação constante
        this->position += moveDirection * currentDeltaTime;

        const double yawInRadians = this->yaw * std::numbers::pi / 180.0f;
        const double pitchInRadians = this->pitch * std::numbers::pi / 180.0f;

        this->direction.x = static_cast<float>(std::cos(pitchInRadians) * std::sin(yawInRadians));  // Calcula a direção X
        this->direction.y = static_cast<float>(std::sin(pitchInRadians));                            // Calcula a direção Y (pitch)
        this->direction.z = -static_cast<float>(std::cos(pitchInRadians) * std::cos(yawInRadians)); // Calcula a direção Z

        this->direction = normalize(this->direction);
        this->left = cross(this->up, this->direction);
    }

    void Camera::cameraInput_KeyCallback(GLFWwindow *window, const int key, int scancode, const int action, int mods) {
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

    void Camera::cameraInput_MouseCallback(GLFWwindow *window, double xpos, double ypos) {
        auto *camera = static_cast<Camera *>(glfwGetWindowUserPointer(window));
        //direção em x (yaw)

        if (!camera->isMouseFocused) return;

        if (camera->firstTimeMouse) {
            camera->lastMouseXPos = xpos;
            camera->firstTimeMouse = false;
            return;
        }

        const double dx = xpos - camera->lastMouseXPos;
        const double dy = ypos - camera->lastMouseYPos;
        camera->lastMouseXPos = xpos;
        camera->lastMouseYPos = ypos;

        camera->yaw += dx * camera->mouseSensitivity;
        camera->pitch -= dy * camera->mouseSensitivity;
    }

    void Camera::windowFocusCallback(GLFWwindow *window, int focused) {
        auto *camera = static_cast<Camera *>(glfwGetWindowUserPointer(window));
        if (focused) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            camera->isMouseFocused = true;
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            camera->isMouseFocused = false;
        }
    }

    void Camera::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
        auto *camera = static_cast<Camera *>(glfwGetWindowUserPointer(window));
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            if(!camera->isMouseFocused) {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                camera->isMouseFocused = true;
            }
        }
    }


    //Static function
    void Camera::updateViewport(GLFWwindow *window) {
        int windowWidth, windowHeight;
        glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
        glViewport(0, 0, windowWidth, windowHeight);

        const float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, aspectRatio, 0.1f, 500.0f);
        glMatrixMode(GL_MODELVIEW);
    }
}

//
// Created by Marcilio on 18/11/2024.
//

#ifndef CAMERA_H
#define CAMERA_H
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>


namespace GameHelpers {
    class Camera {
        public:
            explicit Camera(glm::vec3 position, int width, int height);
            // ~Camera();

            void update(GLfloat currentDeltaTime);

            static void updateViewport(GLFWwindow *window);

            bool keyStates[1024] = {false};
            bool isWindowMaximized;
            int width, height;

            GLfloat velocity;
            GLfloat walkSpeed;
            GLfloat sprintBoost;
            double lastMouseXPos;
            double lastMouseYPos;
            bool firstTimeMouse;
            GLfloat deltaTime;
            bool isMouseFocused;

            GLfloat lastFrame;

            double mouseSensitivity;
            double yaw;
            double pitch;

            glm::vec3 moveDirection{};

            glm::vec3 position{};
            glm::vec3 direction{};
            glm::vec3 left{};
            glm::vec3 up{};
    };
}


#endif //CAMERA_H

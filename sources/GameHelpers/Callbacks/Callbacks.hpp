//
// Created by Marcilio on 21/11/2024.
//

#ifndef CALLBACKS_HPP
#define CALLBACKS_HPP
#include <GLFW/glfw3.h>

namespace GameHelpers {
    class Callbacks {
        public:
            static void cameraInput_KeyCallback(GLFWwindow* window,
                int key, int scancode, int action, int mods);
            static void cameraInput_MouseCallback(GLFWwindow* window,
                double xpos, double ypos);
            static void windowFocusCallback(GLFWwindow* window, int focused);
            static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    };
}

#endif //CALLBACKS_HPP

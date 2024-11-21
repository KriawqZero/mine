//
// Created by Marcilio on 18/11/2024.
//

#include "GameHelper.hpp"

#include <GLFW/glfw3.h>

namespace Misc {
    GameHelper::GameHelper(const GLfloat fps) {
        lastTime = 0;
        deltaTime = 0;
        reactionTime = 0;
        currentTime = 0;

        fixedFPS = fps;
    }

    GLfloat GameHelper::fixFPS() {
        do {
            currentTime = static_cast<GLfloat>(glfwGetTime());
            deltaTime = currentTime - lastTime;

        } while (deltaTime < 1 / fixedFPS);
        lastTime = currentTime;
        return deltaTime;
    }

}

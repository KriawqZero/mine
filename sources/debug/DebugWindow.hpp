//
// Created by Marcilio on 22/11/2024.
//

#ifndef IMGUI_HPP
#define IMGUI_HPP
#include <imgui_impl_glfw.h>
#include <GL/gl.h>

#include "DebugHelper.hpp"

namespace Minecraft {
    class Game;
}

namespace Debug {
    class DebugWindow {
        public:
            DebugWindow(Minecraft::Game* game, GameHelpers::Camera* camera, GLFWwindow* window);
            ~DebugWindow();
            int x, z;
            void DestroyDebugTool();

            static void renderMainWindow();
            void renderFpsMSdebug() const;
            void debugWindow();
        private:
            Minecraft::Game* game;
            GameHelpers::Camera* camera;
            GLFWwindow* window;
            DebugHelper* debugHelper;
    };
}



#endif //IMGUI_HPP

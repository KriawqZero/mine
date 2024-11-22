//
// Created by Marcilio on 22/11/2024.
//

#ifndef IMGUI_HPP
#define IMGUI_HPP
#include <imgui_impl_glfw.h>
#include <GL/gl.h>

namespace Minecraft {
    class Game;
}

namespace debug {
    class DebugTool {
        public:
        DebugTool();
        int x, z;
        static void InitDebugTool(GLFWwindow* wwindow);
        static void DestroyDebugTool();

        static void renderMainWindow();
        static void renderFpsMSdebug(GLfloat deltaTime, GLfloat fps, const Minecraft::Game* game);
        void debugWindow(Minecraft::Game* game);
    };
}



#endif //IMGUI_HPP

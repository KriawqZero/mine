//
// Created by Marcilio on 17/11/2024.
//

#ifndef GAME_H
#define GAME_H
#include <atomic>
#include <string>
#include <GLFW/glfw3.h>

#include "../GameHelpers/Miscellaneous/GameHelper.hpp"
#include "../GameHelpers/Camera/Camera.hpp"
#include "../Texture/Texture.hpp"
#include "../World/Terrain/Terrain.hpp"
#include "../World/WorldGen/Chunk.hpp"

namespace Minecraft {
    class Game {
        public:
            Game(int width, int height, GLfloat fps,
                const std::string &title, const std::string &version);
            // ~Game();
            void debugConsole();
            int run();
            void spawnBlock(GLfloat x, GLfloat y, GLfloat z);
            //Camera* getCamera() {return &camera; }
            void getObjects() const;
            void getPosition() const;

        private:
            std::atomic<bool> running;
            int width, height;
            std::string title, version;

            GLFWwindow* window;
            GameHelpers::Camera camera;

            Misc::GameHelper gameHelper;
            GLfloat deltaTime;

            enum {BRICK, PAINTED, WOOD, GRASS};
            Texture texture[4];
            std::vector<World::Primitive*> objects;
            std::vector<World::Chunk*> chunks;

            GLfloat fpsCount = 0.0f;
            GLfloat fps = 0.0f;
            GLfloat lastFpsTime = 0.0f;

            float angle = 0.0f;

            void init();
            void update();
    };
}



#endif //GAME_H

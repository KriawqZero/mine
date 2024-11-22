//
// Created by Marcilio on 17/11/2024.
//

#ifndef GAME_H
#define GAME_H
#include <atomic>
#include <string>
#include <GLFW/glfw3.h>

#include "../debug/DebugTool.hpp"
#include "../GameHelpers/Miscellaneous/GameHelper.hpp"
#include "../GameHelpers/Camera/Camera.hpp"
#include "../Texture/Texture.hpp"
#include "../World/WorldGen/Chunk.hpp"

namespace Minecraft {
    class Game {
        public:
            Game(int width, int height, GLfloat fps,
                const std::string &title, const std::string &version);
            // ~Game();
            //void debugConsole();
            int run();
            void spawnBlock(GLfloat x, GLfloat y, GLfloat z);
            //Camera* getCamera() {return &camera; }
            void getObjects() const;

            [[nodiscard]] glm::vec3 getPosition() const;
            [[nodiscard]] std::string getChunkData() const;
            [[nodiscard]] std::string getChunksPos() const;
            void genNewChunk(int x, int y);
            debug::DebugTool debugTool;

        private:
            std::atomic<bool> running;
            int width, height;
            std::string title, version;

            GLFWwindow* window;
            GameHelpers::Camera camera;

            Misc::GameHelper gameHelper;
            GLfloat deltaTime;

            std::vector<World::Primitive*> objects;
            std::vector<World::Chunk*> chunks;

            GLfloat fpsCount = 0.0f;
            GLfloat fps = 0.0f;
            GLfloat lastFpsTime = 0.0f;

            float angle = 0.0f;

            void init();
            void update();
            void finish();
    };
}



#endif //GAME_H

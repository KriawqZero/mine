//
// Created by Marcilio on 22/11/2024.
//

#ifndef DEBUGCALLBACKS_HPP
#define DEBUGCALLBACKS_HPP
#include <string>
#include <GL/gl.h>
#include <glm/vec3.hpp>

namespace GameHelpers {
    class Camera;
}

namespace Minecraft {
    class Game;
}

namespace Debug {
    class DebugHelper {
        public:
            DebugHelper(Minecraft::Game* gameInstance, GameHelpers::Camera* camera);
            ~DebugHelper();

            void spawnBlock(GLfloat x, GLfloat y, GLfloat z) const;
            //Camera* getCamera() {return &camera; }
            void getObjects() const;

            [[nodiscard]] glm::vec3 getPosition() const;
            [[nodiscard]] std::string getChunkData() const;
            [[nodiscard]] std::string getChunksPos() const;
            void genNewChunk(int x, int y) const;

        private:
            Minecraft::Game* gameInstance;
            GameHelpers::Camera* camera;
    };
}



#endif //DEBUGCALLBACKS_HPP

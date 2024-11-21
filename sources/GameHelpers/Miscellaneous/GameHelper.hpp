//
// Created by Marcilio on 18/11/2024.
//

#ifndef GAMEHELPER_H
#define GAMEHELPER_H
#include <GL/gl.h>


namespace Misc {
    class GameHelper {
        public:
            explicit GameHelper(GLfloat fps);

            GLfloat fixFPS();

        private:
            GLfloat deltaTime;
            GLfloat reactionTime;
            GLfloat fixedFPS;
            float lastTime;
            float currentTime;
    };
}


#endif //GAMEHELPER_H

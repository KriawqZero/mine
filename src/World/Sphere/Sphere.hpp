//
// Created by Marcilio on 18/11/2024.
//

#ifndef SPHERE_H
#define SPHERE_H
#include <GL/gl.h>


namespace World {
    class Sphere {
    public:
        static void drawSphere(GLfloat radius, GLfloat nStacks, GLfloat nSectors);
    };
}


#endif //SPHERE_H

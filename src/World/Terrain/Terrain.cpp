//
// Created by Marcilio on 21/11/2024.
//

#include "Terrain.hpp"
#include <GL/gl.h>

#include "../../debug/colors.h"

namespace World {
    Terrain::Terrain(const glm::vec3 _pos): Primitive(_pos) {
        //primitiveID = glGenLists(1);
    }

    Terrain::~Terrain() = default;

    void Terrain::BuildTerrain(const GLfloat size) const {
        glNewList(primitiveID, GL_COMPILE);
            glColor3fv(cinza);
            glBegin(GL_LINES);
            for (GLfloat i = -size; i < size; i++) {
                glVertex3f(i, worldPosition.y, -size);
                glVertex3f(i, worldPosition.y, size);

                glVertex3f(-size, worldPosition.y, i);
                glVertex3f(size, worldPosition.y, i);
            }
            glEnd();
            glColor3fv(branco);
        glEndList();
    }
}

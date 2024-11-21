//
// Created by Marcilio on 21/11/2024.
//

#include "Primitive.hpp"

#include <GL/gl.h>

namespace World {
    Primitive::Primitive(const glm::vec3 worldPosition):
    worldPosition(worldPosition) {
        primitiveID = glGenLists(1);
    }

    Primitive::~Primitive() {
        glDeleteLists(primitiveID, 1);
    }

    void Primitive::setPosition(const glm::vec3 newPosition) {
        this->worldPosition = newPosition;
    }

    void Primitive::Render() const {
        glPushMatrix();
            glTranslatef(this->worldPosition.x, this->worldPosition.y, this->worldPosition.z);
            glCallList(primitiveID);
        glPopMatrix();
    }

    std::string Primitive::getPosition() const {
        return "ID: " + std::to_string(primitiveID) +
               ". worldPosition: X: " + std::to_string(worldPosition.x) +
               " Y: " + std::to_string(worldPosition.y) +
               " Z: " + std::to_string(worldPosition.z);
    }

}

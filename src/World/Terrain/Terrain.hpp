//
// Created by Marcilio on 21/11/2024.
//

#ifndef TERRAIN_HPP
#define TERRAIN_HPP
#include <GL/gl.h>

#include "../Primitive/Primitive.hpp"

namespace World {
    class Terrain: public Primitive{
        public:
            explicit Terrain(glm::vec3 _pos);
            ~Terrain();
            void BuildTerrain(GLfloat size) const;

    };
}

#endif //TERRAIN_HPP

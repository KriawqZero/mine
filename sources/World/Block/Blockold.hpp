//
// Created by Marcilio on 17/11/2024.
//

#ifndef BLOCK_H
#define BLOCK_H

#pragma once
#include <memory>
#include <unordered_map>
#include <GL/gl.h>
#include <glm/vec3.hpp>

#include "../../Texture/Texture.hpp"
#include "../Primitive/Primitive.hpp"

namespace World {
    class Blockold: public Primitive {
        public:
        enum BLOCKTYPE {GRASS, DIRT, STONE, BEDROCK};

        explicit Blockold(glm::vec3 _pos, BLOCKTYPE _type);
        ~Blockold();

        void makeBlock() const;

        private:
        BLOCKTYPE type;
        GLuint primitiveID;

        enum CubeFace {TOP, BOTTOM, BACK, FRONT, LEFT, RIGHT};

        // Cache de texturas compartilhadas
        static std::unordered_map<BLOCKTYPE, std::shared_ptr<Texture>> textureCache;

        // Métodos auxiliares
        static void drawFace(glm::vec3 pv1, glm::vec3 pv2, glm::vec3 pv3, glm::vec3 pv4, CubeFace face);
        static std::shared_ptr<Texture> getTexture(BLOCKTYPE type);

        static void drawBlock(float size, BLOCKTYPE type);
    };
}


#endif //BLOCK_H

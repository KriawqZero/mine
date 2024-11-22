
#ifndef BLOCK_H
#define BLOCK_H

#pragma once
#include <memory>
#include <unordered_map>
#include <GL/gl.h>
#include <glm/vec3.hpp>

#include "../../Texture/Texture.hpp"
#include "../Primitive/Primitive.hpp"
#include "../BlockMap/BlockMap.hpp"

namespace World {
    class Block: public Primitive {
        public:
            enum BLOCKTYPE {GRASS, DIRT, STONE, BEDROCK};

            explicit Block(glm::vec3 _pos, BLOCKTYPE _type);
            ~Block();

            void makeBlock(const BlockMap& blockMap);

        private:
            BLOCKTYPE type;
            GLuint primitiveID;

            enum CubeFace {TOP, BOTTOM, BACK, FRONT, LEFT, RIGHT};

            // Cache de texturas compartilhadas
            static std::unordered_map<BLOCKTYPE, std::shared_ptr<Texture>> textureCache;

            // Métodos auxiliares
            static void drawFace(glm::vec3 pv1, glm::vec3 pv2, glm::vec3 pv3, glm::vec3 pv4, CubeFace face);
            static std::shared_ptr<Texture> getTexture(BLOCKTYPE type);

            void drawBlock (float size, BLOCKTYPE type, BlockMap blockMap) const;
    };
}


#endif //BLOCK_H

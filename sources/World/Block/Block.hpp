//
// Created by Marcilio on 17/11/2024.
//

#ifndef BLOCK_H
#define BLOCK_H

#pragma once
#include <glm/vec3.hpp>

#include "../../Texture/Texture.hpp"
#include "../Primitive/Primitive.hpp"

namespace World {
    class Block: public Primitive {
    public:
        enum BLOCKTYPE {GRASS, DIRT, STONE, BEDROCK};
        explicit Block(glm::vec3 _pos, BLOCKTYPE _type);
        ~Block();
        void makeBlock() const;

        static void drawBlock(float size, BLOCKTYPE type);
        static Texture* getTexture(BLOCKTYPE type);

    private:
        BLOCKTYPE type;
        enum CubeFace {TOP, BOTTOM, BACK, FRONT, LEFT, RIGHT};

        static void drawFace(glm::vec3 pv1, glm::vec3 pv2, glm::vec3 pv3, glm::vec3 pv4,
            CubeFace face);

    };
}


#endif //BLOCK_H

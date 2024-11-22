//
// Created by Marcilio on 17/11/2024.
//

#include "Block.hpp"

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "../../Texture/Texture.hpp"

namespace World {
    Block::Block(const glm::vec3 _pos, const BLOCKTYPE _type): Primitive(_pos) {
        primitiveID = glGenLists(1);
        type = _type;
    }

    Block::~Block() = default;

    void Block::makeBlock() const {
        glNewList(primitiveID, GL_COMPILE);
            drawBlock(1, type);
        glEndList();
    }

    void Block::drawFace(const glm::vec3 pv1, const glm::vec3 pv2, const glm::vec3 pv3,
                         const glm::vec3 pv4, const CubeFace face) {
    glBegin(GL_TRIANGLES);
        // Definindo coordenadas de textura com base na face
        glTexCoord2f(0.0f, 0.0f); glVertex3fv(&pv1.x);
        glTexCoord2f(1.0f, 0.0f); glVertex3fv(&pv2.x);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv(&pv3.x);

        glTexCoord2f(0.0f, 0.0f); glVertex3fv(&pv1.x);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv(&pv3.x);
        glTexCoord2f(0.0f, 1.0f); glVertex3fv(&pv4.x);
    glEnd();
}


    void Block::drawBlock(float size,BLOCKTYPE type) {
        float diameter = size / 2;
        float d = diameter;

        glm::vec3 v1(-d,  d, d);
        glm::vec3 v2(-d, -d, d);
        glm::vec3 v3( d, -d, d);
        glm::vec3 v4( d,  d, d);

        glm::vec3 v5( d,  d,-d);
        glm::vec3 v6( d, -d,-d);
        glm::vec3 v7(-d, -d,-d);
        glm::vec3 v8(-d,  d,-d);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        auto* blockTexture = getTexture(type);
        if(blockTexture != nullptr) blockTexture->bind();

        drawFace(v1, v2, v3, v4, FRONT); //frente
        drawFace(v4, v3, v6, v5, RIGHT); //direita
        drawFace(v5, v8, v7, v6, BACK); //atrás
        drawFace(v1, v8, v7, v2, LEFT); //esquerda

        drawFace(v1, v4, v5, v8, TOP); //cima
        drawFace(v2, v7,v6,v3, BOTTOM); //baixo
        Texture::unbind();
    }

    Texture* Block::getTexture(const BLOCKTYPE type) {
        auto* texture = new Texture;
        switch (type) {
            case GRASS:
                texture->loadTexture("../resources/images/grass_block_top.png");
                break;
            case DIRT:
                texture->loadTexture("../resources/images/dirt.png");
                break;
            case STONE:
                texture->loadTexture("../resources/images/stone.png");
                break;
            case BEDROCK:
                texture->loadTexture("../resources/images/bedrock.png");
                break;
            default:
                std::cerr << "Unknown block type" << std::endl;
                texture = nullptr;
       }
        return texture;
   }
}

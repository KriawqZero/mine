#include "Block.hpp"
#include <GL/gl.h>
#include <unordered_map>
#include <memory>
#include <iostream>
#include "../../Texture/Texture.hpp"
#include "../BlockMap/BlockMap.hpp"

namespace World {
    // Definição da variável estática
    std::unordered_map<Block::BLOCKTYPE, std::shared_ptr<Texture>> Block::textureCache;

    Block::Block(const glm::vec3 _pos, const BLOCKTYPE _type): Primitive(_pos) {
        primitiveID = glGenLists(1);
        type = _type;
    }

    Block::~Block() {
        // Liberação da lista do display
        glDeleteLists(primitiveID, 1);
    }

    void Block::makeBlock(const BlockMap& blockMap) {
        glNewList(primitiveID, GL_COMPILE);
            drawBlock(1.0f, type, blockMap); // Usa o tipo do bloco e o map de blocos
        glEndList();
    }

    void Block::drawFace(const glm::vec3 pv1,
                         const glm::vec3 pv2,
                         const glm::vec3 pv3,
                         const glm::vec3 pv4,
                         CubeFace face) {
        glBegin(GL_TRIANGLES);
            // Primeiro triângulo
            glTexCoord2f(0.0f, 0.0f); glVertex3fv(&pv1.x);
            glTexCoord2f(1.0f, 0.0f); glVertex3fv(&pv2.x);
            glTexCoord2f(1.0f, 1.0f); glVertex3fv(&pv3.x);

            // Segundo triângulo
            glTexCoord2f(0.0f, 0.0f); glVertex3fv(&pv1.x);
            glTexCoord2f(1.0f, 1.0f); glVertex3fv(&pv3.x);
            glTexCoord2f(0.0f, 1.0f); glVertex3fv(&pv4.x);
        glEnd();
    }
    void Block::drawBlock(float size, BLOCKTYPE type, const BlockMap blockMap) const{
        float d = size / 2.0f;

        glm::vec3 v1(-d,  d,  d);
        glm::vec3 v2(-d, -d,  d);
        glm::vec3 v3( d, -d,  d);
        glm::vec3 v4( d,  d,  d);

        glm::vec3 v5( d,  d, -d);
        glm::vec3 v6( d, -d, -d);
        glm::vec3 v7(-d, -d, -d);
        glm::vec3 v8(-d,  d, -d);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // Obter textura associada ao tipo do bloco
        auto blockTexture = getTexture(type);
        if (blockTexture != nullptr)
            blockTexture->bind();

        // Verificar se há blocos ao lado antes de desenhar as faces
        if (!blockMap.hasBlock(worldPosition + glm::vec3(0, 0, 1))) // Frente
            drawFace(v1, v2, v3, v4, FRONT);

        if (!blockMap.hasBlock(worldPosition + glm::vec3(1, 0, 0))) // Direita
            drawFace(v4, v3, v6, v5, RIGHT);

        if (!blockMap.hasBlock(worldPosition + glm::vec3(0, 0, -1))) // Trás
            drawFace(v5, v8, v7, v6, BACK);

        if (!blockMap.hasBlock(worldPosition + glm::vec3(-1, 0, 0))) // Esquerda
            drawFace(v1, v8, v7, v2, LEFT);

        if (!blockMap.hasBlock(worldPosition + glm::vec3(0, 1, 0))) // Cima
            drawFace(v1, v4, v5, v8, TOP);

        if (!blockMap.hasBlock(worldPosition + glm::vec3(0, -1, 0))) // Baixo
            drawFace(v2, v7, v6, v3, BOTTOM);

        Texture::unbind(); // Desvincular textura
    }

    std::shared_ptr<Texture> Block::getTexture(const BLOCKTYPE type) {
        // Verificar se a textura já existe no cache
        if (!textureCache.contains(type)) {
            const auto texture = std::make_shared<Texture>();
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
                    return nullptr;
            }
            textureCache[type] = texture;
        }
        return textureCache[type];
    }
}

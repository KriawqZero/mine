#include "Blockold.hpp"
#include <GL/gl.h>
#include "../../Texture/Texture.hpp"
#include <unordered_map>
#include <memory>
#include <iostream>

namespace World {
    // Definição da variável estática
    std::unordered_map<Blockold::BLOCKTYPE, std::shared_ptr<Texture>> Blockold::textureCache;

    Blockold::Blockold(const glm::vec3 _pos, const BLOCKTYPE _type): Primitive(_pos) {
        primitiveID = glGenLists(1);
        type = _type;
    }

    Blockold::~Blockold() {
        // Liberação da lista do display
        glDeleteLists(primitiveID, 1);
    }

    void Blockold::makeBlock() const {
        glNewList(primitiveID, GL_COMPILE);
            drawBlock(1.0f, type); // Usa o tipo do bloco
        glEndList();
    }

    void Blockold::drawFace(const glm::vec3 pv1, const glm::vec3 pv2, const glm::vec3 pv3, const glm::vec3 pv4,
        CubeFace face) {
        glBegin(GL_TRIANGLES);
            glTexCoord2f(0.0f, 0.0f); glVertex3fv(&pv1.x);
            glTexCoord2f(1.0f, 0.0f); glVertex3fv(&pv2.x);
            glTexCoord2f(1.0f, 1.0f); glVertex3fv(&pv3.x);

            glTexCoord2f(0.0f, 0.0f); glVertex3fv(&pv1.x);
            glTexCoord2f(1.0f, 1.0f); glVertex3fv(&pv3.x);
            glTexCoord2f(0.0f, 1.0f); glVertex3fv(&pv4.x);
        glEnd();
    }

    void Blockold::drawBlock(float size, BLOCKTYPE type) {
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

        drawFace(v1, v2, v3, v4, FRONT);  // Frente
        drawFace(v4, v3, v6, v5, RIGHT); // Direita
        drawFace(v5, v8, v7, v6, BACK);  // Trás
        drawFace(v1, v8, v7, v2, LEFT);  // Esquerda
        drawFace(v1, v4, v5, v8, TOP);   // Cima
        drawFace(v2, v7, v6, v3, BOTTOM); // Baixo

        Texture::unbind(); // Desvincular textura
    }

    std::shared_ptr<Texture> Blockold::getTexture(const BLOCKTYPE type) {
        std::cout << textureCache;
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

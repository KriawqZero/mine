//
// Created by Marcilio on 21/11/2024.
//

#include "Chunk.hpp"

#include <bits/fs_fwd.h>
namespace World {
    Chunk::Chunk(const int x, const int z) {
        size = 16; // Tamanho fixo da chunk
        height = 4; // Altura em blocos

        // Calcula as coordenadas da chunk (inteiras)
        this->x = x / size;
        this->z = z / size;
    }

    Chunk::~Chunk() = default;

    void Chunk::generateChunk() {
        for (int y = 0; y < height; y++) {
            genBlockLine(y);
        }
    }

    void Chunk::displayChunk() const {
        for (int i = 0; i < blocks.size(); i++) {
            blocks[i].Render();
        }
    }

    std::string Chunk::getBlocks() const {
        std::string str = " \n";
        for (auto& block : blocks) {
            str.append(block.getPosition());
            str.append("\n ");
        }
        return str;
    }

    glm::vec3 Chunk::getPosition() const {
        return {x, 0, z};
    }

    void Chunk::genBlockLine(const int y) {
        // Coordenadas iniciais no mundo
        const int startX = this->x * size;
        const int startZ = this->z * size;

        // Coordenadas finais no mundo
        const int endX = startX + size;
        const int endZ = startZ + size;

        for (int i = startX; i < endX; i++) {
            for (int j = startZ; j < endZ; j++) {
                // Cria e adiciona o bloco à lista
                const auto temp_block = new Block(glm::vec3(i, y, j), Block::GRASS);
                temp_block->makeBlock();
                blocks.push_back(*temp_block);
            }
        }
    }
}

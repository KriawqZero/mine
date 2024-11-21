//
// Created by Marcilio on 21/11/2024.
//

#include "Chunk.hpp"

namespace World {
    Chunk::Chunk() {
        size = 8;
        height = 4;
    }

    Chunk::~Chunk() = default;

    void Chunk::generateChunk() {
        for (int y = 0; y < height; y++) {
            genBlockLine(y);
        }
    }

    void Chunk::displayChunk() const {
        for(auto& block : blocks) {
            block.Render();
        }
    }

    // ReSharper disable once CppDFAConstantFunctionResult
    std::string Chunk::getBlocks() const {
        std::string str = " \n";
        for (auto & block : blocks) {
            //str.append(" \n");
            str.append(block.getPosition());
            str.append("\n ");
        }
        return str;
    }

    void Chunk::genBlockLine(const int y) {
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                //std::cout << "Criando bloco em: " << i << ", " << y << ", " << j << std::endl;
                const auto* temp_block = new Block(glm::vec3(i, y, j), Block::STONE);
                temp_block->makeBlock();
                blocks.push_back(*temp_block);
            }
        }
    }
}

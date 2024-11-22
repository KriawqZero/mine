//
// Created by Marcilio on 21/11/2024.
//

#include "Chunk.hpp"

#include <bits/fs_fwd.h>

namespace World {
    Chunk::Chunk() {
        size = 2;
        height = 3;
    }

    Chunk::~Chunk() = default;

    void Chunk::generateChunk() {
        for (int y = 0; y < height; y++) {
            genBlockLine(y);
        }
    }

    void Chunk::displayChunk() const {
        for(int i = 0; i < blocks.size(); i++) {
            blocks[i].Render();
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
                const auto* temp_block = new Block(glm::vec3(i, y, j), Block::GRASS);
                temp_block->makeBlock();
                blocks.push_back(*temp_block);
            }
        }
    }
}

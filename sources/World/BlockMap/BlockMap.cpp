//
// Created by Marcilio on 22/11/2024.
//
#include "BlockMap.hpp"
#include <iostream>

#include "../Block/Block.hpp"

namespace World {

    void BlockMap::addBlock(const glm::vec3& position, Block::BLOCKTYPE _type) {
        if (!hasBlock(position)) {
            blockMap[position] = std::make_unique<Block>(position, _type);
        } else {
            std::cout << "Bloco já existe na posição " << position.x << ", " << position.y << ", " << position.z << std::endl;
        }
    }

    void BlockMap::removeBlock(const glm::vec3& position) {
        if (hasBlock(position)) {
            blockMap.erase(position);
        } else {
            std::cout << "Nenhum bloco encontrado na posição " << position.x << ", " << position.y << ", " << position.z << std::endl;
        }
    }

    bool BlockMap::hasBlock(const glm::vec3& position) const {
        return blockMap.contains(position);
    }

    Block* BlockMap::getBlock(const glm::vec3& position) const {
        if (hasBlock(position)) return blockMap.at(position).get();
        return nullptr;
    }
}

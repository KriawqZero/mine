//
// Created by Marcilio on 22/11/2024.
//

#ifndef BLOCKMAP_HPP
#define BLOCKMAP_HPP
#include <unordered_map>
#include <glm/vec3.hpp>

#include "../Block/Block.hpp"

namespace World {
    // Usando glm::vec3 como chave, que representa as coordenadas no mundo.
    struct BlockHash {
        std::size_t operator()(const glm::vec3& v) const {
            return std::hash<int>()(static_cast<int>(v.x)) ^ std::hash<int>()(static_cast<int>(v.y)) ^ std::hash<int>()(static_cast<int>(v.z));
        }
    };

    class BlockMap {
        public:
        BlockMap() = default;
        ~BlockMap() = default;

        // Adiciona um bloco à posição especificada
        void addBlock(const glm::vec3& position, Block::BLOCKTYPE _type);

        // Remove um bloco da posição especificada
        void removeBlock(const glm::vec3& position);

        // Verifica se há um bloco na posição especificada
        bool hasBlock(const glm::vec3& position) const;

        // Retorna um ponteiro para o bloco na posição especificada
        Block* getBlock(const glm::vec3& position) const;

        private:
        // Mapa que relaciona uma posição a um bloco
        std::unordered_map<glm::vec3, std::unique_ptr<Block>, BlockHash> blockMap;
    };

}


#endif //BLOCKMAP_HPP

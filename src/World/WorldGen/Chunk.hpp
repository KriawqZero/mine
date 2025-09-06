//
// Created by Marcilio on 21/11/2024.
//

#ifndef CHUNK_HPP
#define CHUNK_HPP
#include <glm/detail/type_vec1.hpp>

#include "../Block/Block.hpp"

namespace World {
    class Chunk {
        public:
            Chunk(int x, int z);
            ~Chunk();
            std::vector<Block> blocks;
            void generateChunk();
            void displayChunk() const;

            [[nodiscard]] std::string getBlocks() const;
            [[nodiscard]] glm::vec3 getPosition() const;

        private:
            int size, height;
            int x, z;

            void genBlockLine(int y);
    };
}

#endif //CHUNK_HPP

//
// Created by Marcilio on 21/11/2024.
//

#ifndef CHUNK_HPP
#define CHUNK_HPP
#include "../Block/Block.hpp"

namespace World {
    class Chunk {
        public:
            Chunk();
            ~Chunk();
            std::vector<Block> blocks;
            void generateChunk();
            void displayChunk() const;

            std::string getBlocks() const;

        private:
            int size, height;

            void genBlockLine(int y);
    };
}

#endif //CHUNK_HPP

//
// Created by Marcilio on 22/11/2024.
//

#include "DebugHelper.hpp"

#include "../Game/Game.hpp"
#include "../World/Block/Block.hpp"

namespace Debug {
    DebugHelper::DebugHelper(Minecraft::Game *gameInstance, GameHelpers::Camera* camera) {
        this->gameInstance = gameInstance;
        this->camera = camera;
    }

    DebugHelper::~DebugHelper() = default;

    // void Game::debugConsole() {
    //     std::string command;
    //     if(running) std::cout << ">> ";
    //     while (running) {
    //         //if(!std::getline(std::cin, command)) break;
    //         if(!running) break;
    //
    //         std::getline(std::cin, command);
    //         std::istringstream iss(command);
    //         std::string cmd;
    //         iss >> cmd;
    //
    //         if (cmd == "exit") {
    //             running = false; // Sinaliza para encerrar o programa
    //         } else if (cmd == "show_fps") {
    //             std::cout << "FPS: (mock value)" << std::endl;
    //         } else if (cmd == "spawn_block") {
    //             GLfloat x, y, z;
    //             if (iss >> x >> y >> z) {
    //                 spawnBlock(x, y, z);
    //             } else {
    //                 std::cout << "<<Erro: comando inválido para spawn_block. Formato esperado: spawn_block x y z" << std::endl;
    //             }
    //         } else if (cmd == "show_objects") {
    //             getObjects();
    //         } else if (cmd == "get_position") {
    //             //getPosition();
    //         } else if (cmd == "get_chunk_data") {
    //             //getChunkData();
    //         } else {
    //             std::cout << "Comando desconhecido: " << command << std::endl;
    //         }
    //
    //         std::cout << ">> ";
    //     }
    // }

    void DebugHelper::spawnBlock(const GLfloat x, const GLfloat y, const GLfloat z) const {
        // Criação do bloco na posição (x, y, z)
        std::cout << "Criando bloco em: " << x << ", " << y << ", " << z << std::endl;

        // Cria o bloco na posição fornecida
        auto* newBlock = new World::Block(glm::vec3(x, y, z), World::Block::STONE);
        newBlock->makeBlock();

        // Se você precisar adicionar o bloco à lista de blocos ou chunks
        gameInstance->objects.push_back(newBlock);
    }

    void DebugHelper::getObjects() const {
        std::string objectsList;
        for (const auto object : gameInstance->objects) {
            objectsList.append(object->getPosition());
        }
        std::cout << objectsList << std::endl;
    }

    glm::vec3 DebugHelper::getPosition() const {
        const float x = camera->position.x;
        const float y = camera->position.y;
        const float z = camera->position.z;

        return {x, y, z};
    }

    std::string DebugHelper::getChunkData() const {
        std::string chunkData;
        for (const auto chunk : gameInstance->chunks) {
            chunkData.append(chunk->getBlocks() + "\n");
        }
        return chunkData;
    }

    std::string DebugHelper::getChunksPos() const {
        std::string chunksPos;
        for(const auto* chunk : gameInstance->chunks) {
            const int x = static_cast<int>(chunk->getPosition().x);
            const int z = static_cast<int>(chunk->getPosition().z);
            chunksPos.append("Chunk X: " + std::to_string(x) + ", Z: " + std::to_string(z) + "\n");
        }
        return chunksPos;
    }

    void DebugHelper::genNewChunk(int x, int z) const {
        x *= 16;
        z *= 16;
        auto* chunk = new World::Chunk(x, z);
        chunk->generateChunk();

        gameInstance->chunks.push_back(chunk);
    }

}

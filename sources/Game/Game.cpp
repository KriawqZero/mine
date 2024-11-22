//
// Created by Marcilio on 17/11/2024.
//
#include "Game.hpp"

#include <iostream>
#include <ostream>
#include <sstream>
#include <thread>

#include "imgui_impl_opengl3.h"
#include "imgui.h"
#include "../debug/DebugTool.hpp"

#include "GLFW/glfw3.h"
#include "../GameHelpers/Miscellaneous/GameHelper.hpp"
#include "../GameHelpers/Camera/Camera.hpp"
#include "../World/Block/Blockold.hpp"
#include "../World/Terrain/Terrain.hpp"

namespace Minecraft
{
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

    void Game::spawnBlock(GLfloat x, GLfloat y, GLfloat z) {
        // Criação do bloco na posição (x, y, z)
        std::cout << "Criando bloco em: " << x << ", " << y << ", " << z << std::endl;

        // Cria o bloco na posição fornecida
        auto* newBlock = new World::Blockold(glm::vec3(x, y, z), World::Blockold::STONE);
        newBlock->makeBlock();

        // Se você precisar adicionar o bloco à lista de blocos ou chunks
        objects.push_back(newBlock);
    }

    void Game::getObjects() const {
        std::string objectsList;
        for (const auto object : objects) {
            objectsList.append(object->getPosition());
        }
        std::cout << objectsList << std::endl;
    }

    glm::vec3 Game::getPosition() const {
        const float x = camera.position.x;
        const float y = camera.position.y;
        const float z = camera.position.z;

        return {x, y, z};
    }

    std::string Game::getChunkData() const {
        std::string chunkData;
        for (const auto chunk : chunks) {
            chunkData.append(chunk->getBlocks() + "\n");
        }
        return chunkData;
    }

    std::string Game::getChunksPos() const {
        std::string chunksPos;
        for(auto* chunk : chunks) {
            const int x = static_cast<int>(chunk->getPosition().x);
            const int z = static_cast<int>(chunk->getPosition().z);
            chunksPos.append("Chunk X: " + std::to_string(x) + ", Z: " + std::to_string(z) + "\n");
        }
        return chunksPos;
    }

    void Game::genNewChunk(int x, int z) {
        x *= 16;
        z *= 16;
        auto* chunk = new World::Chunk(x, z);
        chunk->generateChunk();

        chunks.push_back(chunk);
    }

    Game::Game(const int width,
               const int height,
               const GLfloat fps,
               const std::string &title,
               const std::string &version):
    camera(glm::vec3(0.0f, 0.0f, 50.0f), width, height),
    gameHelper(fps){
        this->height = height;
        this->width = width;
        this->window = nullptr;
        this->title = title;
        this->version = version;

        this->deltaTime = 0;
    }

    void Game::init() {
        glLoadIdentity();

        glClearColor(0.0f, 0.0, 0.0f, 1.0f);
        //glEnable(GL_CULL_FACE);
        //glCullFace(GL_CCW);
        auto* terrain = new World::Terrain(glm::vec3(0.0f, -3.0f, 0.0f));
        terrain->BuildTerrain(500);
        objects.push_back(terrain);

        constexpr int worldSize = 32;
        for (int x = 0; x < worldSize / 16; x++) {
            for (int z = 0; z < worldSize / 16; z++) {
                auto* chunk = new World::Chunk(x * 16, z * 16);
                chunk->generateChunk();
                chunks.push_back(chunk);
            }
        }

        //std::cout << chunk->getBlocks() << std::endl;
        debug::DebugTool::InitDebugTool(window);
    }

    void Game::update() {
        GameHelpers::Camera::updateViewport(window);
        glLoadIdentity();
        camera.update(deltaTime);

        debug::DebugTool::renderMainWindow();

        for(const auto* object : objects) {
            object->Render();
        }

        for(const auto* chunk: chunks) {
            chunk->displayChunk();
        }

        // Contador de FPS
        fpsCount++;

        // Atualiza o FPS a cada 1 segundo
        if (const auto currentTime = static_cast<GLfloat>(glfwGetTime());
            currentTime - lastFpsTime >= 1.0f) {
            fps = fpsCount;  // O número de quadros no último segundo
            fpsCount = 0;  // Reseta o contador
            lastFpsTime = currentTime;
            //std::cout << "FPS: " << fps << std::endl;  // Exibe no console
        }

        debug::DebugTool::renderFpsMSdebug(deltaTime, fps, this);
        debugTool.debugWindow(this);

        const float angularVelocity = 60 * deltaTime;
        angle += angularVelocity;// Draw ImGui UI

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    void Game::finish() { // NOLINT(*-convert-member-functions-to-static)
        //glDisable(GL_CULL_FACE);
        debug::DebugTool::DestroyDebugTool();
    }


    int Game::run() {
        running = true;
        if (!glfwInit()) { running = false; return -1; }
        window = glfwCreateWindow(width, height, (title + " " + version)
            .c_str(), nullptr, nullptr);
        if (!window) { glfwTerminate(); running = false; return -1;  }

        glfwMakeContextCurrent(window);
        glfwSetWindowUserPointer(window, &camera);

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, GameHelpers::Camera::cameraInput_MouseCallback);
        glfwSetKeyCallback(window, GameHelpers::Camera::cameraInput_KeyCallback);
        glfwSetWindowFocusCallback(window, GameHelpers::Camera::windowFocusCallback);
        glfwSetMouseButtonCallback(window, GameHelpers::Camera::mouseButtonCallback);

        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
        glShadeModel(GL_SMOOTH);

        init();

        while (!glfwWindowShouldClose(window) && running) {
            glfwPollEvents();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            deltaTime = gameHelper.fixFPS();

            update();

            glfwSwapBuffers(window);
        }
        finish();
        running = false;
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_DEPTH_TEST);
        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
    }

}

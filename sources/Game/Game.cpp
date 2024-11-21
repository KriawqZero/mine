//
// Created by Marcilio on 17/11/2024.
//
#include "Game.hpp"

#include <iostream>
#include <ostream>
#include <sstream>
#include <thread>

#include "GLFW/glfw3.h"
#include "../GameHelpers/Miscellaneous/GameHelper.hpp"
#include "../GameHelpers/Camera/Camera.hpp"
#include "../World/Block/Block.hpp"
#include "../World/Sphere/Sphere.hpp"

namespace Minecraft
{
    void Game::debugConsole() {
        std::string command;
        while (running) {
            std::getline(std::cin, command);
            std::istringstream iss(command);
            std::string cmd;
            iss >> cmd;

            if (cmd == "exit") {
                running = false; // Sinaliza para encerrar o programa
            } else if (cmd == "show_fps") {
                std::cout << "FPS: 60 (mock value)" << std::endl;
            } else if (cmd == "spawn_block") {
                GLfloat x, y, z;
                if (iss >> x >> y >> z) {
                    spawnBlock(x, y, z);
                } else {
                    std::cout << "Erro: comando inválido para spawn_block. Formato esperado: spawn_block x y z" << std::endl;
                }
            } else if (cmd == "show_objects") {
                getObjects();
            } else if (cmd == "get_position") {
                getPosition();
            } else {
                std::cout << "Comando desconhecido: " << command << std::endl;
            }
        }
    }

    void Game::spawnBlock(GLfloat x, GLfloat y, GLfloat z) {
        // Criação do bloco na posição (x, y, z)
        std::cout << "Criando bloco em: " << x << ", " << y << ", " << z << std::endl;

        // Cria o bloco na posição fornecida
        auto* newBlock = new World::Block(glm::vec3(x, y, z), World::Block::STONE);
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

    void Game::getPosition() const {
        const float x = camera.position.x;
        const float y = camera.position.y;
        const float z = camera.position.z;
        std::cout << "Player position> ";
        std::cout << x << ", " << y << ", " << z << std::endl;
    }

    Game::Game(const int width,
               const int height,
               const GLfloat fps,
               const std::string &title,
               const std::string &version):
    camera(glm::vec3(0.0f, 0.0f, 50.0f), width, height),
    gameHelper(fps) {
        this->height = height;
        this->width = width;
        this->window = nullptr;
        this->title = title;
        this->version = version;

        this->deltaTime = 0;
    }

    void Game::init() {
        glLoadIdentity();
        texture[BRICK].loadTexture("../resources/images/brick.png");
        texture[WOOD].loadTexture("../resources/images/wood.png");
        texture[PAINTED].loadTexture("../resources/images/painted_brick.png");

        // Carregando texturas de cubemap
        const std::vector<std::string> faces = {
            "../resources/images/grass_block_side.png",
            "../resources/images/grass_block_side.png",
            "../resources/images/grass_block_top.png",
            "../resources/images/dirt.png",
            "../resources/images/grass_block_side.png",
            "../resources/images/grass_block_side.png"
        };
        texture[GRASS].loadCubemap(faces); // Carregar cubemap

        glClearColor(0.0f, 0.0, 0.0f, 1.0f);
        //glEnable(GL_CULL_FACE);
        //glCullFace(GL_CW);
        auto* terrain = new World::Terrain(glm::vec3(0.0f, -3.0f, 0.0f));
        terrain->BuildTerrain(500);
        objects.push_back(terrain);

        auto* chunk = new World::Chunk();
        chunk->generateChunk();

        chunks.push_back(chunk);

        //std::cout << chunk->getBlocks() << std::endl;
    }

    void Game::update() {
        GameHelpers::Camera::updateViewport(window);
        glLoadIdentity();
        camera.update(deltaTime);

        for(auto* object : objects) {
            object->Render();
        }

        chunks[0]->displayChunk();

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

        const float angularVelocity = 60 * deltaTime;
        angle += angularVelocity;
    }


    int Game::run() {
        running = true;
        if (!glfwInit()) return -1;
        window = glfwCreateWindow(width, height, (title + " " + version)
            .c_str(), nullptr, nullptr);
        if (!window) { glfwTerminate(); return -1; }

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

        init();

        while (!glfwWindowShouldClose(window) && running) {
            glfwPollEvents();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            deltaTime = gameHelper.fixFPS();

            update();

            glfwSwapBuffers(window);
        }
        running = false;
        glDisable(GL_CULL_FACE);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_DEPTH_TEST);
        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
    }

}

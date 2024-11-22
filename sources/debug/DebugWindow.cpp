//
// Created by Marcilio on 22/11/2024.
//

#include "DebugWindow.hpp"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "DebugHelper.hpp"
#include "../Game/Game.hpp"

namespace Debug {
    DebugWindow::DebugWindow(Minecraft::Game* _game, GameHelpers::Camera* _camera, GLFWwindow* _window) {
        x=0, z=0;
        debugHelper = new DebugHelper(_game, _camera);
        window = _window;
        camera = _camera;
        game = _game;

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init();
    }

    DebugWindow::~DebugWindow() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void DebugWindow::renderMainWindow() {
        // New ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void DebugWindow::renderFpsMSdebug() const {
        ImGui::SetNextWindowPos(ImVec2(10, 10)); // Topo esquerdo com 10px de margem
        ImGui::SetNextWindowSize(ImVec2(200, 130)); // Define um tamanho padrão para a janela
        ImGui::Begin("F3");
        const glm::vec3 pos = debugHelper->getPosition();
        ImGui::Text("Player Position>\n X: %.0f,\n Y: %.0f,\n Z: %.0f", pos.x, pos.y, pos.z);
        ImGui::Text("FPS: %f", game->fps);
        ImGui::Text("MS: %.1f", game->deltaTime * 100.0f);
        ImGui::End();
    }

    void DebugWindow::debugWindow() {
        ImGui::SetNextWindowPos(ImVec2(10, 150)); // Topo esquerdo com 10px de margem
        ImGui::SetNextWindowSize(ImVec2(200, 130)); // Define um tamanho padrão para a janela
        ImGui::Begin("Debug");
        ImGui::Text(("Chunk data> \n" + debugHelper->getChunksPos()).c_str());
        ImGui::InputInt("< X", &x, ImGuiInputTextFlags_None);
        ImGui::InputInt("< Z", &z, ImGuiInputTextFlags_None);
        if(ImGui::Button("Add other chunk")) {
            debugHelper->genNewChunk(x, z);
        }
        ImGui::End();
    }

}

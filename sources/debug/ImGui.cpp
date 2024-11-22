//
// Created by Marcilio on 22/11/2024.
//

#include "ImGui.hpp"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GL/gl.h>

#include "../Game/Game.hpp"

namespace debug {
    DebugTool::DebugTool() {
        x=0;
        z=0;
    }
    void DebugTool::InitDebugTool(GLFWwindow* wwindow) {

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
        ImGui_ImplGlfw_InitForOpenGL(wwindow, true);
        ImGui_ImplOpenGL3_Init();

    }

    void DebugTool::renderMainWindow() {
        // New ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void DebugTool::renderFpsMSdebug(const GLfloat deltaTime, const GLfloat fps, const Minecraft::Game* game) {
        ImGui::SetNextWindowPos(ImVec2(10, 10)); // Topo esquerdo com 10px de margem
        ImGui::SetNextWindowSize(ImVec2(200, 130)); // Define um tamanho padrão para a janela
        ImGui::Begin("F3");
        const glm::vec3 pos = game->getPosition();
        ImGui::Text("Player Position>\n X: %.0f,\n Y: %.0f,\n Z: %.0f", pos.x, pos.y, pos.z);
        ImGui::Text("FPS: %f", fps);
        ImGui::Text("MS: %.1f", deltaTime * 100.0f);
        ImGui::End();
    }

    void DebugTool::debugWindow(Minecraft::Game* game) {
        ImGui::SetNextWindowPos(ImVec2(10, 150)); // Topo esquerdo com 10px de margem
        ImGui::SetNextWindowSize(ImVec2(200, 130)); // Define um tamanho padrão para a janela
        ImGui::Begin("Debug");
        ImGui::Text(("Chunk data> " + game->getChunksPos()).c_str());
        ImGui::InputInt("< X", &x, ImGuiInputTextFlags_None);
        ImGui::InputInt("< Z", &z, ImGuiInputTextFlags_None);
        if(ImGui::Button("Add other chunk")) {
            game->genNewChunk(x, z);
        }
        ImGui::End();
    }

    void DebugTool::DestroyDebugTool() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}

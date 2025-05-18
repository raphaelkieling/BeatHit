#include "imgui.h"
#include "application.h"
#include "debug.h"
#include <raylib.h>
#include <string>
#include "rlImGui.h"

void Debug::EndProcess(Application* app) {
    ImGui::PopStyleColor();
    rlImGuiEnd();
}

void Debug::StartProcess(Application* app) {
    rlImGuiBegin();

    if (!app->currentScene) {
        return;
    }

    //ImGuiViewport* viewport = ImGui::GetMainViewport();
    //ImGui::SetNextWindowPos(viewport->Pos);
    //ImGui::SetNextWindowSize(viewport->Size);
    //ImGui::SetNextWindowViewport(viewport->ID);

    //ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar |
    //    ImGuiWindowFlags_NoCollapse |
    //    ImGuiWindowFlags_NoResize |
    //    ImGuiWindowFlags_NoMove |
    //    ImGuiWindowFlags_NoBringToFrontOnFocus |
    //    ImGuiWindowFlags_NoNavFocus |
    //    ImGuiWindowFlags_NoBackground;

    //// Estilo da janela fullscreen dockspace
    //ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    //ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    //ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    //ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));

    //ImGui::Begin("DockSpace Window", nullptr, window_flags);

    //ImGui::PopStyleColor();
    //ImGui::PopStyleVar(3);

    //ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    //ImGui::DockSpace(dockspace_id, ImVec2(0, 0), ImGuiDockNodeFlags_PassthruCentralNode);
    //ImGui::End();

    //// Janela Debug Info, flutuante e movível, sem dock automático
    //ImGuiWindowFlags debugFlags = ImGuiWindowFlags_NoDocking; // Não pode ser dockada

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Game")) {
            if (ImGui::MenuItem("Restart Scene")) {
                app->SetScene(app->currentScene->name);
            }

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0.7f));
    ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_Once);
    ImGui::Begin("Debug Info");
    ImGui::Text("FPS: %d", GetFPS());
    ImGui::Text("Delta Time: %f", GetFrameTime());
    ImGui::Text("Scene name: %s", app->currentScene->name.c_str());
    ImGui::Text("Count root scene: %d", (int)app->currentScene->components.size());

    for (int i = 0; i < app->currentScene->components.size(); i++) {
        Component* c = app->currentScene->components[i];

        std::string headerStr = "Entity: " + std::to_string(c->id);
        const char* header = headerStr.c_str();

        if (ImGui::CollapsingHeader(header)) {
            ImGui::Text("Id: %d", c->id);
            ImGui::Text("Local position: %d - %d", c->localPosition.x, c->localPosition.y);

            if (ImGui::Button("Drop")) {
                app->currentScene->DropComponentId(c->id);
            }
        }
    }

    ImGui::End();
}


void Debug::Load(Application* app) {
    rlImGuiSetup(true);

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
}
#include "imgui.h"
#include "application.h"
#include "debug.h"
#include "sprite.h"
#include "physicsComponent.h"
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

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0.7f));
    ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_Once);

    ImGui::Begin("Debug Info", nullptr, ImGuiWindowFlags_MenuBar);
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("Game")) {
                if (ImGui::MenuItem("Restart Scene")) {
                    app->SetScene(app->currentScene->name);
                }
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem(!app->pauseProcess ? "Pause" : "Play")) {
                app->pauseProcess = !app->pauseProcess;
            }

            if (ImGui::MenuItem("Save scene")) {
                printf("Saving scene\n");
            }

            ImGui::EndMenuBar();
        }

        ImGui::Text("FPS: %d", GetFPS());
        ImGui::Text("Frame Time: %f", GetFrameTime());
        ImGui::Text("Scene name: %s", app->currentScene->name.c_str());
        ImGui::Checkbox("Debug", &app->useDebug);

        if (ImGui::CollapsingHeader("Component Tree")) {
            RenderComponentTree(app->currentScene->root);
        }

    ImGui::End();
}

void Debug::RenderComponentTree(Component* component) {
    std::string nodeLabel = component->name + "##" + std::to_string(component->id);

    if (ImGui::TreeNode(nodeLabel.c_str())) {
        ImGui::Text("Id: %llu", component->id);
        ImGui::Text("Name: %s", component->name.c_str());
        ImGui::Text("Local position: %d - %d", (int)component->localPosition.x, (int)component->localPosition.y);

        if (Sprite* sprite = dynamic_cast<Sprite*>(component)) {
            ImGui::Text("Sprite path: %s", sprite->path);
            ImGui::SliderFloat("Cell X", &sprite->cellX, 0.0f, 20.0f);
            ImGui::SliderFloat("Cell Y", &sprite->cellY, 0.0f, 20.0f);

            ImGui::SliderFloat("Atlax X", &sprite->atlas.x, 0.0f, 20.0f);
            ImGui::SliderFloat("Atlax Y", &sprite->atlas.y, 0.0f, 20.0f);
            ImGui::Text("Texture Size: %d / %d", &sprite->texture.width, &sprite->texture.height);
        }

        if (PhysicsComponent* sprite = dynamic_cast<PhysicsComponent*>(component)) {
            ImGui::SliderFloat("Mass", &sprite->mass, 0.0f, 20.0f);
        }

        if (ImGui::Button(("Drop##" + std::to_string(component->id)).c_str())) {
            Application::GetInstance().currentScene->DropComponentId(component->id);
        }

        for (Component* child : component->components) {
            RenderComponentTree(child);
        }

        ImGui::TreePop();
    }
}

void Debug::Load(Application* app) {
    rlImGuiSetup(true);

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
}
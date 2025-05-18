#include "application.h"
#include "debug.h"
#include <raylib.h>
#include "imgui.h"
#include <string>
#include "rlImGui.h"

void Debug::EndProcess(Application* app) {
    rlImGuiEnd();
}

void Debug::StartProcess(Application* app){
     rlImGuiBegin();

     if (!app->currentScene) {
         return;
     }
     
     ImGui::Text("FPS: %d", GetFPS());
     ImGui::Text("Delta Time: %f", GetFrameTime());
     ImGui::Text("Scene name: %s", app->currentScene->name.c_str());
     ImGui::Text("Count root scene: %d", app->currentScene->components.size());

     if (ImGui::Button("Restart scene")) {
         app->SetScene(app->currentScene->name);
     }

     for (int i = 0; i < app->currentScene->components.size(); i++) {
         Component* c = app->currentScene->components[i];

         std::string headerStr = "Entity: " + std::to_string(c->id);
         const char* header = headerStr.c_str();

         if (ImGui::CollapsingHeader(header)) {
             ImGui::Text("Id: %d", c->id);
             ImGui::Text("Local position: %d - %d", c->localPosition.x, c->localPosition.y);

             if (ImGui::Button("Drop")) {
                 app->currentScene->DropComponentId(app->currentScene->components[i]->id);
             }
         }
     }
}

void Debug::Load(Application* app) {
    rlImGuiSetup(true);
}
#include "application.h"
#include "debug.h"
#include <raylib.h>
#include "imgui.h"

void Debug::Process(Application* app){
     if (app->currentScene) {
         ImGui::Text("FPS: %d", GetFPS());
         ImGui::Text("Scene name: %s", app->currentScene->name.c_str());
         ImGui::Text("Count root scene: %d", app->currentScene->components.size());

         if (ImGui::Button("Restart scene")) {
             app->SetScene(app->currentScene->name);
         }

         for (int i = 0; i < app->currentScene->components.size(); i++) {
             if (ImGui::CollapsingHeader("Entity")) {
                 ImGui::Text("Id: %d", app->currentScene->components[i]->id);

                 if (ImGui::Button("Drop")) {
                     app->currentScene->DropComponentId(app->currentScene->components[i]->id);
                 }
             }
         }
     }
    }
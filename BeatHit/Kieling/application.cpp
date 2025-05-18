#include <raylib.h>
#include "scene.cpp"
#include <vector>
#include <algorithm>
#include "rlImGui.h"
#include "imgui.h"

using namespace std;

class Application {
private:
	vector<Scene*> scenes;
	Scene* currentScene;

public:
	Application() {
		currentScene = nullptr;

		InitWindow(800, 600, "BeatHit");
		SetTargetFPS(60);
		rlImGuiSetup(true);
	}

	void DebugScene() {
		if (currentScene) {
			ImGui::Text("Scene name: %s", currentScene->name.c_str());
			ImGui::Text("Count root scene: %d", currentScene->components.size());

			if (ImGui::Button("Restart scene")) {
				currentScene->OnExit();
				currentScene->Load();
			}

			for (int i = 0; i < currentScene->components.size(); i++) {
				if (ImGui::CollapsingHeader("Entity")) {
					ImGui::Text("Id: %d", currentScene->components[i]->id);

					if (ImGui::Button("Drop")) {
						currentScene->DropComponentId(currentScene->components[i]->id);
					}
				}
			}
		}
	}

	void Run() {
		while (!WindowShouldClose()) {
			if (currentScene) {
				currentScene->ClearRemoveQueue();
			}

			BeginDrawing();
			ClearBackground(RAYWHITE);
			rlImGuiBegin();

			DebugScene();

			if (currentScene) {
				currentScene->Process();
			}

			rlImGuiEnd();
			EndDrawing();
		}
	}

	Application* AddScene(Scene* scene) {
		scenes.push_back(scene);
		return this;
	}

	Application* SetScene(string sceneName) {
		if (currentScene) {
			currentScene->OnExit();
		}

		auto it = find_if(scenes.begin(), scenes.end(), [&sceneName](Scene* s) {
			return s->name == sceneName;
		});

		if (it != scenes.end()) {
			currentScene = *it;
			currentScene->Load();
		}
		else {
			printf("Scene does't exists");
		}

		return this;
	}

	~Application() {
		rlImGuiShutdown();
		CloseWindow();
	}
};

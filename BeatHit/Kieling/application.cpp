#include <raylib.h>
#include "scene.cpp"
#include <vector>
#include <algorithm>
#include "rlImGui.h"
#include "imgui.h"

using namespace std;
using namespace Kieling;

namespace Kieling {
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

		void Run() {
			while (!WindowShouldClose()) {
				BeginDrawing();
				ClearBackground(RAYWHITE);
				rlImGuiBegin();

				if (currentScene) {
					DrawText(string("Welcome to BeatHit! " + currentScene->name).c_str(), 25, 25, 16, LIGHTGRAY);
				}

				ImGui::Text("Hello, world %d", 123);

				rlImGuiEnd();
				EndDrawing();
			}
		}

		Application* AddScene(Scene* scene) {
			scenes.push_back(scene);
			return this;
		}

		Application* SetScene(string sceneName) {
			auto it = find_if(scenes.begin(), scenes.end(), [&sceneName](Scene* s) {
				return s->name == sceneName;
			});

			if (it != scenes.end()) {
				currentScene = *it;
				currentScene->Load();
			} else {
				printf("Scene does't exists");
			}

			return this;
		}

		~Application() {
			rlImGuiShutdown();
			CloseWindow();
		}
	};
}


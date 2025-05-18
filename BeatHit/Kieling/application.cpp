#include <algorithm>
#include <raylib.h>
#include "rlImGui.h"
#include "imgui.h"
#include "application.h"

Application::Application() {
		currentScene = nullptr;

		InitWindow(800, 600, "BeatHit");
		SetTargetFPS(60);
		rlImGuiSetup(true);
}

void Application::Run() {
		while (!WindowShouldClose()) {
			if (currentScene) {
				currentScene->ClearRemoveQueue();
			}

			BeginDrawing();
			ClearBackground(RAYWHITE);
			rlImGuiBegin();

			debug.Process(this);

			if (currentScene) {
				currentScene->Process();
			}

			rlImGuiEnd();
			EndDrawing();
		}
}

Application* Application::AddScene(Scene* scene) {
		scenes.push_back(scene);
		return this;
}

Application* Application::SetScene(std::string sceneName) {
		if (currentScene) {
			currentScene->OnExit();
		}

		auto it = find_if(scenes.begin(), scenes.end(), [&sceneName](Scene* s) {
			return s->name == sceneName;
		});

		if (it != scenes.end()) {
			currentScene = *it;
			currentScene->Load();
			currentScene->OnStart();
		}
		else {
			printf("Scene does't exists");
		}

		return this;
}
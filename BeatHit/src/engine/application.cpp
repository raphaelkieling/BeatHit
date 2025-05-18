#include <algorithm>
#include <raylib.h>
#include "application.h"

Application::Application() {
		currentScene = nullptr;

		InitWindow(1280, 720, "BeatHit");
		SetTargetFPS(60);
		debug.Load(this);
}

void Application::Run() {
		while (!WindowShouldClose()) {
			if (currentScene) {
				currentScene->ClearRemoveQueue();
			}

			BeginDrawing();
			ClearBackground(RAYWHITE);
			
			debug.StartProcess(this);

			if (currentScene) {
				currentScene->Process();
			}

			debug.EndProcess(this);
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
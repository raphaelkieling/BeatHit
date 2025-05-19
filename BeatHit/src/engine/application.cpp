#include <algorithm>
#include <raylib.h>
#include "application.h"

Application::Application() {
		currentScene = nullptr;

		InitWindow(1280, 720, "BeatHit");
		SetTargetFPS(60);
		debug.Load(this);
}

Application& Application::GetInstance() {
	static Application instance;
	return instance;
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
				if (!pauseProcess) {
					currentScene->InternalProcess();
				}

				currentScene->InternalDraw();
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

static Component* FindComponentByName(Component* root, const std::string& name) {
	if (!root) return nullptr;
	if (root->name == name) return root;

	for (Component* child : root->components) {
		Component* found = FindComponentByName(child, name);
		if (found) return found;
	}

	return nullptr;
}

Component* Application::GetComponentByName(const std::string& name) {
	if (!currentScene || !currentScene->root) return nullptr;

	return FindComponentByName(currentScene->root, name);
}
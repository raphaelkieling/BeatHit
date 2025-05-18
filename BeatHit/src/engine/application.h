#pragma once
#include "scene.h"
#include "debug.h"
#include <vector>
#include <string>

class Application {
public:
	std::vector<Scene*> scenes;
	Scene* currentScene;
	Debug debug;

	Application();
	void Run();
	Application* AddScene(Scene* scene);
	Application* SetScene(std::string sceneName);
};
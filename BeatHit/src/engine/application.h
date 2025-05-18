#pragma once
#include <vector>
#include <string>
#include "scene.h"
#include "debug.h"

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
#pragma once
#include <vector>
#include <string>
#include "scene.h"
#include "debug.h"
#include "component.h"

class Application {
private:
    Application();
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

public:
    std::vector<Scene*> scenes;
    Scene* currentScene;
    Debug debug;

    static Application& GetInstance();

    Component* GetComponentByName(const std::string& name);

    void Run();
    Application* AddScene(Scene* scene);
	Application* SetScene(std::string sceneName);
};
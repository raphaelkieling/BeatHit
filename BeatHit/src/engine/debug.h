#pragma once

class Application;

class Debug {
public:
    void Load(Application* app);
    void StartProcess(Application* app);
    void EndProcess(Application* app);
    void RenderComponentTree(Component* component);
};

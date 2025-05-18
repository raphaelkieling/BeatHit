#include "Kieling/scene.h"
#include "Kieling/component.h"
#include <raylib.h>
#include "imgui.h"

class Ball : public Component {
private:
    Vector2 pos;
public:
    void Load() override {
        pos = { 200, 150 };
    }

    void Process() override {
        pos.y += 1;

        DrawCircleV(pos, 20, RED);
    }

    void Drop() override {}
};

class Game : public Scene {
public:
	Game() : Scene("Game") {}

    void Load() override {
        Ball* ball = new Ball();

        this->AddComponent(ball);
    }
};

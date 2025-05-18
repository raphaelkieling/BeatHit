#include "../engine/scene.h"
#include "../engine/component.h"
#include "ball.cpp"

class Game : public Scene {
public:
	Game() : Scene("Game") {}

    void Load() override {
        Ball* ball = new Ball();
        ball->setLocalPosition(Vector2{ 100, 100 });
        this->AddComponent(ball);
    }
};

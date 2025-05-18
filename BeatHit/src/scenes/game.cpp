#include "ball.cpp"
#include "../engine/scene.h"
#include "../engine/component.h"
#include "../engine/application.h"

class Game : public Scene {
public:
	Game() : Scene("Game") {}

    void Load() override {
        Ball* ball = new Ball();
        ball->SetName("ball")->SetLocalPosition(Vector2{100, 100});
        this->AddComponent(ball);

        Sprite* mouse = new Sprite("spritesheet-characters-default.png", 8, 8);
        mouse->SetAtlas(Vector2{2,2});
        mouse->SetName("mouse")->SetLocalPosition(Vector2{50, 50});
        this->AddComponent(mouse);
    }

    void Process() override {
        Sprite* m = dynamic_cast<Sprite*>(Application::GetInstance().GetComponentByName("mouse"));

        if (m) {
            m->localPosition.x = GetMousePosition().x;
            m->localPosition.y = GetMousePosition().y;
        }

        Scene::Process();
    }
};

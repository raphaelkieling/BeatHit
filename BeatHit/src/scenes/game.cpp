#include "ball.cpp"
#include "player.cpp"
#include "../engine/scene.h"
#include "../engine/component.h"
#include "../engine/application.h"
#include <raymath.h>

class Game : public Scene {
public:
	Game() : Scene("Game") {}

    void Load() override {
        Ball* ball = new Ball();
        ball->SetName("ball")->SetLocalPosition(Vector2{100, 100});
        this->AddComponent(ball);

        Player* player = new Player();
        player->SetName("player")->SetLocalPosition(Vector2{300, 300 });
        this->AddComponent(player);

        Sprite* mouse = new Sprite("spritesheet-characters-default.png", 8, 8);
        mouse->SetAtlas(Vector2{2,2});
        mouse->SetName("mouse")->SetLocalPosition(Vector2{50, 50});
        this->AddComponent(mouse);

        // TODO - make an engine component for it (if possible) since the camera has a
        // position. Maybe i would need to create a BeforeDraw() and AfterDraw() to do the same
        // as the scene
        activeCamera = new Camera2D();
        activeCamera->offset = Vector2{ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
        activeCamera->target = Vector2{ 0.0f, 0.0f };
        activeCamera->rotation = 0.0f;
        activeCamera->zoom = 0.6f;
    }

    void Process() override {
        Component* p = Application::GetInstance().GetComponentByName("player");
        if (p) {
            activeCamera->target = p->globalPosition;
        }
    }

    void Draw() override { }
};

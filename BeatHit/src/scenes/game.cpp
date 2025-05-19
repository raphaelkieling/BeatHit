#include "ball.cpp"
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
        activeCamera->zoom = 1.5f;
    }

    void Process() override {
        Component* c1 = Application::GetInstance().GetComponentByName("ball");
        Component* c2 = Application::GetInstance().GetComponentByName("mouse");

        if (c1 && c2) {
            Vector2 mouseScreen = GetMousePosition();
            Vector2 mouseWorld = GetScreenToWorld2D(mouseScreen, *activeCamera);


            activeCamera->target.x = Lerp(activeCamera->target.x, c1->globalPosition.x, 0.01);
            activeCamera->target.y = Lerp(activeCamera->target.y, c1->globalPosition.y, 0.01);

            c2->localPosition = mouseWorld;
        }
    }

    void Draw() override {
        Component* c1 = Application::GetInstance().GetComponentByName("ball");
        Component* c2 = Application::GetInstance().GetComponentByName("mouse");

        if (c1 && c2) {
            DrawLine(c1->localPosition.x, c1->globalPosition.y, c2->localPosition.x, c2->localPosition.y, PURPLE);
        }
    }
};

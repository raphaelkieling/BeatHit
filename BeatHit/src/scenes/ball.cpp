#include <raylib.h>
#include "imgui.h"
#include "../engine/component.h"
#include "../engine/utils.h"
#include "../engine/sprite.h"
#include "../engine/application.h"
#include <string>

class Ball : public Component {
private:
    int gravity = 40;

public:
    Ball() {}

    void Load() {
        Sprite* spr = new Sprite("spritesheet-enemies-default.png", 8, 8);
        spr->SetName("MainBallSprite");
        this->AddComponent(spr);
    }

    void Process() {
        localPosition.y += gravity * GetFrameTime();
        DrawCircleV(globalPosition, 2, RED);
    }

    void Drop() {}
};
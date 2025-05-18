#include <raylib.h>
#include "imgui.h"
#include "../engine/component.h"
#include "../engine/utils.h"
#include "../engine/sprite.h"
#include <string>

class Ball : public Component {
public:
    Ball() {}

    void Load() override {
        Sprite* spr = new Sprite("spritesheet-enemies-default.png", 8, 8);
        spr->setName("MainBallSprite");
        this->AddComponent(spr);
    }

    void Process() {
        localPosition.x += 1;

        DrawCircleV(globalPosition, 2, RED);
    }

    void Drop() override {}
};
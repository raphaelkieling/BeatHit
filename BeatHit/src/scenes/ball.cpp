#include <raylib.h>
#include "imgui.h"
#include "../engine/component.h"
#include "../engine/utils.h"
#include "../engine/sprite.h"
#include <string>

class Ball : public Component {
private:
    int gravity = 40;

public:
    Ball() {}

    void Load() {
        Sprite* spr = new Sprite("spritesheet-enemies-default.png", 8, 8);
        spr->SetAtlas(Vector2{ 1,1 });
        spr->SetName("MainBallSprite");
        this->AddComponent(spr);
    }

    void Process() {
        localPosition.y += gravity * GetFrameTime();
    }

    void Drop() {}

    void Draw() {}
};
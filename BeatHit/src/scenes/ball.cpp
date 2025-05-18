#include <raylib.h>
#include "imgui.h"
#include "../engine/component.h"
#include "../engine/utils.h"
#include "../engine/sprite.h"
#include <string>

class Ball : public Component {
private:
    Sprite spr;

public:
    Ball() {
        this->spr = Sprite("spritesheet-enemies-default.png", 8, 8);
    }

    void Load() override {
        spr.Load();
    }

    void Process() {
        localPosition.x += 1;

        DrawCircleV(globalPosition, 2, RED);

        spr.InternalProcess(this);
    }

    void Drop() override {
        spr.Drop();
    }
};
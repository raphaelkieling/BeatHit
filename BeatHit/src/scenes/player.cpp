#include <raylib.h>
#include "imgui.h"
#include "../engine/component.h"
#include "../engine/utils.h"
#include "../engine/sprite.h"
#include "../engine/physicsComponent.h"
#include <string>

class Player: public PhysicsComponent {
public:
    void Load() {
        this->mass = 10.0f;

        Sprite* spr = new Sprite("spritesheet-characters-default.png", 8, 8);
        spr->SetAtlas(Vector2{ 1,1 });
        spr->SetName("MainBallSprite");
        this->AddComponent(spr);
    }

    void Drop() {}

    void Draw() {}
};
#include <raylib.h>
#include "imgui.h"
#include "../engine/component.h"
#include "../engine/utils.h"
#include "../engine/sprite.h"
#include "../engine/physics_component.h"
#include "../engine/animation_player.h"
#include <string>

class Player: public PhysicsComponent {
public:
    void Load() {
        this->mass = 10.0f;

        auto* spr = new Sprite("spritesheet-characters-default.png", 8, 8);
        spr->SetAtlas(Vector2{ 1,1 });
        spr->SetName("MainBallSprite");
        this->AddComponent(spr);

        auto* anim = new AnimationPlayer(spr);
        anim->SetName("PlayerAnimation");
        anim->AddFrame({0, 0}, 0.2f);
        anim->AddFrame({0, 1}, 0.2f);
        this->AddComponent(anim);
    }

    void Drop() {}

    void Draw() {}
};
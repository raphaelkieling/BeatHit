#include <raylib.h>
#include "imgui.h"
#include "../engine/component.h"
#include "../engine/utils.h"
#include "../engine/sprite.h"
#include "../engine/physics_component.h"
#include "../engine/animation_player.h"
#include "../engine/state.h"
#include "../engine/state_machine.h"
#include <string>

class IdleState : public State
{
public:
    AnimationPlayer* anim;
    PhysicsComponent* player;
    StateMachine* machine;

    IdleState(AnimationPlayer* a, PhysicsComponent* p, StateMachine* s) : anim(a), player(p), machine(s) {}

    void OnEnter() override
    {
        anim->SetCurrentAnimation("idle");
    }
    void OnUpdate() override
    {
        if (IsKeyDown(KEY_D) or IsKeyDown(KEY_A))
        {
            machine->SetCurrent("move");
        }
    }
    void OnExit() override {}
    void OnDraw() override {}
};

class MoveState : public State
{
public:
    AnimationPlayer* anim;
    PhysicsComponent* player;
    StateMachine* machine;

    MoveState(AnimationPlayer* a, PhysicsComponent* p, StateMachine* s) : anim(a), player(p), machine(s) {}

    void OnEnter() override
    {
        anim->SetCurrentAnimation("run");
    }
    void OnUpdate() override
    {
        if (IsKeyDown(KEY_D))
        {
			player->direction = Vector2{ 1, 0 };
        }
        else if (IsKeyDown(KEY_A)) {
            player->direction = Vector2{ -1, 0 };
        }
        else {
            player->direction = Vector2{ 0, 0 };
            machine->SetCurrent("idle");
        }

        player->localPosition.x += player->direction.x * 10;
    }
    void OnExit() override {}
    void OnDraw() override {}
};

class Player : public PhysicsComponent
{
public:
    void Load()
    {
        this->mass = 10.0f;

        auto *spr = new Sprite("spritesheet-characters-default.png", 8, 8);
        spr->SetAtlas(Vector2{1, 1});
        spr->SetName("MainBallSprite");
        this->AddComponent(spr);

        auto *anim = new AnimationPlayer(spr);
        anim->SetName("AnimationPlayer");
        anim->AddAnimation("idle")
            ->AddFrameToAnimation("idle", {0, 0}, 0.2f)
            ->AddFrameToAnimation("idle", {0, 1}, 0.2f);
        anim->AddAnimation("run")
            ->AddFrameToAnimation("run", {0, 1}, 0.1f)
            ->AddFrameToAnimation("run", {0, 3}, 0.1f);
        this->AddComponent(anim);

        StateMachine *sm = new StateMachine();
        sm->SetName("MachinePlayer");
        sm
            ->AddState("idle", new IdleState(anim, this, sm))
            ->AddState("move", new MoveState(anim, this, sm))
            ->SetCurrent("idle");

        this->AddComponent(sm);
    }

    void Drop() {}

    void Draw() {}
};
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
    AnimationPlayer *anim;
    Component* player;
    StateMachine *machine;

    IdleState(AnimationPlayer* a, Component* p, StateMachine* s) : anim(a), player(p), machine(s) {}

    void OnEnter() override
    {
        anim->SetCurrentAnimation("idle");
        printf("Entrou no Idle\n");
    }
    void OnUpdate() override
    {
        if (IsKeyDown(KEY_D))
        {
            printf("INDO PRO RUN!");
            machine->SetCurrent("run");
        }
    }
    void OnExit() override { printf("Saiu do Idle\n"); }
    void OnDraw() override { /* draw idle */ }
};

class MoveState : public State
{
public:
    AnimationPlayer *anim;
    Component *player;
    StateMachine *machine;

    MoveState(AnimationPlayer* a, Component* p, StateMachine* s) : anim(a), player(p), machine(s) {}

    void OnEnter() override
    {
        anim->SetCurrentAnimation("run");
        printf("Entrou no Move\n");
    }
    void OnUpdate() override
    {
        if (IsKeyDown(KEY_D))
        {
            player->globalPosition.x += 5;
        }else {
            machine->SetCurrent("idle");
        }
    }
    void OnExit() override { printf("Saiu do Move\n"); }
    void OnDraw() override { /* draw move */ }
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
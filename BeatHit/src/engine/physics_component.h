#pragma once
#include "component.h"

class PhysicsComponent : public Component {
public:
    Vector2 direction = { 0,0 };
    float mass = 1.0f;
    float gravity = 9.8f;
    float velocity = 5.0f;

    PhysicsComponent(float mass = 1.0f, float gravity = 9.8f)
        : mass(mass), gravity(gravity) {}

    void Process() {
        velocity += gravity * mass * GetFrameTime();
        localPosition.y += velocity * GetFrameTime();
    }

    void Reset() {
        velocity = 0.0f;
    }
};
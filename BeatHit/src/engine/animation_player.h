#pragma once
#include "component.h"
#include "sprite.h"
#include <vector>

struct Frame {
    Vector2 atlasPos;
    float duration; // in seconds
};

class AnimationPlayer : public Component {
private:
    Sprite* sprite = nullptr;
    float timer = 0.0f;
    bool playing = true;
public:
    int currentFrame = 0;
    std::vector<Frame> frames;

    AnimationPlayer(Sprite* target) : Component(), sprite(target) {}

    void AddFrame(Vector2 atlasPos, float duration);
    void Load() override {}
    void Process() override;
    void Drop() override {}
    void Draw() override;
    void Play();
    void Pause();
    void Reset();
};
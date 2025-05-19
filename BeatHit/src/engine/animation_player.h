#pragma once
#include "component.h"
#include "sprite.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <raylib.h>

struct Frame {
    Vector2 atlasPos;
    float duration; // segundos
};

class Animation {
public:
    std::vector<Frame> frames;

    void AddFrame(Vector2 atlasPos, float duration) {
        frames.push_back({ atlasPos, duration });
    }
};

class AnimationPlayer : public Component {
private:
    Sprite* sprite = nullptr;
    std::unordered_map<std::string, Animation> animations;
    float timer = 0.0f;
    bool playing = true;
public:
    Animation* currentAnimation = nullptr;
    int currentFrame = 0;
    AnimationPlayer(Sprite* target);

    AnimationPlayer* AddAnimation(const std::string& name);
    AnimationPlayer* AddFrameToAnimation(const std::string& animName, Vector2 atlasPos, float duration);
    void SetCurrentAnimation(const std::string& name);

    void Load() override {}
    void Process() override;
    void Drop() override {}
    void Draw() override;

    void Play();
    void Pause();
    void Reset();
};

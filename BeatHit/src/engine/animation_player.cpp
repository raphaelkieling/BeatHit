#include "animation_player.h"
#include <raylib.h>

AnimationPlayer::AnimationPlayer(Sprite* target) : sprite(target) {}

AnimationPlayer* AnimationPlayer::AddAnimation(const std::string& name) {
    if (animations.find(name) == animations.end()) {
        animations[name] = Animation();
    }
    return this;
}

AnimationPlayer* AnimationPlayer::AddFrameToAnimation(const std::string& animName, Vector2 atlasPos, float duration) {
    if (animations.find(animName) != animations.end()) {
        animations[animName].AddFrame(atlasPos, duration);
    }
    return this;
}

void AnimationPlayer::SetCurrentAnimation(const std::string& name) {
    auto it = animations.find(name);
    if (it != animations.end()) {
        currentAnimation = &it->second;
        currentFrame = 0;
        timer = 0.0f;
        if (sprite && !currentAnimation->frames.empty()) {
            sprite->SetAtlas(currentAnimation->frames[0].atlasPos);
        }
        playing = true;
    }
}

void AnimationPlayer::Process() {
    if (!playing || !currentAnimation || currentAnimation->frames.empty() || !sprite) return;

    timer += GetFrameTime();
    if (timer >= currentAnimation->frames[currentFrame].duration) {
        timer = 0.0f;
        currentFrame = (currentFrame + 1) % currentAnimation->frames.size();
        sprite->SetAtlas(currentAnimation->frames[currentFrame].atlasPos);
    }
}

void AnimationPlayer::Draw() {
    if (sprite) sprite->Draw();
}

void AnimationPlayer::Play() {
    playing = true;
}

void AnimationPlayer::Pause() {
    playing = false;
}

void AnimationPlayer::Reset() {
    currentFrame = 0;
    timer = 0.0f;
    if (sprite && currentAnimation && !currentAnimation->frames.empty())
        sprite->SetAtlas(currentAnimation->frames[0].atlasPos);
}

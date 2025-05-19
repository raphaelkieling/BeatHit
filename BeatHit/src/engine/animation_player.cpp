#include "animation_player.h"

void AnimationPlayer::AddFrame(Vector2 atlasPos, float duration) {
    frames.push_back({ atlasPos, duration });
}

void AnimationPlayer::Play() { playing = true; }
void AnimationPlayer::Pause() { playing = false; }
void AnimationPlayer::Reset() {
    currentFrame = 0;
    timer = 0;
}

void AnimationPlayer::Process() {
    if (!playing || frames.empty() || !sprite) return;

    timer += GetFrameTime();
    if (timer >= frames[currentFrame].duration) {
        timer = 0;
        currentFrame = (currentFrame + 1) % frames.size();
    }
}

void AnimationPlayer::Draw() {
    sprite->SetAtlas(frames[currentFrame].atlasPos);
}
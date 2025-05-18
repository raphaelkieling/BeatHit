#include "sprite.h"
#include <raylib.h>
#include <string>
#include "application.h"

void Sprite::Load() {
    texture = LoadTexture(getAssetPath(this->path).c_str());
}

void Sprite::Process() {}

void Sprite::Draw() {
    float sizeX = texture.width / cellX;
    float sizeY = texture.height / cellY;

    if (Application::GetInstance().useDebug) {
        // Show Whole Sprite for debug
        // DrawTextureRec(texture, { 0, 0, (float)texture.width, (float)texture.height}, globalPosition, WHITE);

        DrawCircleV(globalPosition, 2, RED);
        DrawRectangleLines(globalPosition.x, globalPosition.y, (int)sizeX, (int)sizeY, GREEN);
    }
    
    DrawTextureRec(texture, { (float)atlas.x * sizeX, (float)atlas.y * sizeY, sizeX, sizeY }, globalPosition, WHITE);
}

Sprite* Sprite::SetAtlas(Vector2 vec) {
    this->atlas = vec;
    return this;
}

void Sprite::Drop() {
    UnloadTexture(texture);
}
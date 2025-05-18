#include "sprite.h"
#include <raylib.h>
#include <imgui.h>
#include <string>

void Sprite::Load() {
    texture = LoadTexture(getAssetPath(this->path).c_str());
}

void Sprite::Process() {
    std::string headerStr = "Sprite: " + std::to_string(id);
    ImGui::Begin(headerStr.c_str());

    float sizeX = texture.width / cellX;
    float sizeY = texture.height / cellY;

    ImGui::Text("Texture Size: %d / %d", texture.width, texture.height);
    ImGui::Text("Cell Size: %f / %f", cellX, cellY);
    ImGui::Text("Actual Size: %f / %f", sizeX, sizeY);

    DrawTextureRec(texture, { 0, 0, sizeX, sizeY }, globalPosition, WHITE);
    
    // Show Whole Sprite for debug
    //DrawTextureRec(texture, { 0, 0, (float)texture.width, (float)texture.height}, globalPosition, WHITE);

    DrawRectangleLines(globalPosition.x , globalPosition.y, (int)sizeX, (int)sizeY, GREEN);

    ImGui::End();
}

void Sprite::Drop() {
    UnloadTexture(texture);
}
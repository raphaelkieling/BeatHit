#include "component.h"
#include <raylib.h>

class Sprite: public Component {
public:
	float cellX;
	float cellY;
	Vector2 atlas = Vector2{ 0,0 };
	Texture2D texture;
	const char* path;

	Sprite() = default;
	Sprite(const char* filePath) : Component(), path(filePath) {}
	Sprite(const char* filePath, float cellXx, float cellYy) : Component(), path(filePath), cellX(cellXx), cellY(cellYy) {}

	Sprite* SetAtlas(Vector2 vec);
	void Load() override;
	void Process() override;
	void Drop() override;
	void Draw() override;
};
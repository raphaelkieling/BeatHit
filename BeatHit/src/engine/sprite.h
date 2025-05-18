#include "component.h"
#include <raylib.h>

class Sprite: public Component {
private:
	Texture2D texture;
	const char* path;

	float cellX;
	float cellY;

public:
	Sprite() = default;
	Sprite(const char* filePath) : Component(), path(filePath) {}
	Sprite(const char* filePath, float cellXx, float cellYy) : Component(), path(filePath), cellX(cellXx), cellY(cellYy) {}

	void Load() override;
	void Process() override;
	void Drop() override;
};
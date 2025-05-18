#include "Kieling/scene.h"
#include "Kieling/component.h"
#include <raylib.h>

class Ball : public Component {
private:
    Vector2 pos;
public:
    void Load() override {
        printf("---- BALL\n");
        pos.x = 100;
        pos.y = 150;
    }

    void Process() override {
        printf("---- BALL PROCESS\n");
        pos.x += 5;
        DrawCircleV(pos, 20, RED);
    }

    void Drop() override {
        printf("---- BALL DROP\n");
    }
};

class Game : public Scene {
public:
	Game() : Scene("Game") {
        Ball* ball = new Ball();

		this->AddComponent(ball);
	}
};

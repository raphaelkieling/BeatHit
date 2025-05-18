#include "BeatHit.h"
#include "Kieling/application.cpp"
#include "GameScene.cpp"

using namespace std;

int main()
{
	Application app;
	Game game;

	app
		.AddScene(&game)
		->SetScene(game.name)
		->Run();

	return 0;
}

#include "BeatHit.h"
#include "Kieling/application.h"
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

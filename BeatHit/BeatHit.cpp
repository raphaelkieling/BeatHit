#include "BeatHit.h"
#include "src/engine/application.h"
#include "src/scenes/game.cpp"

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

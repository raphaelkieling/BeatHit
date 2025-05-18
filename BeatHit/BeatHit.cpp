// BeatHit.cpp : Defines the entry point for the application.
//

#include "BeatHit.h"
#include "Kieling/application.cpp"

using namespace std;
using namespace Kieling;

class Menu : public Scene {
public:
	Menu() : Scene("Menu"){}
};

class Game : public Scene {
public:
	Game() : Scene("Game") {}
};

int main()
{
	Application app;
	Menu menu;
	Game game;

	app
		.AddScene(&menu)
		->AddScene(&game)
		->SetScene(menu.name)
		->Run();

	return 0;
}

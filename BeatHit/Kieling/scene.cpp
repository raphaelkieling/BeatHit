#include <vector>
#include <string>
#include "scene.h"
#include "component.h"

using namespace std;

void Scene::Load() {
	printf(string("Loading scene: " + name).c_str());

	for(Component* c: this->components)
	{
		c->Load();
	}
}

void Scene::Process() {
	for (Component* c : this->components)
	{
		c->Process();
	}
}

void Scene::OnExit() {
	for (Component* c : this->components)
	{
		c->Drop();
	}
}

void Scene::AddComponent(Component* component) {
	components.push_back(component);
}
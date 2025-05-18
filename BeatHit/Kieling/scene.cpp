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

	ClearComponents();
}

void Scene::AddComponent(Component* component) {
	components.push_back(component);
}

void Scene::ClearRemoveQueue() {
	while (!toRemoveIds.empty()) {
		uint64_t id = toRemoveIds.front(); 
		toRemoveIds.pop(); 

		auto it = std::find_if(components.begin(), components.end(),
			[id](Component* c) { return c->id == id; });

		if (it != components.end()) {
			delete* it;
			components.erase(it);
		}
	}
}

void Scene::ClearComponents() {	
	for (auto it = components.begin(); it != components.end(); ) {
		delete* it;
		it = components.erase(it);
	}
}

void Scene::DropComponentId(uint64_t id) {
	toRemoveIds.push(id);
}
#include <vector>
#include <string>
#include "component.h"
#include "scene.h"

void Scene::OnStart() {
	root->Load();
}

void Scene::Process()  {
	root->InternalProcess(root);
}

void Scene::OnExit()  {
	root->Drop();
	root->ClearAllChildren();
}

void Scene::AddComponent(Component* component) {
	root->AddComponent(component);
}

void Scene::ClearRemoveQueue() {
	while (!toRemoveIds.empty()) {
		uint64_t id = toRemoveIds.front();
		toRemoveIds.pop();

		root->RemoveComponentById(id);
	}
}

void Scene::DropComponentId(uint64_t id) {
	toRemoveIds.push(id);
}
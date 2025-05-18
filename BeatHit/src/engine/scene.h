#pragma once
#include <vector>
#include <string>
#include <queue>
#include "component.h"
#include "root.h"

class Scene {
public:
	std::string name;
	std::queue<uint64_t> toRemoveIds;
	Root* root;

	Scene(std::string name): name(name) {
		Root* r = new Root();
		this->root = r;
	}

	virtual void Load() = 0;
	virtual void AddComponent(Component* component);
	virtual void DropComponentId(uint64_t id);
	virtual void ClearRemoveQueue();

	virtual void OnStart();
	virtual void Process();
	virtual void Draw();
	virtual void OnExit();
};
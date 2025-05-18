#pragma once
#include <vector>
#include <string>
#include <queue>
#include "component.h"

class Scene {
public:
	std::vector<Component*> components;
	std::string name;
	std::queue<uint64_t> toRemoveIds;

	Scene(std::string name) {
		this->name = name;
	}

	virtual void Load() = 0;
	virtual void AddComponent(Component* component);
	virtual void DropComponentId(uint64_t id);
	virtual void ClearRemoveQueue();
	virtual void ClearComponents();

	virtual void OnStart();
	virtual void Process();
	virtual void OnExit();
};
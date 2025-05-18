#pragma once
#include <vector>
#include <string>
#include "component.h"

class Scene {
public:
	std::vector<Component*> components;
	std::string name;

	Scene(std::string name) {
		this->name = name;
	}

	virtual void Load();
	virtual void Process();
	virtual void AddComponent(Component* component);
	virtual void OnExit();
};
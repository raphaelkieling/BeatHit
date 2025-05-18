#pragma once
#include "utils.h"
#include <raylib.h>
#include <vector>

class Component {
public:
	uint64_t id;

	Vector2 globalPosition;
	Vector2 localPosition;
	std::vector<Component*> components;
	std::string name;

	Component() {
		this->id = generateRandomId64();
		this->globalPosition = Vector2{ 0, 0 };
		this->localPosition = Vector2{ 0, 0 };
	}

	Component* setLocalPosition(Vector2 localPosition);
	Component* GetComponentById(uint64_t id);
	Component* GetComponentByName(const std::string& searchName);
	Component* setName(const std::string& newName);

	virtual void Load() = 0;
	virtual void Process() = 0;
	virtual void Drop() = 0;

	void AddComponent(Component* c);
	void InternalProcess(Component* parent);
	void InternalProcess();
};
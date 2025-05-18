#pragma once
#include "utils.h"
#include <raylib.h>

class Component {
public:
	uint64_t id;

	Vector2 globalPosition;
	Vector2 localPosition;

	Component() {
		this->id = generateRandomId64();
		this->globalPosition = Vector2{ 0, 0 };
		this->localPosition = Vector2{ 0, 0 };
	}

	Component* setLocalPosition(Vector2 localPosition);

	virtual void Load() = 0;
	virtual void Process() = 0;
	virtual void Drop() = 0;

	void InternalProcess(Component* parent);
	void InternalProcess();
};
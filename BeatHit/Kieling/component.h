#pragma once
#include "utils.h"

class Component {
public:
	uint64_t id;

	Component() {
		this->id = generateRandomId64();
	}

	virtual void Load() = 0;
	virtual void Process() = 0;
	virtual void Drop() = 0;
	virtual ~Component() {}
};
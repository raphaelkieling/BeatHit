#include "component.h"
#include <raymath.h>

Component* Component::setLocalPosition(Vector2 localPosition) {
	this->localPosition = localPosition;
	return this;
}

void Component::AddComponent(Component* c) {
	if (c) {
		components.push_back(c);
		c->Load();
	}
}

Component* Component::setName(const std::string& newName) {
	this->name = newName;
	return this;
}

void Component::InternalProcess(Component* parent) {
	globalPosition = Vector2Add(parent->globalPosition, localPosition);
	this->Process();

	for (Component* c : components) {
		c->InternalProcess(this);
	}
}

Component* Component::GetComponentById(uint64_t searchId) {
	if (this->id == searchId) return this;

	for (auto* c : components) {
		if (!c) continue;
		Component* result = c->GetComponentById(searchId);
		if (result) return result;
	}

	return nullptr;
}

Component* Component::GetComponentByName(const std::string& searchName) {
	if (this->name == searchName) return this;

	for (auto* c : components) {
		if (!c) continue;
		Component* result = c->GetComponentByName(searchName);
		if (result) return result;
	}

	return nullptr;
}

void Component::InternalProcess() {
	globalPosition = localPosition;
	this->Process();

	for (Component* c : components) {
		if (c) {
			c->InternalProcess(this);
		}
	}
}

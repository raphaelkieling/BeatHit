#include "component.h"
#include <raymath.h>

Component* Component::SetLocalPosition(Vector2 localPosition) {
	this->localPosition = localPosition;
	return this;
}

void Component::AddComponent(Component* c) {
	if (c) {
		components.push_back(c);
		c->Load();
	}
}

Component* Component::SetName(const std::string& newName) {
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

void Component::InternalDraw(Component* parent) {
	this->Draw();

	for (Component* c : components) {
		c->InternalDraw(this);
	}
}


void Component::Draw() {
	for (Component* c : components) {
		c->Draw();
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

bool Component::RemoveComponentById(uint64_t id) {
	for (auto it = components.begin(); it != components.end(); ++it) {
		if ((*it)->id == id) {
			delete* it;
			components.erase(it);
			return true;
		}
		else if ((*it)->RemoveComponentById(id)) {
			return true;
		}
	}
	return false;
}

void Component::ClearAllChildren() {
	for (Component* c : components) {
		c->Drop();
		c->ClearAllChildren();
		delete c;
	}
	components.clear();
}
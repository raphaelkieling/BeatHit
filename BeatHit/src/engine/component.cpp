#include "component.h"

Component* Component::setLocalPosition(Vector2 localPosition) {
	this->localPosition.x = localPosition.x;
	this->localPosition.y = localPosition.y;
	return this;
}

void Component::InternalProcess(Component* parent) {
	this->globalPosition.x = parent->globalPosition.x + this->localPosition.x;
	this->globalPosition.y = parent->globalPosition.y + this->localPosition.y;

	Process();
}

void Component::InternalProcess() {
	this->globalPosition.x = this->localPosition.x;
	this->globalPosition.y = this->localPosition.y;

	Process();
}
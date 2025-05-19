#pragma once
#include <vector>
#include <string>
#include <queue>
#include "component.h"
#include "root.h"

// TODO: we could have a cache for the component here and invalidate the cache as soon
// as something is removed / added
class Scene {
private:
	Vector2 lastCameraMousePos = { 0 };
	void CameraControl();

public:
	std::string name;
	std::queue<uint64_t> toRemoveIds;
	Root* root;
	Camera2D* activeCamera;

	Scene(std::string name): name(name) {
		Root* r = new Root();
		this->root = r;
		this->activeCamera = nullptr;
	}

	virtual void Load() = 0;
	virtual void AddComponent(Component* component);
	virtual void DropComponentId(uint64_t id);
	virtual void ClearRemoveQueue();

	virtual void OnStart();
	virtual void Process();
	virtual void Draw();
	virtual void OnExit();

	void InternalProcess();
	void InternalDraw();
};